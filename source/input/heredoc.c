/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 12:33:48 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Checks weather the given str contains quotes.
 * Return value:
 * 1 if quoted, 0 if not.
*/
static int	is_quoted(char *str)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = 1;
		i++;
	}
	if (quote == 1)
		return (1);
	return (0);
}

/*
 * Processes the line by expanding the env values if found.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	process_line(char **line, int expand, t_shell *sh, char *lim)
{
	char	*expand_line;

	if (strcmp(*line, lim))
	{
		expand_line = str_expand(dollar, *line, expand, sh);
		if (!expand_line)
			return (0);
		free (*line);
		*line = expand_line;
	}
	return (1);
}

/*
 * Displays an eof message when reached eof.
 * Return value:
 * 1 on success.
*/
static int	readline_eof(int fd, char *lim)
{
	if (g_return == 130 || g_return == 131)
		return (close(fd), 0);
	printf("minishell: here-doc delimited by eof (wanted `%s')\n", lim);
	return (close (fd), 1);
}

int	heredoc(char *raw_lim, char *lim, char *tmp_filename, t_shell *sh)
{
	int		expand;
	int		fd;
	char	*line;

	expand = 1;
	if (is_quoted(raw_lim))
		expand = 0;
	fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (readline_eof(fd, lim));
		if (ft_strchr(line, '$') && expand == 1)
		{
			if (!process_line(&line, expand, sh, lim))
				return (free(line), close (fd), 0);
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			return (close (fd), 1);
		ft_putendl_fd(line, fd);
		free (line);
	}
}
