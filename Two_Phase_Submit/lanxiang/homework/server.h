#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <map>
#include <vector>

#include "worker.h"

namespace homework
{

class Server
{
public:
    typedef std::vector<WorkerPtr> WorkerPtrs;
    typedef std::vector<uint8_t> WorkerIds;
    Server();

    ~Server();

    bool UpdateTable(const std::string& content, const std::string& tableName);

private:
    std::map<uint8_t, WorkerPtr> mWorkers;
    std::map<std::string, std::vector<uint8_t> > mTables;
};
}

#endif
