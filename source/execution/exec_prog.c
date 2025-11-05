/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:09:03 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 11:56:18 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path_for_cmd(t_prog prog)
{
	char	*path;

	path = ft_strdup((char *)prog.prog->arr[0]);
	return (path);
}
/*
 * Called by parent, sets the exit status of a child process.
*/
static void	set_status(int status)
{
	if (WIFEXITED(status))
		g_return = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_return = 128 + WTERMSIG(status);
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

	path = get_path_for_cmd(shell->items[0]);
	if (!path)
		return (0);
	pid = fork();
	if (pid == -1)
		return (free(path), perror(ER_FORK), 0);
	if (pid == 0)
	{
		signal_set(1);
		execve(path, (char **)shell->items->prog->arr, (char **)shell->env->arr);
	}
	else
	{
		signal_set(2);
		if (waitpid(pid, &status, 0) == -1)
			return (signal_set(0), perror(ER_WAITPID), 0);
		set_status(status);
	}
	return (signal_set(0), free(path), 1);
}

/*
 * Execution of a bulit in function passed as a parameter
 * Return value:
 * 0 on error, 1 on success.
*/
int	exec_bltn(t_bltn *bltn, t_shell *shell)
{
	if (!bltn->func(shell->items[0].prog, shell))
		return (0);
	return (1);
}

/*
 * Checks if the redirection files are valid and
 * sets all the needed fds for execution.
 * Return value:
 * 0 on error, 1 on valid.
*/
static int	set_redirect(t_shell *shell)
{
	t_red	*red;
	int		i;

	i = 0;
	while (i < shell->count)
	{
		red = (t_red *)shell->items[i].redirect->arr[i];
		if (red->type == out_create || red->type == out_append)
		{
			if (red->type == out_create)
				red->fd = open(red->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (red->type == out_append)
				red->fd = open(red->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (red->fd == -1)
				return (cmd_perror(ER_MINI, red->val, strerror(errno)), 0);
			else
				shell->items[i].fd_io[1] = red->fd;
		}
		else if (red->type == in_file || red->type == in_heredoc)
		{
			if (red->type == in_file)
				red->fd = open(red->val, O_RDONLY);
			else if (red->type == in_heredoc)
				red->fd = open(red->val, O_RDONLY);
			if (red->fd == -1)
				return (cmd_perror(ER_MINI, red->val, strerror(errno)), 0);
			else
				shell->items[i].fd_io[0] = red->fd;
		}
		i++;
	}
	return (1);
}

/*
 * Dup_fds function checks all the existing programs fds
 * and calls dup2 if needed for duplicating an fd to stdin or out etc.
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
 * Programs_validate validates each program if its executable
 * and has valid redirections.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	programs_validate(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->count)
	{
		if (!program_validate(shell, &shell->items[i]))
			return (0);
		i++;
	}
	if (!set_redirect(shell))
		return (0);
	if (!dup_fds(shell))
		return (0);
	return (1);
}

/*
 * Exec_programs checks if the programs are valid,
 * if yes executes the commands and updates the status.
*/
void	exec_programs(t_shell *shell)
{
	int	i;

	i = 0;
	if (!programs_validate(shell))
		return ;
	if (shell->count == 1)
	{
		if (shell->items[0].bltin == NULL)
			exec_single(shell);
		else
			exec_bltn(shell->items[0].bltin, shell);
	}
	else
	{
		while (i < shell->count)
		{
			// execute shell->items[i++];
			printf("Pipeline execution to be made\n");
		}
	}
}
