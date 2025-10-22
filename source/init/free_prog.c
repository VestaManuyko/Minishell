/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/22 12:28:46 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

void	free_progs(t_prog **items, int count)
{
	int	i;

	i = 0;
	if (items == NULL || *items == NULL)
		return ;
	while (i < count)
	{
		tar_free(items[i]->prog);
		tar_free(items[i]->redirect);
		i++;
	}
	free(*items);
	*items = NULL;
}
