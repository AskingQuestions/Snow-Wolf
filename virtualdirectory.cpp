//#include "VirtualDirectory.hpp"
using namespace std;

string VirtualDirectory::getPath(string path, string name) {
	string rtn = path;
	if (path == "") return name;
	if (path[path.length()-1] == '/')
		rtn += name;
	else
		rtn += "/"+name;
	return rtn;
}

void VirtualDirectory::createFolder(string path, string name) {
	VD_item i;
	i.name = name;
	i.path = path;
	i.type = 1;
	folders[getPath(path, name)] = i;
}

void VirtualDirectory::createFile(string path, string name, DataStructure content) {
	VD_item i;
	i.name = name;
	i.path = path;
	i.type = 2;
	i.contents = content;
	
	files[getPath(path, name)] = i;
}

void VirtualDirectory::editFile(string path, DataStructure content) {
	files[path].contents = content;
}

void VirtualDirectory::deleteFolder(string path) {
	delete &folders[path];
}

void VirtualDirectory::deleteFile(string path) {
	delete &files[path];
}

DataStructure VirtualDirectory::find(string path) {
	if (files.count(path) > 0)
		return files[path].contents;
	DataStructure data;
	return data;
}