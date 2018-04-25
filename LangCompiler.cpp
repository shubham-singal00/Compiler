using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cassert>
#define US unordered_set 
#define ll long long
#define ss second
#define ff first
#define FastIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define pb push_back
#include "Buffer.hpp"
#include "Table.hpp"
#include "DFA.hpp"
#include "Token.hpp"
#include "paser.hpp"
#include "Scanner.hpp"
 
#define FOR(i, a, b) for(long long i=a;i<b;i++)


string DATATYPE(string k ,string s){
	if(k=="keyword")
		{
			if(s=="if")
				return "IF";
			if(s=="else")
				return "ELSE";
			if(s=="while")
				return "WHILE";
			if(s=="int" || s=="float" || s=="long" || s=="char" || s=="double")
				return "TYPE";
			if(s=="true")
				return "TRUE";
			if(s=="false")
				return "FALSE";

		}
	if(k=="identifier")
		return "ID";
	if (k=="comment")
		return "";
	if(k=="single"){
		if(s == "<" || s == ">" || s == "<=" || s == ">=" || s == "!=" || s == "==" )
			return "REL_OPT";
		if(s=="||")
			return "OR";
		if(s=="&&")
			return "AND";
		if(s=="!")
			return "NOT";
		else
			return s;
	}
		
	
	if(k=="integer")
		return "DIGIT";
	//if(s == '+' || s == '-' || s=='*' || s=='%'){}
}
int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		cout << "error" << endl;
		return 1;
	}

	string fileName( argv[1] );
	Data tokens = Scanner::LangScanner(fileName);
	//
/* {int a 10;}


while(a<=20){
	a=a+2;
	b=b-1;
}
*/
	string fin = "";
	for (int i = 0; i < tokens.tok.size(); ++i)
	{
			cout << "name: " << tokens.tok[i].m_name;
			cout << " value:" << tokens.tok[i].m_value;
			cout <<  " Line: " << tokens.tok[i].m_line;
			cout << " tok id: " << tokens.symbol_table[tokens.tok[i].m_value] << endl;	
			fin += " " + DATATYPE(tokens.tok[i].m_name,tokens.tok[i].m_value) + " ";
			
	}
	fin += "$";
	Parser p(fin);
	cout<<fin<<endl;
	// Parser P(" { TYPE ID = DIGIT ; } WHILE ( ID REL_OPT DIGIT ) { ID = ID + DIGIT ; } $");
	// P.printcsv();
	// string val = "r32"; 
	// int num = stoi( string(val.begin()+1, val.end()));
	// cout << num << endl;
	return 0;
}
