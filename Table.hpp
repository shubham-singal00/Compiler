#ifndef TABLE
#define TABLE

class Table
{
public:

	int m_state[10][128];

	Table()
	{
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 128; ++j)
			{
				m_state[i][j] = -1;
			}
		}
	}
	
};

#endif