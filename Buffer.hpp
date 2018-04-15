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
};

#endif