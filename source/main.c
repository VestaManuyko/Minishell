/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/28 10:22:00 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

sig_atomic_t volatile	g_return = 0;

void	red_shellstatus(t_shell *sh)
{
	if (sh->status == 0)
		sh->status = 1;
	if (is_only_space(sh->cmd_line))
	{
		if (sh->status != 130)
			sh->status = 0;
	}
}

void	gret_to_status(t_shell *sh)
{
	if (g_return >= 130)
	{
		sh->status = g_return;
		g_return = 0;
	}
}

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
			gret_to_status(&sh);
			if (programs_populate(&sh))
			{
				exec_programs(&sh);
				reset_shell(&sh);
			}
			else
				red_shellstatus(&sh);
		}
	}
	return (0);
}
