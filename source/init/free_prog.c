/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 13:32:43 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_prog(t_prog item)
{
	if (item.prog != NULL)
		tar_free(item.prog);
	
}

void	free_progs(t_prog *items, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free_prog(items[i]);
		free(&items[i]);
		i++;
	}
}
