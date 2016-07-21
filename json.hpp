#ifndef json_def
#define json_def

#include <regex>
#include <sstream>

using namespace std;

class JSON {
public:
	/**
	* This is used to define whether or not the json output should be pretty. 
	*/
	bool nice;
	/**
	* \brief The indent string.
	* 
	* This is inserted to structure the json.
	*/
	string indent;
	
	JSON(bool pretty = true, string indentor = "   ");
	
	/**
	* \brief Turns any DataStructure instance into a json formated string.
	*/
	string stringify(DataStructure ds);
	/**
	* \brief Turns any json formated string into a DataStructure instance.
	*/
	DataStructure parse(string input);
	
	
private:
	template <typename T>
	string toString(T val);
	
	string indenter(int count);
	
	string recur(DataStructure ds, int ind);
	
	template <typename T>
	string vectorList(vector<T> vl);
	
	DataStructure reparse(string input);
	
	vector<string> splitString(string src, char delim);
	
	string replaceString(string src);
	
	Any fromString(string value);
	
	string typeString(string value);
	
	template<typename T>
	vector<T> stringToArray(string vals);
	
	Any arrayFromList(string list);
	
	bool isInteger(const string & s);
	
	bool isDouble(const string & s);
};

#include "json.cpp"

#endif