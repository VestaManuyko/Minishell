/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 02:12:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/18 02:12:12 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void red_free(void *item)
{
	
	if (item == NULL)
		return ;
	if (((t_red *)item)->val != NULL)
		free(((t_red *)item)->val);
	free(item);
}
