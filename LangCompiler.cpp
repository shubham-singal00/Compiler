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
#include "Scanner.hpp"
 
#define FOR(i, a, b) for(long long i=a;i<b;i++)

int main(int argc, char *argv[])
{
	if(argc <= 1)
	{
		cout << "error" << endl;
		return 1;
	}

	string fileName( argv[1] );
	Scanner::LangScanner(fileName);
	
	return 0;
}
