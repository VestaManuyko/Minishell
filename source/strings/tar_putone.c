/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:13:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 12:32:41 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**arr_double(char **src, int capacity)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)malloc(capacity * 2 * sizeof(char *));
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

int	tar_putone(t_arr *tar, char *str)
{
	char	**arr;
	int		i;

	i = 0;
	if (str == NULL || tar == NULL)
		return (-1);
	if (tar->capacity <= tar->size + 1)
	{
		tar->arr = arr_double(tar->arr, tar->capacity);
		if (tar->arr == NULL)
			return (-1);
		tar->capacity *= 2;
	}
	tar->arr[tar->size] = ft_strdup(str);
	if (tar->arr[tar->size] == NULL)
		return (-1);
	(tar->size)++;
	tar->arr[tar->size] = NULL;
	return (1);
}
