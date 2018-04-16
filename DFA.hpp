#ifndef DFAS
#define DFAS

class DFA
{
public:
	int init_s, dead_s, curr_s;
	US<int> states;
	US<int> final_states;
	Table m_table;
	

	void Init(int init_state, int dead_state, US<int> all_states, US<int> final_sts, Table table )
	{
		init_s = init_state;
		dead_s = dead_state;
		curr_s = init_state;
		states = all_states;
		final_states = final_sts;
		m_table = table;
	}

	int CheckTransition(Buffer *buf)
	{
		int m_tok_len = 0;
		bool found_final = false;
		curr_s = init_s;
		(*buf).Mark();
		while(true)
		{
			char c  = (*buf).ReadNextChar();
			// cout << "first " << c << endl;
			curr_s = m_table.ReturnState(curr_s, (int)c);
			// cout <<"second " << curr_s << endl; 
			if(curr_s == dead_s)
			{
				// cout << "third " << found_final <<endl;
				// cout << "fourth " << m_tok_len;
				break;
			}	

			if( final_states.find(curr_s) != final_states.end())
			{
				found_final = true;
			}
			m_tok_len++;
		}

		(*buf).Reset();
		if(found_final == true)
		{
			return m_tok_len;
		}
		else
		{
			cout << "here we are" <<endl;
			return -1;
		}	

	}

};

#endif