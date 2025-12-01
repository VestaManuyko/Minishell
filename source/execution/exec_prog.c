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
/*
 * Execution of a bulit-in function passed as a parameter
 * Return value:
 * 1 on error, 0 on success.
*/
int	exec_bltn(t_bltn *bltn, t_shell *shell)
{
	int	stdin_main;
	int	stdout_main;
	int	err_ret;

	err_ret = 0;
	if (shell->items[0].redirect->size != 0)
	{
		stdin_main = dup(STDIN_FILENO);
		stdout_main = dup(STDOUT_FILENO);
		if (!dup_fds(&shell->items[0]) || stdin_main == -1 || stdout_main == -1)
			return (close(stdin_main), close(stdout_main), 1);
	}
	if (!bltn->func(shell->items[0].prog, shell))
		err_ret = 1;
	if (shell->items[0].redirect->size != 0)
	{
		dup2(stdin_main, STDIN_FILENO);
		dup2(stdout_main, STDOUT_FILENO);
		close(stdin_main);
		close(stdout_main);
	}
	if (err_ret == 1)
		return (1);
	return (0);
}

/*
 * Called by parent, sets the exit status of a child process.
*/
void	set_status(int status, t_shell *sh)
{
	if (WIFEXITED(status))
		sh->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		sh->status = 128 + WTERMSIG(status);
}

/*
 * Dup_fds function checks the existing programs fds
 * and calls dup2 if needed for duplicating an fd to stdin or stdout.
 * Return value:
 * 0 on error 1 on success.
*/
int	dup_fds(t_prog *item)
{
	if (item->fd_io[0] != 0)
	{
		if ((dup2(item->fd_io[0], STDIN_FILENO)) == -1)
			return (0);
		close (item->fd_io[0]);
		item->fd_io[0] = -1;
	}
	if (item->fd_io[1] != 1)
	{
		if ((dup2(item->fd_io[1], STDOUT_FILENO)) == -1)
			return (0);
		close (item->fd_io[1]);
		item->fd_io[1] = -1;
	}
	return (1);
}

/*
 * Programs_validate validates each program if its executable
 * and has valid redirections.
*/
static void	programs_validate(t_shell *shell)
{
	int		i;
	char	*red_val;

	i = 0;
	while (i < shell->count)
	{
		if (!program_validate(shell, &shell->items[i]))
		{
			arr_free((char **)shell->items[i].prog->arr);
			shell->items[i].prog->arr = NULL;
			shell->items[i].prog->size = 0;
			shell->items[i].complete = shell->status;
		}
		red_val = set_redirect(shell, &shell->items[i]);
		if (red_val)
		{
			if (red_val[0] == '$')
				cmd_perror(ER_MINI, red_val, "ambiguous redirect");
			else
				cmd_perror(ER_MINI, red_val, strerror(errno));
			shell->items[i].complete = 1;
		}
		i++;
	}
	cl_red_fds(shell);
}

/*
 * Exec_programs checks if the programs are valid,
 * if yes executes the commands and updates the status.
*/
void	exec_programs(t_shell *shell)
{
	programs_validate(shell);
	if (shell->count == 1)
	{
		if (set_redirect(shell, &shell->items[0]))
		{
			shell->status = 1;
			return ;
		}
		if (shell->items[0].prog->size == 0)
		{
			close_fds(shell);
			return ;
		}
		if (shell->items[0].bltin == NULL)
			exec_single(shell);
		else
			shell->status = exec_bltn(shell->items[0].bltin, shell);
		close_fds(shell);
	}
	else
	{
		if (!exec_pipeline(shell))
			return ;
	}
}
