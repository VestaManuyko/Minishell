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
 * -1 on error, 0 on success.
*/
static int	process_line(char **line, t_arr *env, int expand)
{
	char	*expand_line;

	expand_line = str_expand(dollar, env, *line, expand);
	if (!expand_line)
		return (-1);
	free (*line);
	*line = expand_line;
	return (0);
}

/*
 * Displays an eof message if reached eof, otherwise closes
 * write fd and returns.
 * Return value:
 * NULL on error, tmp_filename on eof.
*/
static int	readline_eof(int fd, char *limiter)
{
	if (errno == 0)
	{
		printf("minishell: here-doc delimited by eof (wanted `%s')\n",
			limiter);
		close (fd);
		return (1);
	}
	else
	{
		close (fd);
		return (0);
	}
}

/*
 * Get_filename sets the expand flag for the heredoc function if
 * quotes are found within the raw limiter value. Creates a string with
 * the temporary filename as follows:
 * "/tmp/heredoc_(int)1[pid]";
 * Then opens a write fd.
 * Return value:
 * NULL on errors, tmp_filename on success.
*/
char	*get_filename(void)
{
	char		*tmp_filename;
	static int	nbr = 0;
	char		*path;
	char		*temp;
	
	if (nbr++ == 2147483645)
		nbr = 0;
	temp = ft_itoa(nbr);
	path = ft_strjoin("/tmp/heredoc_", temp);
	free(temp);
	temp = ft_itoa(getpid());
	tmp_filename = ft_strjoin(path, temp);
	free(temp);
	free(path);
	if (!tmp_filename)
		return (NULL);
	return (tmp_filename);
}

int	heredoc(char *raw_lim, char *limiter, t_arr *env, char *tmp_filename)
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
			return (readline_eof(fd, limiter));
		if (ft_strchr(line, '$') && expand == 1)
		{
			if (process_line(&line, env, expand) == -1)
				return (free(line), free(tmp_filename), close (fd), 0);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			return (close (fd), free(tmp_filename), 1);
		ft_putendl_fd(line, fd);
		free (line);
	}
}
