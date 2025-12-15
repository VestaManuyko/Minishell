/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/12/15 16:59:08 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	programs_free(t_prog *items, int count)
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
