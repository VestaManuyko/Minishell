/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 11:00:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
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
