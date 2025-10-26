/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_popone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:31:44 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 15:57:29 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_popone(t_arr *tar, int id)
{
	int	i;

	i = id + 1;
	if (tar == NULL)
		return (0);
	if (id >= tar->size)
		return (0);
	if (tar->arr[id] != NULL)
		tar->u_free(tar->arr[id]);
	while (i < tar->size)
		tar->arr[id++] = tar->arr[i++];
	tar->arr[id] = NULL;
	tar->size += -1;
	return (1);
}
