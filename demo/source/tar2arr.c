
#include "ms_init.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void tar_print_char(t_arr *tar)
{
	int i;

	i = 0;
	while (i < tar->size)
	{
		printf("%s\n", (char *)tar->arr[i]);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_shell	sh;
	t_arr *tar;
	char **arr;
	char **arr2;
	char *line;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	get_command(&sh);
	arr = str_split_by_set(sh.cmd_line, MS_BLANKS, 1);
	tar = tar_init(arr, free);
	arr_free(arr);
	tar_print_char(tar);
	tar_print_char(sh.env);
	arr2 = arr_deepcpy((char **)tar->arr);
	arr_print(arr2);
	tar_free(tar);
	line = arr_to_str(arr2, 1);
	printf("%s\n", line);
	free(line);
	free_shell(&sh);
	return (0);
}