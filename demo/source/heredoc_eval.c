/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_eval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:50:21 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 12:50:09 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	char	*line;
	t_shell shell;
	char	*limiter;
	char	*tmp_filename;
	
	if (argc != 2)
		return (printf("Needs 1 limiter\n"), 1);
	if (!init_shell(&shell, envp))
		return (1);
	limiter = str_expand(quotes, shell.env, argv[1], 0);
	if (!limiter)
		return (1);
	tmp_filename = heredoc(argv[1], limiter, &shell);
	if (!tmp_filename)
		return (free(limiter), 1);
	fd = open (tmp_filename, O_RDONLY);
	unlink(tmp_filename);
	free (tmp_filename);
	if (fd == -1)
		return (free(limiter), 1);
	else
	{
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
			{
				close (fd);
				break ;
			}
			printf("%s", line);
			free(line);
		}
	}
	free_shell(&shell);
	return (free(limiter), 0);
}
