/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:29:16 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 16:24:27 by vmanuyko         ###   ########.fr       */
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
	prompt = ft_strjoin(user, "/minishell> ");
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

void	clean_exit(char *message, t_shell *shell, int status)
{
	if (!message)
	{
		free_shell(shell);
		exit(status);
	}
	if (!ft_strncmp(message, CLOSE_FDS, ft_strlen(CLOSE_FDS) + 1))
	{
		close_fds(shell);
		free_shell(shell);
		exit(status);
	}
	else
	{
		perror(message);
		free_shell(shell);
		exit(status);
	}
}

int	get_command(t_shell *shell)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt((char **)shell->env->arr);
	if (!prompt)
		clean_exit(ER_PROMPT, shell, 1);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		write(1, "exit\n", 5);
		clean_exit(0, shell, shell->status);
	}
	if (quote_opened(line))
	{
		shell->status = 1;
		return (add_history(line), free(line), ft_putendl_fd(ER_QUOTES, 2), 0);
	}
	shell->cmd_line = line;
	if (*line)
		add_history(line);
	return (1);
}
