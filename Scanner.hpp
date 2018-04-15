#ifndef SCANNER
#define SCANNER

namespace Scanner
{
	//std::vector<string> keywords = { "else", "new", "return", "elsif", "not", "of", "exit", "or", "and", "for", "out", "array", "function", "at", "begin", "then", "if", "procedure", "type", "case", "in", "is", "use", "declare", "range", "record", "when", "delta", "loop", "while", "digits", "with", "do", "xor"}
	// std::vector<string> keywords = { "integer", "character", "string", "float", "boolean", "if", "elsif", "else", "while", "do", "is", "begin", "procedure", "loop", "array", "case"};

	// std::map<int, string> symbolTable;
	int key = 100;

	void LangScanner(string fil)
	{
		Buffer buf(fil);
		string s = buf.GetString(12);
		cout << s << endl;
		US <int> states = { 1,2,3};
		Table tab;
		cout << tab.m_state[1][3];		
	}
}
#endif