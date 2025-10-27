/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_eval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:43:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 09:34:03 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_init.h"
#include "ms_structs.h"
#include <minishell.h>

int main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	signal_set();
	if (!init_shell(&shell, envp))
		return (ft_putendl_fd(ER_INIT, 2), 1);
	while (1)
	{
		if (get_command(&shell))
		{
			printf("Line: %s\n", shell.cmd_line);
			reset_shell(&shell);
		}
	}
	free_shell(&shell);
	rl_clear_history();
	return (0);
}
