//#include "json.hpp"
using namespace std;


JSON::JSON(bool pretty, string indentor) {
	nice = pretty;
	indent = indentor;
}

string JSON::stringify(DataStructure ds) {
	return recur(ds, 1);
}

DataStructure JSON::parse(string input) {
	return reparse(input);
}

template <typename T>
string JSON::toString(T val) {
	stringstream stream;
	stream << val;
	return stream.str();
}

string JSON::indenter(int count) {
	string rtn = "";
	for (int i = 0; i < count; i++)
		rtn += indent;
	return rtn;
}

string JSON::recur(DataStructure ds, int ind) {
	string built = "{";
	if (nice)
		built += "\n";
	auto c = ds.rbegin();
	string k = c->first;
	for (auto i = ds.begin(); i != ds.end(); i++) {
		string key;
		if (nice) {
			built += indenter(ind);
			key = "\""+i->first+"\": ";
		}else {
			key = "\""+i->first+"\":";
		}
		
		built += key;
		Any value = i->second;
		if (value.is<int>()) {
			built += toString(value._<int>());
		}else if (value.is<double>()) {
			built += toString(value._<double>());
		}else if (value.is<bool>()) {
			built += (value._<bool>()) ? "true" : "false";
		}else if (value.is<string>()) {
			built += "\""+value._<string>()+"\"";
		}else if (value.is<DataStructure>()) {
			built += recur(value._<DataStructure>(), ind+1);
		}else if (value.is<vector<int>>()) {
			built += "["+vectorList<int>(value._<vector<int>>())+"]";
		}else if (value.is<vector<bool>>()) {
			built += "["+vectorList<bool>(value._<vector<bool>>())+"]";
		}else if (value.is<vector<double>>()) {
			built += "["+vectorList<double>(value._<vector<double>>())+"]";
		}else if (value.is<vector<string>>()) {
			built += "["+vectorList<string>(value._<vector<string>>())+"]";
		}
		
		if (k != i->first)
			built += ",";
		if (nice)
			built += "\n";
	}
	if (!nice) {
		built += "}";
	}else{
		built += indenter(ind-1)+"}";
	}
	return built;
}

template <typename T>
string JSON::vectorList(vector<T> vl) {
	string rtn = "";
	for (int i = 0; i < vl.size(); i++) {
		rtn += toString(vl[i]);
		if (i != vl.size()-1)
			rtn += ",";
	}
	return rtn;
}


DataStructure JSON::reparse(string input) {
	input.erase(input.begin());
	input.erase(input.end()-1);
	regex re("\"(.*?)\"");
	DataStructure ds;
	vector<string> split = splitString(input, ',');
	for (int i = 0; i < split.size(); i++) {
		vector<string> kv = splitString(split[i], ':');
		smatch sm;
		regex_search(kv[0], sm, re);
		ds[sm[1]] = fromString(kv[1]);
	}
	
	return ds;
}

vector<string> JSON::splitString(string src, char delim) {
	vector<string> rtn;
	string current = "";
	int scope = 0;
	for (int i = 0; i < src.length(); i++) {
		if (src[i] == delim && scope == 0) {
			rtn.push_back(current);
			current = "";
			continue;
		}else{
			if (src[i] == '[' || src[i] == '{') scope += 1;
			if ((src[i] == ']' || src[i] == '}')) scope -= 1;
		}
		current += src[i];
		if (i == src.length() - 1) {
			rtn.push_back(current);
		}
	}
	return rtn;
}

string JSON::replaceString(string src) {
	string rtn;
	bool scope = false;
	for (int i = 0; i < src.length(); i++) {
		bool add = true;
		if (src[i] == '"') scope = !scope;
		if ((src[i] == ' ' || src[i] == '\n' || src[i] == '\t') && scope == false) {
			add = false;
		}
		if (add)
			rtn += src[i];
	}
	return rtn;
}

Any JSON::fromString(string value) {
	value = replaceString(value);
	string valtype = typeString(value);
	if (valtype == "string")
		{
			string t = value;
			t.erase(t.begin());
			t.erase(t.end()-1);
			Any rtn = t;
			return rtn;
		}
	else if(valtype == "datastructure")
		{
			Any rtn = reparse(value);
			return rtn;
		}
	else if(valtype == "array")
		{
			return arrayFromList(value);
		}
	else if(valtype == "boolean")
		{
			if (value == "true") {
				bool t = true;
				Any rtn = t;
				return rtn;
			}else if(value == "false"){
				bool t = false;
				Any rtn = t;
				return rtn;
			}
		}
	else if(valtype == "integer")
		{
			int t = atoi(value.c_str());
			Any rtn = t;
			return rtn;
		}
	else if(valtype == "double")
		{
			double t = atof(value.c_str());
			Any rtn = t;
			return rtn;
		}
	
	return Any("Unknown");
}

string JSON::typeString(string value) {
	string rtn;
	value = replaceString(value);
	switch (value[0]) {
		case '"': 
		{
			rtn = "string";
			break;
		}
		case '{':
		{
			rtn = "datastructure";
			break;
		}
		case '[':
		{
			rtn = "array";
			break;
		}
		default:
		{
			if (value == "true") {
				rtn = "boolean";
			}else if(value == "false"){
				rtn = "boolean";
			}else if (isInteger(value)){
				rtn = "integer";
			}else if(isDouble(value)){
				rtn = "double";
			}
		}
	}
	return rtn;
}

template<typename T>
vector<T> JSON::stringToArray(string vals) {
	vector<T> rtn;
	vector<string> split = splitString(vals, ',');
	for (int i = 0; i < split.size(); i++) {
	cout << split[i] << endl;
		rtn.push_back(fromString(split[i])._<T>());
	}
	return rtn;
}

Any JSON::arrayFromList(string list) {
	string vals = list;
	vals.erase(vals.begin());
	vals.erase(vals.end()-1);
	vector<string> split = splitString(vals, ',');
	if (split.size() > 0) {
		string arrayType = typeString(split[0]);
		Any rtn;
		string t = vals;
		if (arrayType == "string") {
			rtn = stringToArray<string>(t);
		}else if (arrayType == "integer") {
			rtn = stringToArray<int>(t);
		}else if (arrayType == "double") {
			rtn = stringToArray<double>(t);
		}else if (arrayType == "datastructure") {
			rtn = stringToArray<DataStructure>(t);
		}else if (arrayType == "boolean") {
			rtn = stringToArray<bool>(t);
		}else if (arrayType == "double") {
			rtn = stringToArray<int>(t);
		}else if (arrayType == "array") {
			//rtn = stringToArray<>(t);
		}
		
		return rtn;
	}else{
		return Any(false);
	}
}

bool JSON::isInteger(const string & s) {
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   char * p ;
   strtol(s.c_str(), &p, 10) ;
   return (*p == 0) ;
}

bool JSON::isDouble(const string & s) {
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   char * p ;
   strtod(s.c_str(), &p) ;
   return (*p == 0) ;
}
