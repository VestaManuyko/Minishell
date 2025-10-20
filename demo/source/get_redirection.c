#include "minishell.h"
#include "ms_init.h"
#include "ms_strings.h"
#include "ms_structs.h"

/* 
 * This demosntrator showcase how to build the array of redirection 
 * for each t_prog (or string already split by pipe).
 * use this string as first example: 
 * "<$he'll'o" "<<'you'" ">b' 'la" ">>blabla" "<<<"
 * furthermore you can also use this:
 * "<< end" "<<    EOF" "<<'    EOF'" "<<$HOME" "<<'$HOME'"
 */
int main(int ac, char **av, char **env)
{
	t_shell sh;
	char **arr;
	char *line;
	t_arr *me;
	int i;


	init_shell(&sh, env);
	while (1)
	{
		/* Initilizing the t_arr where I'll store the structures of redirections
		 * as you can see I'm adding the function to be used to free the array 
		 * this changes based on the type of array you want to create at that time.
		 */
		me = tar_init(NULL, red_free);
		if (get_command(&sh))
		{
			i = 0;
			/* here I'm ust simulating a way to present the part of string that includes
			 * the redirection and it's value.
			 */
			arr = str_split_by_set(sh.cmd_line, MS_BLANKS,  1);
			while (arr[i] != NULL)
			{
				/* Here I'm just clearing the quotes that wrap the original cmd_line string
				 * to simulate that multiple redirection can happen on the same array.
				 */
				line = str_expand(quotes, sh.env, arr[i]);
				
				if (!tar_putred(me, line))
					printf("item %d not added\n", i);
				free(line);
				i++;
			}
			i = 0; 
			while (i < me->size)
			{
				printf("type: %d, string: %.50s \n", 
					((t_red *)me->arr[i])->type, ((t_red *)me->arr[i])->val);
				i++;
			}
		}
		tar_free(me);
	}
	arr_free(arr);
	free_shell(&sh);
}
