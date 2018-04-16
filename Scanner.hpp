#ifndef SCANNER
#define SCANNER

namespace Scanner
{
	//std::vector<string> keywords = { "else", "new", "return", "elsif", "not", "of", "exit", "or", "and", "for", "out", "array", "function", "at", "begin", "then", "if", "procedure", "type", "case", "in", "is", "use", "declare", "range", "record", "when", "delta", "loop", "while", "digits", "with", "do", "xor"}
	// std::vector<string> keywords = { "integer", "character", "string", "float", "boolean", "if", "elsif", "else", "while", "do", "is", "begin", "procedure", "loop", "array", "case"};
	void CreateIDDFA();
	void CreateSingleDFA();
	void CreateDoubleDFA();
	void CreateComDFA();
	Token GetNextToken(Buffer *buf);
	DFA identifiers;
	DFA string_lit;
	DFA int_lit;
	DFA float_lit;
	DFA doub;
	DFA single;
	DFA comments;

	int ST_ST = 0;
	int DEAD_ST = -1;
	US <string> keywords = {"int", "float", "string", "bool", "while", "if", "else", "true", "false"};
	
	
	void LangScanner(string fil)
	{

		Buffer buf(fil); 	
		int tok_len;
		
		CreateIDDFA();
		CreateComDFA();
		CreateSingleDFA();
		CreateDoubleDFA();

		while(buf.EOFReach == false)
		{
			Token t = GetNextToken(&buf);
			cout << "!" << t.m_name << " " << t.m_value << "!" << endl;
			if(t.m_name == "")
			{
				cout << "!!" << t.m_value << "!" << endl;
			buf.GetToToken();
			}
		}
	}

	Token GetNextToken(Buffer *buf)
	{
		cout << endl << endl << "hjere" << endl;
		string s = (*buf).GetTillNonAlpha();
		cout << s << endl;
		if(keywords.find(s) != keywords.end())
		{
			cout << s << endl;
			Token t("keyword",s);
			return t; 
		}
		else
		{
			(*buf).Reset();
		}
	
		int l = identifiers.CheckTransition(buf);
		if(l != -1)
		{
			s = (*buf).GetString(l);
			cout << s << endl;
			Token t("identifier",s);
			return t;	
		}

		l = comments.CheckTransition(buf);
		if(l != -1)
		{
			s = (*buf).GetString(l);
			cout << s << endl;
			Token t("comment",s);
			return t;	
		}

		l = doub.CheckTransition(buf);
		if(l != -1)
		{
			s = (*buf).GetString(l);
			cout << s << endl;
			Token t("double",s);
			return t;	
		}

		l = single.CheckTransition(buf);
		if(l != -1)
		{
			s = (*buf).GetString(l);
			cout << s << endl;
			Token t("single",s);
			return t;	
		}

		Token t("", "value");
		return t;
	}



	void CreateIDDFA()
	{
		string first_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		string follow_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
		int FIRST_STATE = 1;
		int FINAL_STATE = 2;
		Table tab;
		US <int> states = {0, 1, 2}; 
		US <int> fin_states = {1, 2}; 
		tab.InsertState(ST_ST, first_chars, FIRST_STATE, false);
		tab.InsertState(FIRST_STATE, follow_chars, FINAL_STATE, false);
		tab.InsertState(FINAL_STATE, follow_chars, FINAL_STATE, false);

		identifiers.Init(ST_ST, DEAD_ST, states, fin_states, tab);

	}

	void CreateComDFA()
	{
		string end_comment = "\n";
		int FIRST_HY = 1;
		int SEC_HY = 2;
		Table tab;
		US <int> states = {0, 1, 2 }; 
		US <int> fin_states = {2}; 
		tab.InsertState(ST_ST, "-", FIRST_HY, false);
		tab.InsertState(FIRST_HY, "-", SEC_HY, false);
		tab.InsertState(SEC_HY, "\n", SEC_HY, true);

		comments.Init(ST_ST, DEAD_ST, states, fin_states, tab);
	}

	void CreateSingleDFA()
	{
		string del = "*+-/%<>!?:(){}[]=;";
		int FIRST_CHAR = 1;
		Table tab;
		US <int> states = {0, 1}; 
		US <int> fin_states = {1}; 
		tab.InsertState(ST_ST, del, FIRST_CHAR, false);
		// for(int i=0; i<2; i++)
		// {
		// 	for(int j=0; j<128; j++)
		// 		cout << tab.m_state[i][j] << " " ;
		// 	cout << endl << endl;
		// }	

		single.Init(ST_ST, DEAD_ST, states, fin_states, tab);
	}

	void CreateDoubleDFA()
	{
		int FIRST_EQUAL = 1;
		int FINAL = 2;
		int FIRST_AND = 3;
		int FIRST_OR = 4;
		string first_chars = "=:<>!";
		Table tab;
		US <int> states = {0, 1, 2, 3, 4}; 
		US <int> fin_states = {2}; 
		tab.InsertState(ST_ST, first_chars, FIRST_EQUAL, false);
		tab.InsertState(ST_ST, "&", FIRST_AND, false);
		tab.InsertState(ST_ST, "|", FIRST_OR, false);
		tab.InsertState(FIRST_EQUAL, "=", FINAL, false);
		tab.InsertState(FIRST_AND, "&", FINAL, false);
		tab.InsertState(FIRST_OR, "|", FINAL, false);

		// for(int i=0; i<2; i++)
		// {
		// 	for(int j=0; j<128; j++)
		// 		cout << tab.m_state[i][j] << " " ;
		// 	cout << endl << endl;
		// }	

		doub.Init(ST_ST, DEAD_ST, states, fin_states, tab);
	}
}
#endif