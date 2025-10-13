/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_eval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/10 13:27:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*line;
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	shell.env = malloc(sizeof(t_arr *));
	if (!shell.env)
		return (1);
	shell.env->arr = envp;
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
