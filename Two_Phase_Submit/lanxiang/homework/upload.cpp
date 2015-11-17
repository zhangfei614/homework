#include "server.h"
#include <algorithm>
#include <sstream>

using namespace std;
using namespace homework;
static map<WorkerPtr, string> currentUpdatingTable;
static map<WorkerPtr, Worker::FileIds> tmpFileIds;

bool Server::UpdateTable(const string& tableName, const string& content)
{
    WorkerPtrs workers;
    if (mTables.find(tableName) == mTables.end()) {
        // 如果没找到这个表，就让每个worker去创建表
        for (map<uint8_t, WorkerPtr>::iterator it = mWorkers.begin();
                it != mWorkers.end(); ++it) {
            workers.push_back(it->second);
        }
    }
    /**
     * 找到该表所在的workers
     */
    else {
        WorkerIds workerIds = mTables[tableName];
        for (WorkerIds::iterator it = workerIds.begin();
                it != workerIds.end(); ++it) {
            workers.push_back(mWorkers[*it]);
        }
    }

    /**
     * 让每个worker去更新表
     */
    bool updateSucceed = true;
    for (WorkerPtrs::iterator it = workers.begin();
            it != workers.end(); ++it) {
        updateSucceed &= (*it)->UpdateTable(tableName, content);
    }

    if (updateSucceed && mTables.find(tableName) == mTables.end()) {
        WorkerIds workerIds = WorkerIds();
        for (map<uint8_t, WorkerPtr>::iterator it = mWorkers.begin();
                it != mWorkers.end(); ++it) {
            workerIds.push_back(it->first);
        }
    }

    /**
     * 都成功则每个worker都commit
     * 否则就都rollback
     */
    bool commitOrRollbackSucceed = true;
    for (WorkerPtrs::iterator it = workers.begin();
            it != workers.end(); ++it) {
        if (updateSucceed)
            commitOrRollbackSucceed &= (*it)->commit();
        else
            commitOrRollbackSucceed &= (*it)->rollback();
    }

    return updateSucceed && commitOrRollbackSucceed;
}

bool Worker::UpdateTable(const string& tableName, const string& content)
{
    /* if (mTableFiles.find(tableName) == mTableFiles.end()) return false; */
    currentUpdatingTable[this] = tableName;
    bool updateSucceed = true;

    /**
     * 把现在创建的文件id放在tmpFileIds这个用作log的变量中
     * 我测试ReadTable的结果是这样，每个文件的内容里面不能有
     * 空格，也就是说，要以空格分隔content，以创建多个文件
     */
    istringstream is(content);
    string subContent;
    while (is>>subContent) {
        string fileId = GetFileId();
        updateSucceed &= CreateFile(fileId);
        if (!updateSucceed) return updateSucceed;
        updateSucceed &= WriteToFile(fileId, subContent);
        if (!updateSucceed) return updateSucceed;
        tmpFileIds[this].push_back(fileId);
    }
    return updateSucceed;
}

bool Worker::commit() {
    bool commitSucceed = true;
    FileIds oldFileIds = mTableFiles[currentUpdatingTable[this]];
    /**
     * 先把老的文件删了
     * 再把log里新建的文件更新到mTableFile里
     */
    for (FileIds::iterator it = oldFileIds.begin();
            it != oldFileIds.end();
            ++it) {
        commitSucceed &= DeleteFile(*it);
    }
    mTableFiles[currentUpdatingTable[this]] = tmpFileIds[this];

    /**
     * 清空log
     */
    currentUpdatingTable.erase(this);
    tmpFileIds.erase(this);
    return commitSucceed;
}

bool Worker::rollback() {
    bool rollbackSucceed = true;
    /**
     * 把上一步操作新建的文件删了
     */
    for (FileIds::iterator it = tmpFileIds[this].begin();
            it != tmpFileIds[this].end(); ++it) {
        rollbackSucceed &= DeleteFile(*it);
    }
    /**
     * 清空log
     */
    currentUpdatingTable.erase(this);
    tmpFileIds.erase(this);
    return rollbackSucceed;
}
