Step 1:首先在config.h中配置NUMBERS_COUNT和MAX_NUMBER的大小。
Step 2:分别编译RandomNumberGeneration.cpp和FindMinNumer.cpp 

g++ -std=c++11 RandomNumbersGeneration.cpp -o random.exe
g++ -std=c++11 FindMinNumber.cpp -o find.exe

因为RandomNumberGeneration.cpp使用到了C++11的特性，应在编译加入-std=c++11选项

Step 3:运行random.exe生成data.in测试文件，运行find.exe对data.in文件里面的数据进行测试