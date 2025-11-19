
#include <minishell.h>

void export_print(char **arr)
{
	(void)arr;
	return ;
}

int	bltn_export(t_arr *args, t_shell *sh)
{
	int	i;

	if (args->size == 1)
		export_print((char **)sh->env->arr);
	i = 1;
	while (i < args->size)
	{
		if (!env_entry_update(sh->env, (char *)args->arr[i]))
		{
			cmd_perror(ER_EXP, (char *)args->arr[i], ER_IDENT);
			g_return = 1;
		}
		i++;
	}
	return (1);
}
