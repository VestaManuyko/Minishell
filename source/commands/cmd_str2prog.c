/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_str2prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:10:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 13:24:55 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_str2prog(t_prog *proc, char *str, t_shell *sh)
{
	size_t	i;

	i = 0;
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
	while (i < sh->count)
	{
		proc[i].fd_io[0] = -1;
		proc[i].fd_io[1] = -1;
		i++;
	}
	return (1);
}
