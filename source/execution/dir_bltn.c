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
	char	*str;
	char	*key;
	int		id;

	if (args->size > 2)
		return (ft_putendl_fd(ER_CDAC, 2), 0);
	key = env_getkey("HOME");
	id = env_getid((char **)sh->env->arr, key);
	free(key);
	if (id == -1)
		return (ft_putendl_fd(ER_CDHM, 2), 0);
	if (!env_getvalue((char **)sh->env->arr, &home, id))
		return (cmd_perror(ER_MINI, "cd", strerror(ENOMEM)), 0);
	if (!home || !*home)
		return (free(home), 1);
	if (!args->arr[1])
		str = home;
	else
		str = args->arr[1];
	if (!chdir(str))
		return (free(home), 1);
	return (cmd_perror(ER_CD, args->arr[1], strerror(errno)), free(home), 0);
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
