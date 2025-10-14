/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_deepcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:28:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**arr_deepcpy(char **src)
{
	ssize_t	size;
	ssize_t	i;
	char	**arr;

	if (src == NULL)
		return (NULL);
	size = arr_size(src);
	arr = (char **)ft_calloc((size + 1), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = ft_strdup(src[i]);
		if (arr[i] == NULL)
			return (arr_free(arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
