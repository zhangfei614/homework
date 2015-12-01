#include "test.h"
#include "test_server.h"
#include <string>
#include <vector>

using namespace homework;
using namespace std;

void Test::TestUploadNegetive()
{
    TestServer* demo = new TestServer();
    if(TestUploadInternal(demo))
    {
        cout << "demo pass" << endl;
    }
    else
    {
        cout << "demo fail" << endl;
    }
}

bool Test::TestUploadInternal(TestServer* testServer)
{
    std::string tableName = "demo";
    std::string content = "this is a demo string";

    /*在init过程会调用正常的UpdateTable逻辑*/
    testServer->InitTableForTest(tableName, content);
    
    cout<<"Init success"<<endl;
    /*获取table所有拷贝所在的Worker id*/
    std::vector<size_t> workers = testServer->mTables["demo"];

    if (workers.size() == 0)
    {
        return false;
    }
    cout<<"Get workers success"<<endl;
    /*检查每一个拷贝是否都写成功*/
    for (size_t i = 0; i < workers.size(); ++i)
    {
        std::string result;
        testServer->mWorkers[workers[i]]->ReadTable(tableName, result);
        if (result != content)
        {
            return false;
        }
    }
    cout<<"Write success"<<endl;
    /*添加了test worker后，update会失败,server会向每一个worker里面写入程序*/
    if (testServer->UpdateTable(tableName, content) != false)
    {
        return false;
    }
    cout<<"Detect roll back success"<<endl;
    /*检查之前写入的表是否还能被成功读出*/
    std::vector<size_t> newWorkers = testServer->mTables["demo"];
    for (size_t i = 0; i < newWorkers.size(); ++i)
    {
        std::string result;
        testServer->mWorkers[newWorkers[i]]->ReadTable(tableName, result);
        if (result != content)
        {
            return false;
        }
    }
    cout<<"rollback success"<<endl;
    return true;    
}
