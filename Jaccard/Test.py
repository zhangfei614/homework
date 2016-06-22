"""Simple example in WordCount"""
from pyspark import SparkContext

inputFilePath = "hdfs://localhost:9000/input/"
sc = SparkContext("local","Simple App")
inputFile = sc.textFile(inputFilePath)

result = inputFile.flatMap(lambda line: line.split()).map(lambda word: (word, 1)).reduceByKey(lambda a, b: a+b)

result.saveAsTextFile('/output/')
