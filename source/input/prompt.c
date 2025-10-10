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
	char	*temp_prompt;
	char	*prompt;

	user = ft_strdup(getenv("USER"));
	if (!user)
	{
		user = ft_strdup("");
		if (!user)
			return (NULL);
	}
	temp_prompt = strdup("/minishell>");
	if (!temp_prompt)
		return (NULL);
	prompt = ft_strjoin(user, temp_prompt);
	free(user);
	free (temp_prompt);
	return (prompt);
}

int	get_command(t_shell *shell)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(shell->env);
	if (!prompt)
	{
		perror("Error");
		return (0);
	}
	line = readline(prompt);
	if (!line)
	{
		perror("Error");
		return (0);
	}
	shell->cmd_line = line;
	if (!*line)
		add_history(line);
	free(prompt);
	return (1);
}
