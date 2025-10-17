/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:13:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:03:48 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_putstr(t_arr *tar, char *str)
{
	if (str == NULL || tar == NULL)
		return (0);
	if (tar->capacity <= tar->size + 1)
	{
		tar->arr = arr_double(tar->arr, tar->capacity);
		if (tar->arr == NULL)
			return (0);
		tar->capacity *= 2;
	}
	tar->arr[tar->size] = ft_strdup(str);
	if (tar->arr[tar->size] == NULL)
		return (0);
	(tar->size)++;
	tar->arr[tar->size] = NULL;
	return (1);
}
