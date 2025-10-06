/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_deepcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/06 15:38:49 by fpaglia          ###   ########.fr       */
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

t_arr	*env_deepcpy(char **src)
{
	t_arr	*arr;
	int		i;

	if (src == NULL)
		return (NULL);
	arr = (t_arr *)malloc(sizeof(t_arr));
	if (arr == NULL)
		return (NULL);
	arr->size = arr_size(src);
	arr->capacity = arr->size * 2;
	arr->arr = (char **)malloc(arr->capacity * sizeof(char));
	if (arr->arr == NULL)
		return (free(arr), NULL);
	while (i < size)
	{
		arr->arr[i] = ft_strdup(src[i]);
		if (arr->arr[i] == NULL)
			return (arr_free(arr->arr), free(arr),  NULL);
		i++;
	}
	arr->arr[i] = NULL;
	return (i);
}
