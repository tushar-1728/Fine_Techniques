#include <header.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp = fopen("op.txt","w");
	state_t start_state;
	int inp1, inp2, inp3;

	printf("Enter the contents of 8L 5L 3L jug: ");
	scanf("%d %d %d", &inp1, &inp2, &inp3);
	set_state(&start_state, inp1, inp2, inp3);
	state_t goal_state;
	
	printf("Enter the final state: ");
	scanf("%d %d %d", &inp1, &inp2, &inp3);
	set_state(&goal_state, inp1, inp2, inp3);
	// creating and initialising the list
	list_t l;
	init_list(&l);
	// creatint variable temp to store next possible transition state
	state_t temp;
	// boolean variable soln to check if a given present list is solution or not
	int soln = 0;
	// adding start state to list
	add_at_end(&l, &start_state);
	// variable index to remember which transition function has been applied
	int index;

	void (*pour[])(const state_t *src, state_t *dst) = {
		pour_8to5,
		pour_8to3,
		pour_5to8,
		pour_5to3,
		pour_3to8,
		pour_3to5
	};
	int count = 0; // variable to keep count of solutions
	while(l.tail)
	{
		index = l.tail->st.fn_index;
		pour[index](&l.tail->st , &temp);
		if(! is_repeated(&l, &temp))
		{
			add_at_end(&l, &temp);
			soln = are_same(&temp, &goal_state);
			if(soln){ // printing states once solution is found
				soln = 0;
				++count;
				print_to_file(&l,fp);
			}
		}
		else
		{   // checking if tail of l exists and then backtracking
			while(l.tail && ++l.tail->st.fn_index == 6)
			{
					remove_at_end(&l);
			}	
		}
	}
	fprintf(fp,"%d",count);
	fclose(fp);
}
