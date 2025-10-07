/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:29:16 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/07 18:14:45 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//char *get_prompt gets the USER env variable and appends it with 
// the shell_prompt, so that readline may display prompt as example:
//USER/minishell>
// return value = prompt to be displayed or NULL upon errors;
//NOTE: should be freed later;
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
		return (1);
	}
	line = readline(prompt);
	if (!line)
	{
		perror("Error");
		return (1);
	}
	if (line && *line)
	{
		add_history(line);
		shell->cmd_line = ft_strdup(line);
	}
	free(line);
	free(prompt);
	return (0);
}
