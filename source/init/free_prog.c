/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:33:55 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_prog(t_prog item)
{
	if (item.prog != NULL)
		arr_free(item.prog);
	if (item.f_stdin != NULL)
		free(item.f_stdin);
	if (item.f_stdout != NULL)
		free(item.f_stdout);
}

void	free_progs(t_prog *items, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_prog(items[i]);
		i++;
	}
}
