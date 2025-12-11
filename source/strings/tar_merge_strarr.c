/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_merge_strarr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:37:24 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/24 12:38:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_merge_strarr(t_arr *dest, t_arr *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (i < src->size)
	{
		if (!tar_putstr(dest, src->arr[i]))
			return (0);
		i++;
	}
	return (1);
}
