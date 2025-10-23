/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:03:17 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

void	free_progs(t_prog *items, int count)
{
	int	i;

	i = 0;
	if (items == NULL )
		return ;
	while (i < count)
	{
		tar_free(items[i].prog);
		tar_free(items[i].redirect);
		i++;
	}
	free(items);
}
