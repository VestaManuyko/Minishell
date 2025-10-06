/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_deepcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/06 15:17:25 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int arr_size(char **arr)
{
	int i;

	i = 0;	
	if (arr == NULL)
		return (-1);
	while (arr[i++] != NULL)
			;
	return(i);
}

t_arr	*tarr_deepcpy(char **src)
{
	t_arr	*arr;
	int		size;
	int		i;

	if (src == NULL)
		return (-1);
	size = arr_size(src);
	arr = (char **)malloc((size + 1) * sizeof(char));
	if (arr == NULL)
		return (-1);
	while (i < size)
	{
		arr[i] = ft_strdup(src[i]);
		if (arr[i] == NULL)
			return (arr_free(arr), -1);
		i++;
	}
	arr[i] = NULL;
	*dest = arr;
	return (i);
}
