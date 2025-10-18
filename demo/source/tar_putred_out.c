#include "minishell.h"
#include "ms_init.h"
#include "ms_strings.h"
#include "ms_structs.h"
int main(int ac, char **av, char **env)
{
	t_shell sh;
	char **arr;
	t_arr me;
	int i;

	init_shell(&sh, env);
	while (1)
	{
		if (get_command(&sh))
		{
			i = 0;
			arr = str_split_by_set(sh.cmd_line, MS_BLANKS,  1);
			while (arr[i] != NULL)
			{
				tar_putred(&me, str_expand(quotes, sh.env, arr[i]));
				i++;
			}
			i = 0; 
			while (i < me.size)
			{
				printf("type: %d, string: %.50s \n", ((t_red *)me.arr[i])->type, ((t_red *)me.arr[i])->val);
				i++;
			}
			tar_free(&me);
		}
	}
	free_shell(&sh);
}