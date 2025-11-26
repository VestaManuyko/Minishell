/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_bltn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:45:58 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/25 14:03:22 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Updates the OLDPWD and PWD env variables after cd command.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	set_pwd(t_shell *sh, char *nextdir, char *dir, int ishome)
{
	char	*temp;
	char	*pwd;
	char	*oldpwd;
	char 	*tmp;

	if (ishome == 0)
	{
		tmp = ft_strjoin(dir, "/");
		temp = ft_strjoin(tmp, nextdir);
		pwd = ft_strjoin("PWD=", temp);
		free(tmp);
		free(temp);
	}
	else
		pwd = ft_strjoin("PWD=", nextdir);
	if (!pwd)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", dir);
	if (!oldpwd)
		return (free(pwd), 0);
	if (!env_entry_update(sh->env, pwd))
		return (free(pwd), free(oldpwd), 0);
	if (!env_entry_update(sh->env, oldpwd))
		return (free(pwd), free(oldpwd), 0);
	return (free(pwd), free(oldpwd), 1);
}

static int	cd2(char *nextdir, t_shell *sh, int ishome)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (ft_putendl_fd(ER_CDENV, 2), free(nextdir), 0);
	if (!chdir(nextdir))
	{
		if (!set_pwd(sh, nextdir, dir, ishome))
			return (ft_putendl_fd(ER_CDENV, 2), free(dir), 0);
		return (free(dir), 1);
	}
	return (cmd_perror(ER_CD, nextdir, strerror(errno)), free(dir), 0);
}

int	bltn_cd(t_arr *args, t_shell *sh)
{
	char	*home;
	int		id;

	if (args->size > 2)
		return (cmd_perror(ER_MINI, "cd", ER_AC), 0);
	if (args->size == 1)
	{
		id = env_getid((char **)sh->env->arr, "HOME");
		if (id == -1)
			return (ft_putendl_fd(ER_CDHM, 2), 0);
		if (!env_getvalue((char **)sh->env->arr, &home, id))
			return (cmd_perror(ER_MINI, "cd", strerror(ENOMEM)), 0);
		if (!home || !*home)
			return (free(home), 1);
		if (!cd2(home, sh, 1))
			return (free(home), 0);
		free(home);
	}
	else
	{
		if (!cd2(args->arr[1], sh, 0))
			return (0);
	}
	return (1);
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
