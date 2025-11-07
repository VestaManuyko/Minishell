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

char	*parent_heredoc(pid_t pid, char *tmp_file, t_shell *shell)
{
	int		status;

	signal_set(2, shell);
	if ((waitpid(pid, &status, 0)) == -1)
		return (signal_set(0, shell), perror(ER_WAITPID), free(tmp_file), NULL);
	if (WIFEXITED(status))
	{
		g_return = WEXITSTATUS(status);
		if (g_return == 1)
			return (signal_set(0, shell), free(tmp_file), NULL);
	}
	if (WIFSIGNALED(status))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		g_return = 128 + WTERMSIG(status);
	}
	return (tmp_file);
}

char	*handle_heredoc(char *raw_limiter, char *limiter, t_shell *shell)
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
		signal_set(1, shell);
		if (!heredoc(raw_limiter, limiter, shell->env, tmp_file))
			exit(1);
		exit(0);
	}
	else
	{
		temp = parent_heredoc(pid, tmp_file, shell);
		if (!temp)
			return (NULL);
	}
	signal_set(0, shell);
	return (tmp_file);
}
