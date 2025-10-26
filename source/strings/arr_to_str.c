/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:48:15 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 11:18:06 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	arr_totalsize(char **arr)
{
	int		i;
	ssize_t	chars;

	if (arr == NULL)
		return (-1);
	i = 0;
	chars = 0;
	while (arr[i])
	{
		chars += ft_strlen(arr[i]) + 1;
		i++;
	}
	return (chars);
}

static void	fill_string(char **arr, char **str, int add_space)
{
	ssize_t	j;
	ssize_t	k;
	int		i;

	i = 0;
	j = 0;
	while (arr[i])
	{
		k = 0;
		while (arr[i][k])
			(*str)[j++] = arr[i][k++];
		if (add_space == 1)
			(*str)[j++] = ' ';
		free(arr[i]);
		i++;
	}
	(*str)[j] = '\0';
}

char	*arr_to_str(char **arr, int add_space)
{
	ssize_t	chars;
	char	*str;

	if (arr == NULL)
		return (NULL);
	chars = arr_totalsize(arr);
	str = (char *)ft_calloc((chars + 1), sizeof(char));
	if (!str)
		return (NULL);
	fill_string(arr, &str, add_space);
	free(arr);
	return (str);
}
