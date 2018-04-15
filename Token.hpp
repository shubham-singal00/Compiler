#ifndef TOKEN
#define TOKEN

class Token
{
public:
	string m_name;
	int m_entry;
	string m_value;
	Token(string name, string value, int entry)
	{
		m_name = name;
		m_value = value;
		m_entry = entry;
	}
	
};

#endif