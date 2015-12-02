#include "server.h"

#define SPILT_LENGTH 20

using namespace std;
using namespace homework;

bool Server::UpdateTable(const string& tableName, const string& content)
{
	//每一个worker都写入
	vector<WorkerPtr> allWorkerPtrs;
	vector<size_t> allWorkers;
	for(std::map<size_t, WorkerPtr>::iterator it = mWorkers.begin(); it != mWorkers.end(); ++it){
    	allWorkerPtrs.push_back(it->second);
   		allWorkers.push_back(it->first);
	}
	
	//更新过程
	int size = allWorkerPtrs.size();
	bool rollback = false;
	int i;
	for(i=0;i<size;i++){
		if(!(allWorkerPtrs[i]->UpdateTable(tableName,content))){
			rollback = true;
			// cout<<"Worker"<<i<<" failed"<<endl;
			// break;
		}
		// cout<<"Worker"<<i<<" success"<<endl;
	}
	
	//如果需要回滚，对之前的workers进行回滚
	if(rollback){
		for(i=0;i<size;i++){
			if(!(allWorkerPtrs[i]->rollback(tableName))){
				return false;
			}
			cout<<"Worker"<<i<<" rollback"<<endl;
		}
		return false;
	}
	
	//如果不需要回滚，则提交事务。
	for(i=0;i<size;i++){
		if(!(allWorkerPtrs[i]->commit())){
			return false;
		}
		cout<<"Worker"<<i<<" commit"<<endl;
	}
	
	//更新meta信息
	mTables[tableName]=allWorkers;
	return true;
}

bool Worker::UpdateTable(const string& tableName, const string& content)
{
	//记录原有文件
	log = mTableFiles[tableName];
	
	//分割文件，然后建立新的文件
	vector<string> newFileIds;
	vector<string> spContent = split(content,SPILT_LENGTH);
	int size = spContent.size();
	for(int i=0;i<size;i++){
		string fileId = GetFileId();
		if(!CreateFile(fileId)){
			return false;
		}
		newFileIds.push_back(fileId);
		//更新meta信息
		mTableFiles[tableName] = newFileIds;
		
		if(!WriteToFile(fileId,spContent[i])){
			return false;
		}
	}
	
	
	//返回正确结果
	return true;
}

bool Worker::commit(){
	//把原来的文件删除
	int size = log.size();
	for(int i=0;i<size;i++){
		if(!DeleteFile(log[i])){
			return false;
		}
	}
	log.empty();
	return true;
}

bool Worker::rollback(const std::string& tableName){
	std::vector<std::string> newFileIds;
	newFileIds = mTableFiles[tableName];
	
	mTableFiles[tableName]=log;
	log.empty();
	
	for(int i=0;i<newFileIds.size();i++){
		if(!DeleteFile(newFileIds[i])){
			return false;
		}
	}
	return true;
}

std::vector<std::string> Worker::split(const std::string &s,int slength) {
    std::vector<std::string> elems;
	for(int i=0;i<s.size();i+=slength){
		elems.push_back(s.substr(i,slength));
	}
    return elems;
}