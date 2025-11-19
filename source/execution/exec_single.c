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

int	exec_single(t_shell *sh)
{
	pid_t	pid;
	int		status;
	char	*path;
	t_prog	*item;

	item = &sh->items[0];
	path = (char *)item->prog->arr[0];
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), 0);
	if (pid == 0)
	{
		signal_set(1, sh);
		if (!dup_fds(item))
			exit(1);
		if (execve(path, (char **)item->prog->arr, (char **)sh->env->arr) == -1)
			return (cmd_perror(ER_MINI, "execve", strerror(errno)), 1);
	}
	else
	{
		signal_set(2, sh);
		waitpid(pid, &status, 0);
		set_status(status, sh);
	}
	return (signal_set(0, sh), 1);
}
