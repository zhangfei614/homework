#coding=utf-8
"""倒排索引"""
from pyspark import SparkContext

doc1Path = "/input/m1k1.in"
doc2Path = "/input/m1k2.in"
jaccard = 0.5
splitChar=':'

sc = SparkContext("local","InverseList")

#将输入文件转为（id,[token1 token2]),且保证不重复
doc1 = sc.textFile(doc1Path)
		.map(lambda line:line.split(splitChar))
		.map(lambda a:(a[0],list(set(a[1].split()))))
doc2 = sc.textFile(doc2Path)
		.map(lambda line:line.split(splitChar))
		.map(lambda a:(a[0],list(set(a[1].split()))))

#获取doc2的InvertedList(token,'id1,id2...')
invertedList = doc2.flatMap(lambda (x,y):[(m,x) for m in y])
					.reduceByKey(lambda a,b:a+','+b)

#使用join太慢，使用map-side　join
invertedList_map = dict(invertedList.collect())

#对doc1中的每个文档，查找该文档包含的所有token的IvertedList，并合并去重
#（id,id)
def candidates_map(line):
	words=line[1]
	s=set()
	for word in words:
		if invertedList_map.has_key(word):
			for m in invertedList_map[word].split(','):
				s.add((line[0],m))
	return list(s)

candidates = doc1.flatMap(candidates_map)

candidates.saveAsTextFile('/output/ic/')
#对每一个候选对计算jaccard值
def jaccard_similarity(x,y):
	intersection_cardinality = len(set.intersection(*[set(x), set(y)]))
	union_cardinality = len(set.union(*[set(x), set(y)]))
	return intersection_cardinality/float(union_cardinality)

#使用RDD的join太慢，采用简略的map-side join
doc1_map=dict(doc1.collect())
doc2_map=dict(doc2.collect())
candidates=candidates.map(lambda (x,y):((x,y),jaccard_similarity(doc1_map[x],doc2_map[y])))

#过滤小于阈值的对
candidates=candidates.filter(lambda (x,y):y>=jaccard)

candidates.saveAsTextFile('/output/i/')