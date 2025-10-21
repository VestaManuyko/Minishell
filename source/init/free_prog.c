/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/21 16:09:27 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

void	free_prog(t_prog item)
{
	if (item.prog != NULL)
		tar_free(item.prog);
	if (item.redirect != NULL)
		tar_free(item.redirect);	
}

void	free_progs(t_prog **items, int count)
{
	if (*items == NULL)
		return ;
	while (count-- > 0)
	{
		free_prog((*items)[count]);
	}
	free(*items);
	*items = NULL;
}
