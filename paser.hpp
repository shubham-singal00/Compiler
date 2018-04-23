#ifndef PARSER
#define PARSER
#include "parsetree.hpp"
#include "productionsave.hpp"
#include "Token.hpp"
const int N = 1e3;
#include <string> 
#include <map>
map < string , int> nmtocol;


string movestuff[N][N];



class Parser {
public:
	int errorcount = 0;
	string input;
	stack <int> STACKList;
	stack < string > SymStack;
	string col[N];
	map <string,bool> gotoornot;
	string colid[N];
	int prodn[N];
	std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
	{
	    std::vector<std::string>   result;
	    std::string                line;
	    if( std::getline(str,line) ){
		    cout << "GIVINLIN" << endl << line << endl;

		    std::stringstream          lineStream(line);
		    std::string                cell;

		    while(std::getline(lineStream,cell, ','))
		    {
		        result.push_back(cell);
		    }
		    if (!lineStream && cell.empty())
		    {
		        result.push_back("");
		    }
		    return result;
	    	
	    }
	    else
	    	return result;
	}

	// read csv
	Parser(string toBeParsed) {
		input = toBeParsed;
		ifstream fin;
		fin.open("parsing-table.csv");
		// cout << "WHAT" << endl;
		auto ans = getNextLineAndSplitIntoTokens(fin);
		int k = 0;
		bool gorn = 0;
		for(auto x: ans){
			if(x[0] == '\''){
				x = string(x.begin()+1, x.end()-1);
				cout << x << endl;
			}
			nmtocol[x] = k-1;
			gotoornot[x] = gorn;
			if(x[0] == '$') 
				gorn = false;
			col[k++] = x;
			if(x != "")
			cout << x << endl;		
		}
		int rowreadin = 1;
		while(true)
		{
			k = 0;
			int colreadin = 0;
			ans = getNextLineAndSplitIntoTokens(fin);
			if(ans.size() == 0) 
				break;
			for(auto x: ans)
			{
				if(k == 0)
				{
					k++;
					prodn[rowreadin] = stoi(x)+1;

				}
				else{
					movestuff[rowreadin][colreadin++]  = x;
				}

			}
			rowreadin++;
		}
		printcsv();
		startparsin(toBeParsed);
	}
	void printcsv()
	{
		// for(int i=0;i<7;i++) 
		// 	cout << setw(10) << i << " " << col[i] ;
		// cout << endl;
		// for(int i=1;i<=7;i++){
		// 	cout << setw(10) << prodn[i];
		// 	for(int j=0;j<7;j++)
		// 		cout << setw(10) << i << "x"<< movestuff[i][j] << "x"<<j;
		// 	cout << endl;		
		// }
	}
	void startparsin(string toBeParsed)	
	{
		prods P;
		istringstream streamofinput(toBeParsed);
		int statestate = 0;
		string loookahead = "";
		STACKList.push(statestate);
		int parsedtill = -1;
		streamofinput >> loookahead ;
		while( true )
		{
			// cout << loookahead << endl;
			int next = nmtocol[string(loookahead)];
			int toppostack = STACKList.top() + 1;
			if(gotoornot[string(loookahead)] == true)
			{
				STACKList.pop();
				if(movestuff[toppostack][next].size() == 0)
				{
					errormode();
					return;
				}
				STACKList.push(stoi(movestuff[toppostack][next]));
				continue;
			}
			cout << loookahead << " " << toppostack << " " << next <<  endl;
			// Read some mvoe[][] s() or r()
			string next_move = movestuff[toppostack][next];
			cout << next_move << endl; 
			if(next_move == "")
			{
				cout << endl << endl;
				if( errormode() == false){
					cout << "na baba na, na recover kar sakte" << endl;
					return;
				}
				cout << endl << endl;
				continue;
			}
			if(next_move[0] == 'a')
			{
				cout << "YAY" << endl;
				return ;
			}
			if(next_move[0] == 's')
			{
				//Handle shift
				int num = stoi( string(next_move.begin()+1, next_move.end()));
				//Shift is when consume input literal and then 
				// push production 'x's  on the -num
				STACKList.push(num);
				SymStack.push(loookahead);
				if( ! (streamofinput >> loookahead))
				{
					//Reached eof
					break; 
				}
			}
			else
			{

				int num = stoi( string(next_move.begin()+1, next_move.end()));
				rule used_rule = P.rulenumber[num+1];
				P.printrule(used_rule);
				cout << used_rule.ss.size() << endl;
				cout << STACKList.size() << endl;cout << SymStack.size() << endl;
				for(int i =0; i < used_rule.ss.size(); i++){
				
				STACKList.pop();	
				SymStack.pop();
				}
				auto newtop = STACKList.top() + 1;
				string next_move = movestuff[newtop][nmtocol[used_rule.ff]];
				if(next_move == "")
				{
					cout << endl << endl;
					if( errormode() == false){
						cout << "na baba na, na recover kar sakte" << endl;
						return;
					}
					cout << endl << endl;
					continue;
				}
				STACKList.push(stoi(movestuff[newtop][nmtocol[used_rule.ff]]));
				SymStack.push(used_rule.ff);
				//handle reduc
			}

		}
	}

	bool errormode()
	{
		errorcount ++ ;
		cout << "NOOOOOOOOO" ;
		// pop
		if(SymStack.size() == 0) 
			return false;
		STACKList.pop();
		SymStack.pop();
		return true;

	}

};



#endif