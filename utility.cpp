#include <iostream>
#include "utility.h"

using namespace util;

//-----------------------------------------
int util::random(int min, int max){
	int range = max - min;
	return std::rand() % range + min;
}

//-----------------------------------------
void util::normalize(string& str){
	for(int i = 0; i < str.size(); i++)
		if(str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
}

//-----------------------------------------
void util::removeBlanks(string& str){
	for(int i = 0; i < str.size(); i++)
		if(str[i] == ' ') str.erase(i, 1);
}

//-----------------------------------------
string* util::splitTwo(string str, string sep){
	string* strA = new string[2];

	int pos = str.find(sep);
	if(pos != string::npos){
		strA[0] = str.substr(0, pos);
		strA[1] = str.substr(pos + 1, str.size() - pos);
	}

	return strA;
}
