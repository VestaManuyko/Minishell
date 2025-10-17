/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:03:07 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:34:05 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	**arr_double(void **src, int capacity)
{
	int		i;
	void	**arr;

	i = 0;
	arr = (void **)ft_calloc(capacity * 2, sizeof(void *));
	if (arr == NULL)
		return (NULL);
	while (src[i] != NULL)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = NULL;
	free(src);
	return (arr);
}
