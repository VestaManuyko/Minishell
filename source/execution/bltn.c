/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:44:45 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/25 13:34:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_unset(t_arr *args, t_shell *sh)
{
	int	i;

	i = 0;
	while (i < args->size)
	{
		env_entry_remove(sh->env, (char *)args->arr[i], sh);
		i++;
	}
	return (1);
}

int	bltn_env(t_arr *args, t_shell *sh)
{
	int	i;

	if (args->size > 1)
		return (cmd_perror(ER_MINI, "env", ER_AC), 0);
	i = 0;
	while (i < sh->env->size)
	{
		if (ft_strchr(sh->env->arr[i], '=') != NULL)
			ft_putendl_fd(sh->env->arr[i], 1);
		i++;
	}
	return (1);
}
