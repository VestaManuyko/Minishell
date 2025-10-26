/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_eval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/17 17:35:30 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)ac;
	(void)av;
	shell.env = malloc(sizeof(t_arr *));
	if (!shell.env)
		return (1);
	shell.env->arr = (void**)envp;
	shell.cmd_line = NULL;
	line = NULL;
	while (1)
	{
		if (get_command(&shell))
		{
			line = shell.cmd_line;
			if (!line || !*line)
				continue;
			else
			{
				printf("Line: %s\n", line);
				free (line);
				shell.cmd_line = NULL;
			}
		}
	}
	rl_clear_history();
	free(shell.env);
	return (0);
}
