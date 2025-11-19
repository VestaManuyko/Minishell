/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:44:45 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/19 14:00:35 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_unset(t_arr *args, t_shell *sh)
{
	if (!env_entry_remove(sh->env, (char *)args->arr[1]))
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
		if (ft_strchr(sh->env->arr[i], '=') != NULL)
			ft_putendl_fd(sh->env->arr[i], 1);
		i++;
	}
	return (g_return = 0, 1);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	(void)args;
	free_shell(sh);
	printf("exit\n");
	exit(0);
	return (1);
}
