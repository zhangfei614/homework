#include "server.h"
#include <string>
#include <cstdlib>
#include <algorithm>


#define WORKER_NUMER 10
#define COPY_NUMBER 3
#define SPILT_LENGTH 20

using namespace std;
using namespace homework;


std::vector<std::string> split(const std::string &s,int slength) {
    std::vector<std::string> elems;
	for(int i=0;i<s.size();i+=slength){
		elems.push_back(s.substr(i,slength));
	}
    return elems;
}

// Server::Server(){
// 	for(int i=0;i<WORKER_NUMER;i++){
// 		WorkerPtr p = new Worker(i);
// 		mWorkers[i]=p;
// 	}
// }
// Server::~Server(){
// 	for(int i=0;i<WORKER_NUMER;i++){
// 		free(mWorkers[i]);
// 	}
// }
bool Server::UpdateTable(const string& tableName, const string& content)
{
	vector<uint8_t> tWorkers = mTables[tableName];
	if(tWorkers.empty()){
		//目前没有当前表，后面直接返回false，不需要加入。
		// //分配到COPY_NUMBER个Worker上
		// while(tWorkers.size()<COPY_NUMBER){
		// 	uint8_t t =(uint8_t)(rand()%(WORKER_NUMER));
		// 	if(std::find(tWorkers.begin(),tWorkers.end(),t)!=tWorkers.end()){
		// 		continue;
		// 	}else{
		// 		tWorkers.push_back(t);
		// 	}
		// }
		// //写入到Workers上
		// for(int i=0;i<tWorkers.size();i++){
		// 	uint8_t t = tWorkers[i];
		// 	if((mWorkers[t]->UpdateTable(tableName,content)))
		// 		cout<<"Added "<<tableName<<" to "<<t<<endl;
		// }
		// //修改meta信息
		// mTables[tableName]=tWorkers;
		return false;
	}
	
	map<uint8_t,string> log;
	bool rollback = false;
	for(int i=0;i<tWorkers.size();i++){
		uint8_t t = tWorkers[i];
		
		//读原始值
		string oldValue;
		if(!(mWorkers[t]->ReadTable(tableName,oldValue))){
			// cout<<"server:readTable error in table"<<t<<endl;
			rollback = true;
			break;
		}
		// cout<<"server:From table"<<t<<" read:"<<oldValue<<endl;
		log[t]=oldValue;
	}
	// for(map<uint8_t,string>::iterator it=log.begin();it!=log.end();it++){
	// 		cout<<it->first<<":"<<it->second<<endl;
	// }
	for(int i=0;i<tWorkers.size();i++){
		uint8_t t = tWorkers[i];
		//更新新值
		if(!(mWorkers[t]->UpdateTable(tableName,content))){
			// cout<<"server:updateTable error in table"<<t<<endl;
			rollback = true;
			break;
		}
		// cout<<"server:Update table"<<t<<" to:"<<content<<endl;
		
	}
	if(rollback){
		// cout<<"rollback"<<endl;
		for(map<uint8_t,string>::iterator it=log.begin();it!=log.end();it++){
			if(!(mWorkers[it->first]->UpdateTable(tableName,it->second))){
				// cout<<"server:rollback error in table"<<it->first<<endl;
				return false;
			}
		}
		return false;
	}
	log.clear();
	return true;
}


bool Worker::UpdateTable(const string& tableName, const string& content)
{
	//按照文件长度进行切分。
	vector<string> newFileId;
	vector<string> spContent = split(content,SPILT_LENGTH);
	int size = spContent.size();
	for(int i=0;i<size;i++){		//创建新的文件
		string fileId = GetFileId();
		if(!CreateFile(fileId)){
			// cout<<"worker:createFile error"<<endl;
			return false;
		}
		if(!WriteToFile(fileId,spContent[i])){
			// cout<<"worker:writeToFile error"<<endl;
			return false;
		}
		newFileId.push_back(fileId);
	}

	//更新meta信息
	vector<string> oldFileId = mTableFiles[tableName];
	mTableFiles[tableName] = newFileId;
	
	size = oldFileId.size();		//删除原有文件
	for(int i=0;i<size;i++){
		if(!DeleteFile(oldFileId[i])){
			// cout<<"worker:deleteFile error"<<endl;
			return false;
		}
	}
	
	return true;
}


