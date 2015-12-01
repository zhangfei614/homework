#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <map>
#include <vector>

namespace homework
{
class Worker
{
public:
    Worker(size_t workerId)
    : mWorkerId(workerId)
    {}

    bool UpdateTable(const std::string& tableName, const std::string& content);

    bool ReadTable(const std::string& tableName, std::string& content);

    //提交事务，释放原有文件
    bool commit();
    
    //会滚事务，删除新建文件
    bool rollback(const std::string& tableName);
protected:
    static std::string GetFileId();
    
    virtual bool CreateFile(const std::string& fileId);

    virtual bool DeleteFile(const std::string& fileId);

    virtual bool RenameFile(const std::string& oriFileId, const std::string& newFileId);

    virtual bool WriteToFile(const std::string& fileId, const std::string& content);

    virtual bool ReadFile(const std::string& fileId, std::string& content);    

    //将文件内容按照特定长度分割
    std::vector<std::string> split(const std::string &s,int slength);
    
    //存放原有的fileIds
    std::vector<std::string> log;
    
    size_t mWorkerId;
    std::map<std::string, std::vector<std::string> > mTableFiles;
    std::map<std::string, std::string> mFiles;
};
typedef Worker* WorkerPtr;

}
#endif

