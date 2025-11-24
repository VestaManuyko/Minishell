/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/04 18:45:04 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

sig_atomic_t volatile	g_return = 0;

int	main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	rl_signal_event_hook = rl_hook;
	signal_set(0, &sh);
	if (!init_shell(&sh, env))
		return (ft_putendl_fd(ER_INIT, 2), 1);
	while (1)
	{
		if (get_command(&sh))
		{
			if (g_return == 130)
			{
				sh.status = 130;
				g_return = 0;
			}
			if (programs_populate(&sh))
			{
				exec_programs(&sh);
				reset_shell(&sh);
			}
		}
	}
	return (0);
}
