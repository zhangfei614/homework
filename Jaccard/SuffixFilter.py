#coding=utf-8
"""前缀过滤+位置过滤＋后缀过滤"""
from pyspark import SparkContext

doc1Path = "/input/m1k1.in"
doc2Path = "/input/m1k2.in"
jaccard = 0.5
splitChar=':'

sc = SparkContext("local","SuffixFilter")

#将输入文件转为（id,[token1 token2]),且保证不重复
doc1 = sc.textFile(doc1Path).map(lambda line:line.split(splitChar)).map(lambda a:(a[0],list(set(a[1].split()))))
doc2 = sc.textFile(doc2Path).map(lambda line:line.split(splitChar)).map(lambda a:(a[0],list(set(a[1].split()))))

#计算所有token的文档频率,并排序
df = doc1.union(doc2).flatMap(lambda (x,y):[(m,1) for m in y]).reduceByKey(lambda a,b:a+b).map(lambda (x,y):(y,x)).sortByKey()

#生成token对照表，出现频率多权重较大
df_collect = df.collect()
counter = 0
token_dict={}
for (x,y) in df_collect:
	counter+=1
	token_dict[y]=counter
	
#将所有doc中的token进行排序
def sort_map(line):
	words=[token_dict[m] for m in line[1]]
	words.sort()
	return (line[0],words)

doc1_sort = doc1.map(sort_map)
doc2_sort = doc2.map(sort_map)

#取前缀
doc1_prefix=doc1_sort.map(lambda (x,y):(x,y[:int(round((1-jaccard)*len(y))+1)]))
doc2_prefix=doc2_sort.map(lambda (x,y):(x,y[:int(round((1-jaccard)*len(y))+1)]))

#方便查找
doc1_prefix_map=dict(doc1_prefix.collect())
doc2_prefix_map=dict(doc2_prefix.collect())
doc1_map=dict(doc1_sort.collect())
doc2_map=dict(doc2_sort.collect())

#获取doc2的InvertedList(token,'id1,id2...')
invertedList = doc2_prefix.flatMap(lambda (x,y):[(m,x) for m in y]).reduceByKey(lambda a,b:a+','+b)

#使用join太慢，使用map-side　join
invertedList_map = dict(invertedList.collect())

#前缀过滤，前缀含有相投字符的作为候选集
def candidates_map(line):
	words=line[1]
	s=set()
	for word in words:
		if invertedList_map.has_key(word):
			for m in invertedList_map[word].split(','):
				s.add((line[0],m))
	return list(s)

#经过前缀过滤
candidates = doc1_prefix.flatMap(candidates_map)


#后缀最大overlap
MAX_DEPTH = 1
def suffix(x,y,dp):
    if(dp > MAX_DEPTH or len(x) == 0 or len(y) == 0):
        return min(len(x),len(y))
    m = len(y)/2
    key = y[m]
    lo,hi = 0,len(x)-1
    while(lo < hi):
        mid = (lo+hi)/2
        if(key <= x[mid]):
            hi=mid
        else:
            lo=mid+1
    if(x[lo] == key):
        return suffix(x[:lo],y[:m-1],dp+1)+1+suffix(x[lo+1:],y[m+1:],dp+1)
    else:
        return suffix(x[:lo-1],y[:m-1],dp+1)+suffix(x[lo:],y[m+1:],dp+1)


#position和suffix过滤
def position_suffix_filter((px,x),(py,y)):
	rpx=list(reversed(px))
	rpy=list(reversed(py))
	if rpx[0] > rpy[0]:
		while len(rpx) > 0 and rpx[0] > rpy[0]:
			del rpx[0]
	else:
		while len(rpy) > 0 and rpy[0] > rpx[0]:
			del rpy[0]
	intersection_cardinality = len(set.intersection(*[set(rpx), set(rpy)]))
	prefix_union_cardinality = len(set.union(*[set(rpx), set(rpy)]))
	if ((intersection_cardinality+min(len(x)-len(rpx),len(y)-len(rpy)))/float(prefix_union_cardinality+max(len(x)-len(rpx),len(y)-len(rpy))) < jaccard):
		return False
	H_max=intersection_cardinality+suffix(x[len(rpx):],y[len(rpy):],1)
	union_cardinality = len(set.union(*[set(x), set(y)]))
	return H_max >= union_cardinality*jaccard


candidates = candidates.filter(lambda (x,y):position_suffix_filter((doc1_prefix_map[x],doc1_map[x]),(doc2_prefix_map[y],doc2_map[y])))
candidates.saveAsTextFile('/output/ppsc/')

#对每一个候选对计算jaccard值
def jaccard_similarity(x,y):
	intersection_cardinality = len(set.intersection(*[set(x), set(y)]))
	union_cardinality = len(set.union(*[set(x), set(y)]))
	return intersection_cardinality/float(union_cardinality)

candidates=candidates.map(lambda (x,y):((x,y),jaccard_similarity(doc1_map[x],doc2_map[y])))

#过滤小于阈值的对
candidates=candidates.filter(lambda (x,y):y>=jaccard)

candidates.saveAsTextFile('/output/pps/')