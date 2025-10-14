/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 11:52:04 by vmanuyko         ###   ########.fr       */
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
	}
}

static void	signal_set(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int main(int ac, char **av, char **env)
{
	t_shell				shell;

	signal_set();
	if (!init_shell(&shell, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	while (1)
    {
    	if (get_command(&shell))
      	{
        	populate_programs(&shell);
        	if (validate_programs(&shell))
			{
			run_programs(&shell);
			free_programs(&shell);
			}
		}
    }
}
