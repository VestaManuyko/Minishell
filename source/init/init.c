/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:23:58 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/13 11:51:00 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Initialisation of the t_shell struct;
 * RETURN:
 * 0 on failure, 1 on success;
 */
int	init_shell(t_shell *shell, char **env)
{
	shell->env = tar_init(env);
	if (!shell->env)
		return (0);
	shell->cmd_line = NULL;
	shell->count = 0;
	shell->env_paths = NULL;
	shell->items = malloc(sizeof(t_prog *));
	if (!shell->items)
		return (0);
	shell->items = NULL;
	shell->items->complete = 0;
	shell->items->cpid = 0;
	shell->items->f_stdin = NULL;
	shell->items->f_stdout = NULL;
	shell->items->fd_io[0] = 0;
	shell->items->fd_io[1] = 0;
	shell->items->id = 0;
	shell->items->prog = NULL;
	return (1);
}
