#ifndef SCANNER
#define SCANNER

namespace Scanner
{
	//std::vector<string> keywords = { "else", "new", "return", "elsif", "not", "of", "exit", "or", "and", "for", "out", "array", "function", "at", "begin", "then", "if", "procedure", "type", "case", "in", "is", "use", "declare", "range", "record", "when", "delta", "loop", "while", "digits", "with", "do", "xor"}
	// std::vector<string> keywords = { "integer", "character", "string", "float", "boolean", "if", "elsif", "else", "while", "do", "is", "begin", "procedure", "loop", "array", "case"};
	
	void CreateDFAS();
	DFA identifiers;
	DFA string_lit;
	DFA int_lit;
	DFA float_lit;
	DFA del_op;
	DFA comments;

	int ST_ST = 0;
	int DEAD_ST = -1;

	std::map<int, string> symbolTable;
	int key = 100;

	void LangScanner(string fil)
	{

		int tok_len;
		Buffer buf(fil); 	
		
		CreateDFAS();
		tok_len= identifiers.CheckTransition(&buf);
		string s = buf.GetString(tok_len);
		cout << endl << s <<endl;
	}

	void CreateDFAS()
	{
		string first_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		string follow_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
		int FIRST_STATE = 1;
		int FINAL_STATE = 2;
		Table tab;
		US <int> states = {0, 1, 2}; 
		US <int> fin_states = {1, 2}; 
		tab.InsertState(ST_ST, first_chars, FIRST_STATE);
		tab.InsertState(FIRST_STATE, follow_chars, FINAL_STATE);
		tab.InsertState(FINAL_STATE, follow_chars, FINAL_STATE);

		identifiers.Init(ST_ST, DEAD_ST, states, fin_states, tab);
	}
}
#endif