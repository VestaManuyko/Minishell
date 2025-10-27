/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/27 18:30:39 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_return = 0;

int	programs_run(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->count)
	{
		programs_validate(sh, &sh->items[i]);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
		return (ft_putendl_fd(ER_INIT, 2), 1);
	signal_set();
	while (g_return != -1)
	{
		if (get_command(&sh))
		{
			if (programs_populate(&sh))
			{
				programs_run(&sh);
				programs_print(sh);
				reset_shell(&sh);
			}
		}
	}
	free_shell(&sh);
	return (0);
}
