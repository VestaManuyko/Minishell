/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:13:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 13:38:20 by fpaglia          ###   ########.fr       */
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
