
#ifndef DFA
#define DFA



class DFA
{
public:
	int init_s, dead_s, curr_s;
	US<int> states, final_states;
	Table table;
	
	DFA(int init_state, int curr_state, int dead_state, US<int> all_states, US<int> final_sts )
	{
		init_s = init_state;
		dead_s = dead_state;
		curr_s = curr_state;
		states = all_states;
		final_states = final_sts;
	}

	
	
};

#endif