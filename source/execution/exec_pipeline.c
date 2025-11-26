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

static void	set_pipe_fds2(t_prog *item, t_shell *sh)
{
	if (item->fd_io[0] == -1)
		item->fd_io[0] = sh->pipes[item->id - 1][0];
	else
		close (sh->pipes[item->id - 1][0]);
	if (item->fd_io[1] == -1)
		item->fd_io[1] = sh->pipes[item->id][1];
	else
		close (sh->pipes[item->id][1]);
}

/*
 * Checks for exsisting redirections of stdin/out
 * and sets fds for each program according  to pipe
 * redirections.
 * If statements in this order: all items with both pipe ends,
 * then last item with no write end of pipe and then
 * first item with no pipe end for read.
*/
static void	set_pipe_fds(t_prog *item, t_shell *sh)
{
	if (item->go_to == ispipe && item->id != 0)
		set_pipe_fds2(item, sh);
	else if (item->go_to == end)
	{
		if (item->fd_io[0] == -1)
			item->fd_io[0] = sh->pipes[item->id - 1][0];
		else
			close (sh->pipes[item->id - 1][0]);
		if (item->fd_io[1] == -1)
			item->fd_io[1] = 1;
	}
	else if (item->go_to == ispipe && item->id == 0)
	{
		if (item->fd_io[0] == -1)
			item->fd_io[0] = 0;
		if (item->fd_io[1] == -1)
			item->fd_io[1] = sh->pipes[item->id][1];
		else
			close (sh->pipes[item->id][1]);
	}
}

/*
 * Execution of a single child process.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	exec_child(t_prog *item, t_shell *sh)
{
	char	*pth;

	pth = item->prog->arr[0];
	set_pipe_fds(item, sh);
	if (!dup_fds(item))
		return (0);
	close_unused_fds(item, sh);
	if (item->bltin != NULL)
	{
		if (!item->bltin->func(item->prog, sh))
			clean_exit(0, sh, 1);
		clean_exit(0, sh, 0);
	}
	else
	{
		if (execve(pth, (char **)item->prog->arr, (char **)sh->env->arr) == -1)
			return (cmd_perror(ER_MINI, "execve", strerror(errno)), 0);
	}
	return (1);
}

static void	exec_parent(pid_t pid, t_shell *sh)
{
	int		status;

	close_fds(sh);
	signal_set(2, sh);
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) > 0)
    	;
	set_status(status, sh);
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
	int		i;

	i = 0;
	while (i < sh->count)
	{
		pid = fork();
		if (pid == -1)
			return (perror(ER_FORK), 0);
		if (pid == 0)
		{
			signal_set(1, sh);
			if (set_redirect(sh, &sh->items[i]))
				clean_exit(0, sh, 1);
			if (sh->items[i].prog->size == 0)
			{
				close_fds(sh);
				clean_exit(0, sh, sh->items[i].complete);
			}
			clean_exit(0, sh, exec_child(&sh->items[i], sh));
		}
		i++;
	}
	return (exec_parent(pid, sh), signal_set(0, sh), 1);
}
