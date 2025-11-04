/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:09:03 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/04 18:47:03 by vmanuyko         ###   ########.fr       */
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
 * Executes a single child process
 * Return value:
 * 0 on error, 1 on success.
*/
int	exec_single(t_shell *shell)
{
	pid_t	pid;
	int		exit_status;
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
		if (waitpid(pid, &exit_status, 0) == -1)
			return (perror(ER_WAITPID), 0);
		shell->items->complete = exit_status;
	}
	signal_set(0);
	return (free(path), 1);
}

/*
 * Execution of a bulit in function passed as a parameter
 * Return value:
 * 0 on error, 1 on success.
*/
int	exec_bltn(t_bltn *bltn, t_shell *shell)
{
	if (!bltn->func(shell->items[0].prog, shell->env))
		return (0);
	return (1);
}

/*
 * Programs_validate validates each program if its executable
 * and checks if the redirection files are valid.
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
	//check redirections here;
	return (1);
}

/*
 * Exec_programs checks if the programs are valid,
 * if yes executes the commands and updates the exit_status.
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
