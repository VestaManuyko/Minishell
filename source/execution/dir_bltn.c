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
static int	set_pwd(t_shell *sh, char *home, char *arg, char *dir)
{
	char	*pwd;
	char	*oldpwd;
	char	*temp;

	if (!arg)
		temp = home;
	else
		temp = arg;
	pwd = ft_strjoin("PWD=", temp);
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

static int	cd2(char *home, char *arg, t_shell *sh)
{
	char	*str;
	char	*dir;

	if (!arg)
		str = home;
	else
		str = arg;
	dir = getcwd(NULL, 0);
	if (!dir)
		return (ft_putendl_fd(ER_CDENV, 2), free(home), 0);
	if (!chdir(str))
	{
		if (!set_pwd(sh, home, arg, dir))
			return (ft_putendl_fd(ER_CDENV, 2), free(home), free(dir), 0);
		return (free(home), free(dir), 1);
	}
	return (cmd_perror(ER_CD, arg, strerror(errno)), free(home), free(dir), 0);
}

int	bltn_cd(t_arr *args, t_shell *sh)
{
	char	*home;
	int		id;

	if (args->size > 2)
		return (cmd_perror(ER_MINI, "cd", ER_AC), 0);
	id = env_getid((char **)sh->env->arr, "HOME");
	if (id == -1)
		return (ft_putendl_fd(ER_CDHM, 2), 0);
	if (!env_getvalue((char **)sh->env->arr, &home, id))
		return (cmd_perror(ER_MINI, "cd", strerror(ENOMEM)), 0);
	if (!home || !*home)
		return (free(home), 1);
	return (cd2(home, args->arr[1], sh));
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
