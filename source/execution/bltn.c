/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:44:45 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/17 15:42:51 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_export(t_arr *args, t_shell *sh)
{
	int	i;

	i = 0;
	while (i < args->size)
	{
		if (!env_entry_update(sh->env, (char *)args->arr[i], sh))
		{
			cmd_perror(ER_EXP, (char *)args->arr[i], ER_IDENT);
			g_return = 1;
		}
		i++;
	}
	return (1);
}

int	bltn_unset(t_arr *args, t_shell *sh)
{
	if (!env_entry_remove(sh->env, (char *)args->arr[1], sh))
		return (0);
	return (1);
}

int	bltn_env(t_arr *args, t_shell *sh)
{
	int	i;

	(void)args;
	i = 0;
	while (i < sh->env->size)
	{
		if (ft_strchr(sh->env->arr[i], '='))
			ft_putendl_fd(sh->env->arr[i], 1);
		i++;
	}
	return (g_return = 0, 1);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	int		status;
	int		i;
	char	*str;

	i = 0;
	status = sh->status;
	printf("exit\n");
	if (args->size > 2)
	{
		cmd_perror(ER_MINI, "exit", "too many arguments");
		return (0);
	}
	if (args->size == 1)
		clean_exit(0, sh, status);
	str = (char *)args->arr[1];
	if (!str[i])
	{
		status = 2;
		cmd_perror(ER_EXIT, str, "numeric argument required");
		clean_exit(0, sh, status);
	}
	while (str[i])
	{
		if (isalpha(str[i]))
			break;
		i++;
	}
	if (str[i] != '\0')
	{
		cmd_perror(ER_EXIT, str, "numeric argument required");
		status = 2;
	}
	else
		status = ft_atoi(str);
	clean_exit(0, sh, status);
	return (1);
}
