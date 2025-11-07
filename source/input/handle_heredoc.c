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

void	free_files(char **files, int amnt)
{
	int	i;

	i = 0;
	while (i < amnt)
	{
		free(files[i++]);
	}
	free (files);
}

void	set_filenames(char **files, t_arr *redirect)
{
	t_red 	*red;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (redirect->arr[j])
	{
		red = (t_red *)redirect->arr[j];
		if (red->type == in_heredoc)
		{
			free(red->val);
			red->val = files[i];
			i++;
		}
		j++;
	}
}

int	parent_heredoc(pid_t pid, char **files, t_shell *sh, int amnt, t_arr *red)
{
	int		status;

	signal_set(2, sh);
	if ((waitpid(pid, &status, 0)) == -1)
	{
		free_files(files, amnt);
		return (signal_set(0, sh), perror(ER_WAITPID), 0);
	}
	if (WIFEXITED(status))
	{
		g_return = WEXITSTATUS(status);
		if (g_return == 1)
			return (signal_set(0, sh), free_files(files, amnt), 0);
		set_filenames(files, red);
	}
	if (WIFSIGNALED(status))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		g_return = 128 + WTERMSIG(status);
		return (signal_set(0, sh), free_files(files, amnt), 0);
	}
	return (1);
}

int	handle_heredocs(t_shell *shell, t_arr *redirect, int heredocs)
{
	pid_t	pid;
	char	**tmp_files;
	char	*temp;
	int		j;
	int		i;
	t_red 	*red;

	j = 0;
	i = 0;
	tmp_files = malloc (heredocs * sizeof(char *));
	if (!tmp_files)
		return (0);
	while (i < heredocs)
		tmp_files[i++] = get_filename();
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), 0);
	if (pid == 0)
	{
		signal_set(1, shell);
		i = 0;
		while (redirect->arr[j])
		{
			red = (t_red *)redirect->arr[j];
			if (red->type == in_heredoc)
			{
				if (!heredoc(red->raw, red->val, shell->env, tmp_files[i]))
					exit(1);
				i++;
			}
			j++;
		}
		exit(0);
	}
	else
	{
		if (!parent_heredoc(pid, tmp_files, shell, heredocs, redirect))
			return (0);
	}
	signal_set(0, shell);
	free(tmp_files);
	return (1);
}
