/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_str2prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:10:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 14:27:25 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_commands.h"
#include <minishell.h>

int	cmd_str2prog(t_prog *proc, char *str, t_shell *sh)
{
	proc->redirect = tar_init(NULL, red_free);
	if (proc->redirect == NULL)
		return (0);
	proc->prog = tar_init(NULL, free);
	if (proc->prog == NULL)
		return (0);
	if (!cmd_split_tokens(proc, str, proc->redirect))
		return (0);
	if (!cmd_parse_redirect(proc->redirect, proc, sh))
		return (0);
	if (!cmd_parse_progs(proc, sh->env))
		return (0);
	proc->fd_io[0] = -1;
	proc->fd_io[1] = -1;
	return (1);
}
