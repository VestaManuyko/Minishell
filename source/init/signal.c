/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:09:53 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 18:14:38 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		g_return = -1;
	}
}

void	signal_set(int is_child)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (!is_child)
		sa.sa_handler = handler;
	if (is_child)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror(ER_SIGACT);
		exit(1);
	}
	if (!is_child)
		signal(SIGQUIT, SIG_IGN);
	else
	{
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
		{
			perror(ER_SIGACT);
			exit(1);
		}
	}
}
