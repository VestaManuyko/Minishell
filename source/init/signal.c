/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:09:53 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/04 18:49:01 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handler(int signum)
{
	if (signum == SIGINT)
		g_return = 130;
}

int	rl_hook(void)
{
	if (g_return == 130)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	return (0);
}

void hd_handler(int signum)
{
	if (signum == SIGINT)
		g_return = 130;
	if (signum == SIGQUIT)
		g_return = 131;
}

int rl_hd_hook(void)
{
	close(STDIN_FILENO);
	return (0);
}

/*
 * When int is_child is set to 0, means that those are signal handlers 
 * to be set for the parent, if it's 1 means it's in a child process,
 * if it's 2, means its from the parent waiting for the child and
 * if it's 3, means its from a heredoc child.
*/
void	signal_set(int is_child, t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (!is_child)
		sa.sa_handler = handler;
	if (is_child == 1)
		sa.sa_handler = SIG_DFL;
	if (is_child == 2)
		sa.sa_handler = SIG_IGN;
	if (is_child == 3)
		sa.sa_handler = hd_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		clean_exit(ER_SIGACT, shell, 1);
	if (!is_child)
		signal(SIGQUIT, SIG_IGN);
	else
	{
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			clean_exit(ER_SIGACT, shell, 1);
	}
}
