/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:48:15 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/02 17:57:08 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	arr_size(char **arr)
{
	int		i;
	ssize_t	chars;

	if (arr == NULL)
		return (-1);
	i = 0;
	chars = 0;
	while (arr[i])
	{
		chars += ft_strlen(arr[i]);
		i++;
	}
	return (chars);
}

char	*arr_to_str(char **arr)
{
	ssize_t	chars;
	ssize_t	j;
	ssize_t	k;
	int		i;
	char	*str;

	i = 0;
	j = 0;
	chars = arr_size(arr);
	str = (char *)ft_calloc((chars + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (arr[i])
	{
		k = 0;
		while (arr[i][k])
			str[j++] = arr[i][k++];
		free(arr[i]);
		i++;
	}
	str[j] = '\0';
	free(arr);
	return (str);
}
