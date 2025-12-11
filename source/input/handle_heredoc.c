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

/*
 * Frees all the tmp_files in the files 2d array.
*/
static void	free_files(char **files, int amnt)
{
	int	i;

	i = 0;
	while (i < amnt)
	{
		free(files[i++]);
	}
	free (files);
}

/*
 * Sets all the tmp_filenames created in heredoc_handler
 * into the redirect struct.
*/
static void	set_filenames(char **files, t_arr *redirect)
{
	t_red	*red;
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

/*
 * Executes the parent process of the heredoc_handler.
*/
static int	par_hd(pid_t pid, char **files, t_shell *sh, t_arr *red)
{
	int		status;

	signal_set(2, sh);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		sh->status = WEXITSTATUS(status);
		if (sh->status == 1)
			return (signal_set(0, sh), 0);
		if (sh->status == 130 || sh->status == 131)
			return (signal_set(0, sh), 0);
		set_filenames(files, red);
	}
	if (WIFSIGNALED(status))
	{
		sh->status = 128 + WTERMSIG(status);
		return (signal_set(0, sh), 0);
	}
	return (1);
}

/*
 * Executes the child process of an heredoc_handler.
*/
static int	chld_hd(t_arr *redirect, t_shell *sh, char **files, int amnt)
{
	int				i;
	int				j;
	t_red			*red;
	int				stdin_main;
	struct termios	saved_term;

	i = 0;
	j = 0;
	tcgetattr(STDIN_FILENO, &saved_term);
	stdin_main = dup(STDIN_FILENO);
	rl_signal_event_hook = rl_hd_hook;
	while (redirect->arr[j])
	{
		red = (t_red *)redirect->arr[j++];
		if (red->type == in_heredoc)
		{
			if (!heredoc(red->raw, red->val, files[i++], sh))
			{
				dup2(stdin_main, STDIN_FILENO);
				tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
				return (free_files(files, amnt), close(stdin_main), 0);
			}
		}
	}
	return (free_files(files, amnt), close(stdin_main), 1);
}

/*
 * Creates tmp_files for the amount of heredocs,
 * then calles a child process, which calls heredoc function
 * for all of the heredoc, that eads from stdin until a delimiter is met
 * and writes into the tmp_file provided.
 * In the parent process waits for the child to terminate, if
 * all the heredocs were succesful and no signal interruption occured
 * during the child process, then sets all the tmp_file named for further
 * redirection execution into the redirect struct and updates
 * the exit status of the child.
 * Return value:
 * 0 on error, 1 on success.
*/
int	handle_heredocs(t_shell *shell, t_arr *redirect, int hd, t_arr *cmds)
{
	pid_t	pid;
	char	**tmp_files;

	tmp_files = create_files(hd);
	if (!tmp_files)
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror(ER_FORK), free_files(tmp_files, hd), 0);
	if (pid == 0)
	{
		signal_set(3, shell);
		if (!chld_hd(redirect, shell, tmp_files, hd))
		{
			if (g_return == 130 || g_return == 131)
				return (tar_free(cmds), clean_exit(0, shell, g_return), 0);
			return (tar_free(cmds), clean_exit(0, shell, 1), 0);
		}
		return (tar_free(cmds), clean_exit(0, shell, 0), 1);
	}
	if (!par_hd(pid, tmp_files, shell, redirect))
		return (free_files(tmp_files, hd), 0);
	return (signal_set(0, shell), free(tmp_files), 1);
}
