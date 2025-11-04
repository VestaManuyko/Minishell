/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 15:24:20 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_init.h"
#include <minishell.h>
#include <stdlib.h>

int g_return = 0;

int programs_run(t_shell *sh)
{
	int i;

	i = 0;
	while (i < sh->count)
	{
		programs_validate(sh, &sh->items[i]);
		i++;
	}
	return (1);
}

/* 
 * This demo is a replica of the actual main.c. 
 * core difference is that the programs are not executed but their construction
 * are printed for debugging purposes
 * 
 */
int main(int ac, char **av, char **env)
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
		else
			break ;
    }
	free_shell(&sh);
	return (0);
}
