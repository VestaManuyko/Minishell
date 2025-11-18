/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:31:16 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 16:31:24 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_out_files(t_red *red, t_shell *shell, int i)
{
	if (red->type == out_create)
		red->fd = open(red->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (red->type == out_append)
		red->fd = open(red->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (red->fd == -1)
		return (cmd_perror(ER_MINI, red->val, strerror(errno)), 0);
	else
	{
		if (shell->items[i].fd_io[1] > 0)
			close (shell->items[i].fd_io[1]);
		shell->items[i].fd_io[1] = red->fd;
	}
	return (1);
}

static int	create_in_files(t_red *red, t_shell *shell, int i)
{
	if (red->type == in_file)
		red->fd = open(red->val, O_RDONLY);
	else if (red->type == in_heredoc)
		red->fd = open(red->val, O_RDONLY);
	if (red->fd == -1)
		return (cmd_perror(ER_MINI, red->val, strerror(errno)), 0);
	else
	{
		if (shell->items[i].fd_io[0] > 0)
			close (shell->items[i].fd_io[0]);
		shell->items[i].fd_io[0] = red->fd;
	}
	return (1);
}

/*
 * Checks if the redirection files are valid and
 * sets all the needed fds for execution.
 * Return value:
 * 0 on error, 1 on valid.
*/
int	set_redirect(t_shell *shell)
{
	t_red	*red;
	int		i;
	int		j;
	int		ret;

	i = 0;
	ret = 1;
	while (i < shell->count)
	{
		j = 0;
		while (j < shell->items[i].redirect->size)
		{
			red = (t_red *)shell->items[i].redirect->arr[j];
			if (red->type == out_create || red->type == out_append)
				ret = create_out_files(red, shell, i);
			else if (red->type == in_file || red->type == in_heredoc)
				ret = create_in_files(red, shell, i);
			if (!ret)
				return (close_fds(shell), 0);
			j++;
		}
		i++;
	}
	return (1);
}
