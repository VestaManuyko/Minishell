/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:21:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/09 18:21:55 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
 * Executes multiple programs and redirects the stdin stdout
 * from the pipe between the processes.
 * In the parent sets the exit status of the last process.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	exec_pipeline(t_shell *sh)
{
	pid_t	pid;
	int		status;
	size_t	i;

	i = 0;
	while (i < sh->count)
	{
		pid == fork();
		if (pid == -1)
			return (perror(ER_FORK), 0);
		if (pid == 0)
		{

		}
	}
	signal_set(2, sh);
	if (waitpid(0, &status, 0) == -1)
		return (signal_set(0, sh), perror(ER_WAITPID), 0);
	set_status(status);
	return (signal_set(0, sh), 1);
}

int	fork_children(t_shell *sh)
{
	if (!create_pipes(sh))
		return (cmd_perror(ER_MINI, "fork_children", ER_PIPE), 0);
	if (!exec_pipeline(sh))
		return (0);
	return (1);
}