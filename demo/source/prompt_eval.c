/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_eval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/07 18:42:30 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;

	shell.env = envp;
	shell.cmd_line = NULL;
	line = NULL;
	while (get_command(&shell))
	{
		line = shell.cmd_line;
		if (!line || !*line)
			return (1);
		printf("Line: %s\n", line);
		free (line);
		shell.cmd_line = NULL;
	}
	rl_clear_history();
	return (0);
}