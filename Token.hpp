#ifndef TOKEN
#define TOKEN

class Token
{
public:
	string m_name;
	string m_value;
	int m_line;
	Token(string name, string value, int line)
	{
		m_name = name;
		m_value = value;
		m_line = line;
	}
	
};

class Data
{
public:
	int key = 100;
	std::map<string, int> symbol_table;
	std::vector<Token> tok;
	
};

#endif