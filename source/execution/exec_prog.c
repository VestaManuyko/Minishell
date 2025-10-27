/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:09:03 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 17:25:02 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
 * Exec_programs checks if the programs are valid,
 * if yes executes the commands and updates the exit_status.
 * Return value:
 * 0 on error;
 * 1 on sucess;
*/
int	exec_programs(t_shell *shell)
{
	int	i;

	i = 0;
	if (!programs_validate(shell))
		return (0);
	if (shell->count = 1)
		return (exec_single(shell));
	else
	{
		while (i < shell->count)
		{
			// execute shell->items[i++];
			printf("Pipeline execution to be made\n");
			return (1);
		}
	}
	return (1);
}
