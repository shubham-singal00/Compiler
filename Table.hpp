#ifndef TABLE
#define TABLE

#define MAXST 10
#define CHARS 128
class Table
{
public:

	int m_state[MAXST][CHARS];

	Table()
	{
		for (int i = 0; i < MAXST; ++i)
		{
			for (int j = 0; j < CHARS; ++j)
			{
				m_state[i][j] = -1;
			}
		}
	}

	void InsertState(int first_state, string trans, int fin_state, bool except)
	{
		if(except == true)
		{
			for (int j = 0; j < CHARS; ++j)
			{
				m_state[first_state][j] = fin_state;
			}			

			for(auto it = trans.begin(); it != trans.end(); it++)
			{
				m_state[first_state][(int)*it] = -1;
			}		
		}
		else
		{
			for(auto it = trans.begin(); it != trans.end(); it++)
			{
				// cout << (char)*it << " " << (int)*it << " " ;
				m_state[first_state][(int)*it] = fin_state;
			}		
			// cout << endl << endl << endl << endl;
		}
		// for(int i = 0; i < 10; i++)
		// {
		// 	for (int j = 0; j < 128; j++)
		// 	{
		// 		cout << m_state[i][j] << " ";
		// 	}
		// 	cout << endl << endl << endl << endl;
		// }
	}

	int ReturnState(int cur_state, char transition)
	{
		return m_state[cur_state][transition];
	}
	
};

#endif