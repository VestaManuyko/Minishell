/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:13:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 12:19:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
char **arr_double(char **src, int capacity)
{
	int		i;
	char	**arr;

	i = 0;
	arr == (char **)malloc(capacity * 2 * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (src[i] != NULL)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = NULL;
	return (arr);

}
*/

int	tar_putone(t_arr *tar, char *str)
{
	char	**arr;
	int		i;

	i = 0;
	if (str == NULL || tar == NULL)
		return (-1);
	if (tar->capacity <= tar->size + 1)
	{
		arr = (char **)malloc(tar->capacity * 2 * sizeof(char *));
		if (arr == NULL)
			return (-1);
		while (tar->arr[i] != NULL)
		{
			arr[i] = tar->arr[i];
			i++;
		}
		free(tar->arr);
		tar->arr = arr;
		tar->capacity *= 2;
	}
	tar->arr[tar->size] = ft_strdup(str);
	if (tar->arr[tar->size] == NULL)
		return (-1);
	(tar->size)++;
	tar->arr[tar->size] = NULL;
	return (1);
}
