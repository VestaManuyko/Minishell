/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:23:58 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/24 18:04:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_init.h"
#include <minishell.h>

/*
 * Initialisation of the t_shell struct;
 * RETURN:
 * 0 on failure, 1 on success;
 */
int	init_shell(t_shell *shell, char **env)
{
	shell->env = tar_init(env, free);
	init_bltn_list(shell->bltn);
	if (!shell->env)
		return (0);
	shell->cmd_line = NULL;
	shell->count = 0;
	shell->items = NULL;
	shell->pipes = NULL;
	shell->status = 0;
	return (1);
}
