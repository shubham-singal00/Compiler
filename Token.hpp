#ifndef TOKEN
#define TOKEN

class Token
{
public:
	string m_name;
	string m_value;
	Token(string name, string value)
	{
		m_name = name;
		m_value = value;
	}
	
};

class Data
{
public:
	int key = 100;
	std::map<int, Token> symbol_table;
	std::vector<Token> tok;
	
};

#endif