/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_bltn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:45:58 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 16:46:08 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_cd(t_arr *args, t_shell *sh)
{
	char	*home;
	char	*key;
	int		id;

	key = env_getkey("HOME");
	id = env_getid((char **)sh->env->arr, key);
	free(key);
	if (id == -1)
		return (0);
	if (!env_getvalue((char **)sh->env->arr, &home, id))
		return (0);
	if (!home)
		return (0);
	if (!args->arr[1])
	{
		if ((!chdir(home)))
			return (free(home), 1);
		errno = ENOTDIR;
		cmd_perror(ER_CD, home, strerror(errno));
		return (free(home), 0);
	}
	if (!chdir(args->arr[1]))
		return (free(home), 1);
	cmd_perror(ER_CD, args->arr[1], strerror(errno));
	return (free(home), 0);
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
