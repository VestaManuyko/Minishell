/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:09:03 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 18:14:55 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_single(t_shell *shell)
{
	pid_t	pid;
	int		exit_status;
	
	//block parent signals before fork
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), 0);
	if (pid == 0)
	{
		signal_set(1);
	}
	else
	{
		signal_set(2);
		if (waitpid(pid, &exit_status) == -1)
			return (perror(ER_WAITPID), 0);
		shell->items->complete = exit_status;
	}
	return (1);
}

/*
 * Exec_programs checks if the programs are valid,
 * if yes executes the commands and updates the exit_status.
 * Return value:
 * 0 on error;
 * 1 on sucess;
*/
int	exec_programs(t_shell *shell)
{
	int	i;

	i = 0;
	if (!programs_validate(shell))
		return (0);
	if (shell->count = 1)
		return (exec_single(shell));
	else
	{
		while (i < shell->count)
		{
			// execute shell->items[i++];
			printf("Pipeline execution to be made\n");
			return (1);
		}
	}
	return (1);
}
