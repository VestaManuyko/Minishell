/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   istr_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:54:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/21 10:54:22 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	istr_free(void *item)
{
	if (item == NULL)
		return ;
	if (((t_istr *)item)->str != NULL)
		free(((t_istr *)item)->str);
	free(item);
}
