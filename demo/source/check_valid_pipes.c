/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:56 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 10:15:01 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_commands.h"
#include "ms_init.h"
#include "ms_structs.h"
#include <minishell.h>

sig_atomic_t volatile g_return;


/* This small demo evaluate if pipes are somehow connected to some kind of data.
 * basically if after the delimiter has been found no char have been detected
 * then an error of unexpected token will be thrown.
 */
int main(int ac, char **av, char **env)
{
	t_shell	sh;
	
	(void)ac;
	(void) av;
	init_shell(&sh, env);
	while (1)
	{
		if (get_command(&sh))
			cmd_valid_pipes(sh.cmd_line);
		reset_shell(&sh);		
	}
	free_shell(&sh);
	return (0);	
}