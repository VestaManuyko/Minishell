/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/27 18:05:36 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_shell				shell;

	signal_set(0);
	if (!init_shell(&shell, env))
		return (ft_putendl_fd(ER_INIT, 2), 1);
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
