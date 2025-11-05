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
 * 0 on error, 1 on success.
*/
int	exec_bltn(t_bltn *bltn, t_shell *shell)
{
	if (!bltn->func(shell->items[0].prog, shell))
		return (0);
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
	int	i;

	i = 0;
	while (i < shell->count)
	{
		if (!program_validate(shell, &shell->items[i]))
			return (0);
		i++;
	}
	if (!set_redirect(shell))
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
