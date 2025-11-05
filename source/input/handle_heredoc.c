/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:42:23 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 12:37:04 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*parent_heredoc(pid_t pid, char *tmp_file)
{
	int		status;

	signal_set(2);
	if ((waitpid(pid, &status, 0)) == -1)
		return (signal_set(0), perror(ER_WAITPID), free(tmp_file), NULL);
	if (WIFEXITED(status))
	{
		g_return = WEXITSTATUS(status);
		if (g_return == 1)
			return (signal_set(0), free(tmp_file), NULL);
	}
	if (WIFSIGNALED(status))
		g_return = 128 + WTERMSIG(status);
	return (tmp_file);
}

char	*handle_heredoc(char *raw_limiter, char *limiter, t_arr *env)
{
	pid_t	pid;
	char	*tmp_file;
	char	*temp;

	tmp_file = get_filename();
	if (!tmp_file)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), NULL);
	if (pid == 0)
	{
		signal_set(1);
		if (!heredoc(raw_limiter, limiter, env, tmp_file))
			exit(1);
		exit(0);
	}
	else
	{
		temp = parent_heredoc(pid, tmp_file);
		if (!temp)
			return (NULL);
	}
	signal_set(0);
	return (tmp_file);
}
