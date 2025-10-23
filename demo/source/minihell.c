/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:58:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
 * This demo is a replica of the actual main.c. 
 * core difference is that the programs are not executed but their construction
 * are printed for debugging purposes
 * 
 */
int main(int ac, char **av, char **env)
{
	t_shell	sh;
	int i = 0;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	while (i < 1)
    {
    	if (get_command(&sh))
      	{
			if (!programs_populate(&sh))
				return (free_shell(&sh), 1);
			programs_print(sh);
        	// if (programs_validate(&sh))
			// {
			// 	programs_run(&sh);
			// }
			reset_shell(&sh);
		}
		i++;
    }
	free_shell(&sh);
	return (0);
}
