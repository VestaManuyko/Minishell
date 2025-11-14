/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:21:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/09 18:21:55 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	close_unused_fds(t_prog *item, t_shell *sh)
{
	size_t	i;

	i = 0;
	while (i < (sh->count - 1))
	{
		if (i != (item->id - 1) && sh->pipes[i][0] != -1)
		{
			if (close(sh->pipes[i][0]) == -1)
				return (perror(ER_CLOSE), 0);
			sh->pipes[i][0] = -1;
		}
		if (i != item->id && sh->pipes[i][1] != -1)
		{
			if (close(sh->pipes[i][1]) == -1)
				return (perror(ER_CLOSE), 0);
			sh->pipes[i][1] = -1;
		}
		i++;
	}
	return (1);
}

static int	close_fds(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (i < (sh->count - 1))
	{
		if (sh->pipes[i][0] != -1)
		{
			if (close(sh->pipes[i][0]) == -1)
				return (perror(ER_CLOSE), 0);
		}
		if (sh->pipes[i][1] != -1)
		{
			if (close(sh->pipes[i][1]) == -1)
				return (perror(ER_CLOSE), 0);
		}
		sh->pipes[i][0] = -1;
		sh->pipes[i][1] = -1;
		i++;
	}
	return (1);
}

/*
 * Checks for exsisting redirections of stdin/out
 * and sets fds for each program according  to pipe
 * redirections.
*/
static void	set_pipe_fds(t_prog *item, t_shell *sh)
{
	if (item->go_to == ispipe && item->id != 0)
	{
		if (item->fd_io[0] == -1)
			item->fd_io[0] = sh->pipes[item->id - 1][0];
		if (item->fd_io[1] == -1)
			item->fd_io[1] = sh->pipes[item->id][1];
	}
	else if (item->go_to == end)
	{
		if (item->fd_io[0] == -1)
			item->fd_io[0] = sh->pipes[item->id - 1][0];
		if (item->fd_io[1] == -1)
			item->fd_io[1] = 1;
	}
	else if (item->go_to == ispipe && item->id == 0)
	{
		if (item->fd_io[0] == -1)
			item->fd_io[0] = 0;
		if (item->fd_io[1] == -1)
			item->fd_io[1] = sh->pipes[item->id][1];
	}
}

/*
 * Execution of a single child process.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	exec_child(t_prog *item, t_shell *sh)
{
	char	*path;

	path = item->prog->arr[0];
	set_pipe_fds(item, sh);
	if (!dup_fds(item))
		return (0);
	if (!close_unused_fds(item, sh))
		return (0);
	if (item->bltin != NULL)
	{
		if (!item->bltin->func(item->prog, sh))
			return (0);
	}
	else
	{
		if (execve(path, (char **)item->prog->arr, (char **)sh->env->arr) == -1)
			return (cmd_perror(ER_MINI, "execve", strerror(errno)), 0);
	}
	return (1);
}

/*
 * Executes multiple programs and redirects the stdin stdout
 * from the pipe between the processes.
 * In the parent sets the exit status of the last process.
 * Return value:
 * 0 on error, 1 on success.
*/
int	exec_pipeline(t_shell *sh)
{
	pid_t	pid;
	int		status;
	size_t	i;

	i = 0;
	while (i < sh->count)
	{
		pid = fork();
		if (pid == -1)
			return (perror(ER_FORK), 0);
		if (pid == 0)
		{
			signal_set(1, sh);
			return (exec_child(&sh->items[i], sh));
		}
		i++;
	}
	close_fds(sh);
	signal_set(2, sh);
	while ((waitpid(-1, &status, 0)) > 0)
		;
	return (set_status(status), signal_set(0, sh), 1);
}
