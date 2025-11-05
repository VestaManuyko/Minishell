#include <minishell.h>

int	bltn_cd(t_arr *args, t_shell *sh)
{
	(void)args;
	(void)sh;
	if (!chdir(args->arr[1]))
		return (1);
	cmd_perror(ER_CD, args->arr[1], strerror(errno));
	return (0);
}

int	bltn_pwd(t_arr *args, t_shell *sh)
{
	char	*dir;

	(void)args;
	(void)sh;
	dir = getcwd(NULL, 0);
	if (!dir)
		return (0);
	printf("%s\n", dir);
	free(dir);
	return (1);
}

int	bltn_export(t_arr *args, t_shell *sh)
{
	(void)args;
	(void)sh;
	return (1);
}

int	bltn_unset(t_arr *args, t_shell *sh)
{
	(void)args;
	(void)sh;
	return (1);
}

int	bltn_env(t_arr *args, t_shell *sh)
{
	(void)args;
	arr_print((char **)sh->env->arr);
	return (1);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	(void)args;
	free_shell(sh);
	printf("exit\n");
	exit(0);
	return (1);
}
