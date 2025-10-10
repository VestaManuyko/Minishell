/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:29:16 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/10 13:30:20 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
 * Char *get_prompt gets the USER env variable and appends it with 
 * the shell_prompt, so that readline may display prompt as example:
 * USER/minishell>
 * return value = prompt to be displayed or NULL upon errors;
 * NOTE: should be freed later;
 */
static char	*get_prompt(char **env)
{
	char	*user;
	char	*prompt;
	int		id;

	id = env_getid(env, "USER");
	if (!env_getvalue(env, &user, id))
		return (NULL);
	if (!user)
	{
		user = ft_strdup("");
		if (!user)
			return (NULL);
	}
	prompt = ft_strjoin(user, "/minishell>");
	free(user);
	return (prompt);
}

static int	quote_opened(char *line)
{
	int		status;
	size_t	i;

	status = -1;
	i = 0;
	if (!line[i])
		return (0);
	while (line[i])
	{
		status = str_isquoted(line[i]);
		i++;
	}
	if (!status)
		return (0);
	str_isquoted(status);
	return (1);
}
//FIX change exit for clean_up

int	get_command(t_shell *shell)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(shell->env->arr);
	if (!prompt)
	{
		perror("Error\nget_prompt");
		exit(EXIT_FAILURE);
	}
	line = readline(prompt);
	if (!line)
	{
		perror("Error\nreadline");
		exit (EXIT_FAILURE);
	}
	if (quote_opened(line))
	{
		write(2, "Error\nPlease, open quotes detected.\n", 31);
		return (0);
	}
	shell->cmd_line = line;
	if (*line)
		add_history(line);
	free(prompt);
	return (1);
}
