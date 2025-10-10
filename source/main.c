/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/10 13:34:14 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	t_shell	shell;

	init_shell(&shell);
	while (1)
    {
    	if (get_command(&shell))
      	{
        	populate_programs(&shell);
        	if (validate_programs(&shell))
			{
			run_programs(&shell);
			free_programs(&shell)
			}
		}
    }
}
