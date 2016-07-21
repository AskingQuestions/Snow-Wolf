#ifndef VirtualDirectory_def
#define VirtualDirectory_def

#include <map>
#include <string>
#include "datastructure.hpp"

using namespace std;

struct VD_item {
	string name;
	string path;
	int type;
	DataStructure contents;
};

class VirtualDirectory {
public:
	/**
	*
	*/
	void createFolder(string path, string name);
	
	/**
	*
	*/
	void deleteFolder(string path);
	
	/**
	*
	*/
	DataStructure find(string path);
	
	/**
	*
	*/
	void createFile(string path, string name, DataStructure content);
	
	/**
	*
	*/
	void deleteFile(string path);
	
	/**
	*
	*/
	void editFile(string path, DataStructure content);
	
	/**
	*
	*/
	//string[] listFolder(string path);
	
	/**
	*
	*/
	void saveIntoFile(string path) {
		
	}
	
	/**
	*
	*/
	void loadFromFile(string path) {
	
	}
	
	/**
	*
	*/
	void saveIntoFolder(string path) {
	
	}
	
	/**
	*
	*/
	void loadFromFolder(string path) {
	
	}
private:
	string getPath(string path, string name);
	map<string, VD_item> files;
	map<string, VD_item> folders;
};

#include "virtualdirectory.cpp"

#endif