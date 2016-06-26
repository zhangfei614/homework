#coding=utf-8
"""前缀过滤"""
from pyspark import SparkContext

doc1Path = "/input/m1k1.in"
doc2Path = "/input/m1k1.in"
jaccard = 0.5
splitChar=':'

sc = SparkContext("local","PrefixFilter")

#将输入文件转为（id,[token1 token2]),且保证不重复
doc1 = sc.textFile(doc1Path).map(lambda line:line.split(splitChar)).map(lambda a:(a[0],list(set(a[1].split()))))
doc2 = sc.textFile(doc2Path).map(lambda line:line.split(splitChar)).map(lambda a:(a[0],list(set(a[1].split()))))

#计算所有token的文档频率,并排序
df = doc1.union(doc2)
		.flatMap(lambda (x,y):[(m,1) for m in y])
		.reduceByKey(lambda a,b:a+b)
		.map(lambda (x,y):(y,x))
		.sortByKey()

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

candidates.saveAsTextFile('/output/pc/')

#对每一个候选对计算jaccard值
def jaccard_similarity(x,y):
	intersection_cardinality = len(set.intersection(*[set(x), set(y)]))
	union_cardinality = len(set.union(*[set(x), set(y)]))
	return intersection_cardinality/float(union_cardinality)

#使用RDD的join太慢，采用简略的map-side join
candidates=candidates.map(lambda (x,y):((x,y),jaccard_similarity(doc1_map[x],doc2_map[y])))

#过滤小于阈值的对
candidates=candidates.filter(lambda (x,y):y>=jaccard)

candidates.saveAsTextFile('/output/p/')