#ifndef BUFFER
#define BUFFER

class Buffer
{

  public:
	ifstream fin;
	int mark;
	bool EOFReach = false;
	int line;

	Buffer(string file)
	{
		fin.open(file);
	}

	void Mark()
	{
		mark = fin.tellg();
	}

	void Reset()
	{
		fin.seekg(mark, fin.beg);
	}

	char ReadNextChar()
	{
		char c;
		if(EOFReach)
			return(char(0));

		if(fin.get(c))
		{
			return c;
		}
		else
		{
			EOFReach = true;
			return(char(0));
		}	
	}

	string GetString(int size)
	{
		char c;
		int i;
		char str[100];
		for (i = 0; i < size; ++i)
		{
		
			fin.get(c);
			str[i] = c;
		}
		str[i] = '\0';
		string s(str);
		return s;
	}

	void GetToToken()
	{

		bool seen = false;
		while(true)
		{
			char c = ReadNextChar();
			if(c == ' ' || c == '\n' ||c == '\t' || c == '\r')
			{
				seen = true;
			}
			else
			{
				if(seen == true)
				{
					Reset();
					return;
				}
			}
			Mark();
		}
	}

	string GetTillNonAlpha()
	{
		Mark();
		int i = 0;
		char str[100];
		char c = ReadNextChar();
		while(isalpha(c))
		{
			str[i++] = c;
			c = ReadNextChar();
		}
		str[i] = '\0';
		return string(str);
	}
};

#endif