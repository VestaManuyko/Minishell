/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_deepcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 10:05:27 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arr_deepcpy(char **src, char ***dest, int dest_capacity)
{
	int	i;

	i = 0;
	if (src == NULL || *dest == NULL)
		return (-1);
	while (src[i] != NULL)
	{
		if (dest_capacity <= i)
			return (arr_free(*dest), -1);
		(*dest)[i] = ft_strdup(src[i]);
		if ((*dest)[i] == NULL)
			return (arr_free(*dest), -1);
		i++;
	}
	(*dest)[i] = NULL;
	return (1);
}
