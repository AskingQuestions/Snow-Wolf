#include <cstdio>
#include <iostream>
/*#include <string>
#include "json.hpp"
#include "datastructure.hpp"
#include "virtualdirectory.hpp"
#include "any.hpp"
#include <typeinfo>
#include "system.hpp"
#include <windows.h>*/
#include "includes.hpp"

using namespace std;



int main() {
	System::init();
	cout << System::os.name << " " << System::application.currentApplication;
	DataStructure ds;
	ds["a1"] = string("string");
	ds["a2"] = 20.4223;
	
	ds["a3"] = ds;
	vector<DataStructure> arr;
	arr.push_back(ds);
	arr.push_back(ds);

	ds["a4"] = 3;
	ds["a5"] = 3;
	ds["arr"] = arr;
	//ds["a4"]._<DataStructure>()["struct"] = ds;
	//ds["a4"] = 
	JSON json;
	json.nice = true;
	cout << json.stringify(ds) << endl;
	
	
	DataStructure ds2 = json.parse(json.stringify(ds));
	cout << json.stringify(ds2);
	JSON hello;
	DataStructure dso;
	dso["ko"] = 10;
	cout << hello.stringify(dso);
	
	DataStructure ds3;
	ds3["first"] = 10;
	
	VirtualDirectory vd;
	vd.createFile("", "hello.json", ds3);
	vd.createFolder("", "dir");
	vd.createFile("dir/", "file.json", ds3);
	//vd.find("hello.json");
	DataStructure found = vd.find("dir/file.json");
	
	cout << found["first"]._<int>();
	
	int incre = 0;
	bool stop = false;
	thread myt([&incre, &stop](){
		while (incre < 0xFFFFFFFF) {
			if (stop) {
				incre = -10;
				break;
			}
			incre++;
		}
		return 0;
	});
	char in = ' ';
	while (in != 's') {
		if (in == 'w')
			cout << incre << endl;
		in = getchar();
	}
	stop = true;
	myt.join();
	cout << incre;
	return 0;
}

