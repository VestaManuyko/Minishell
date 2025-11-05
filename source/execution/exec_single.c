/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:30:44 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 16:30:52 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
 * Dup_fds function checks all the existing programs fds
 * and calls dup2 if needed for duplicating an fd to stdin or out etc.
 * Currently done for 1 executable.
 * Return value:
 * 0 on error 1 on success.
*/
int	dup_fds(t_shell *shell)
{
	if (shell->count == 1)
	{
		if (shell->items[0].fd_io[0])
		{
			if ((dup2(shell->items[0].fd_io[0], STDIN_FILENO)) == -1)
				return (0);
			close (shell->items[0].fd_io[0]);
			shell->items[0].fd_io[0] = 0;
		}
		if (shell->items[0].fd_io[1])
		{
			if ((dup2(shell->items[0].fd_io[1], STDOUT_FILENO)) == -1)
				return (0);
			close (shell->items[0].fd_io[1]);
			shell->items[0].fd_io[1] = 0;
		}
	}
	return (1);
}

/*
 * Executes a single child process
 * Return value:
 * 0 on error, 1 on success.
*/
int	exec_single(t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*path;
	t_prog	item;

	item = shell->items[0];
	path = (char *)item.prog->arr[0];
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), 0);
	if (pid == 0)
	{
		signal_set(1);
		if (!dup_fds(shell))
			exit(1);
		execve(path, (char **)item.prog->arr, (char **)shell->env->arr);
	}
	else
	{
		signal_set(2);
		if (waitpid(pid, &status, 0) == -1)
			return (signal_set(0), perror(ER_WAITPID), 0);
		set_status(status);
	}
	return (signal_set(0), 1);
}
