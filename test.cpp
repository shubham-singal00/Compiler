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

int main()
{
	unordered_set<int> us = {1,2,3};

	if(us.find(9) != us.end())
		cout << "t" << endl;
	else
		cout << "f" << endl;
}