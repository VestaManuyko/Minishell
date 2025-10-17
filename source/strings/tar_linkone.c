/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_linkone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:58:36 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:03:42 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_linkone(t_arr *tar, void *item)
{
	if (item == NULL || tar == NULL)
		return (0);
	if (tar->capacity <= tar->size + 1)
	{
		tar->arr = arr_double(tar->arr, tar->capacity);
		if (tar->arr == NULL)
			return (0);
		tar->capacity *= 2;
	}
	tar->arr[tar->size] = item;
	if (tar->arr[tar->size] == NULL)
		return (0);
	(tar->size)++;
	tar->arr[tar->size] = NULL;
	return (1);
}
