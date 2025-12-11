/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:18:21 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 15:18:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**arr_merge(char **arr1, char **arr2)
{
	int		s1;
	int		s2;
	char	**arr_out;
	char	**arr_ptr;

	s1 = arr_size(arr1);
	s2 = arr_size(arr2);
	arr_out = (char **)ft_calloc(s1 * (s1 != -1) + s2 * (s2 != -1) + 1,
			sizeof(char *));
	if (arr_out == NULL)
		return (NULL);
	arr_ptr = arr_out;
	while (s1 != -1 && *arr1 != NULL)
		*arr_ptr++ = *arr1++;
	while (s2 != -1 && *arr2 != NULL)
		*arr_ptr++ = *arr2++;
	return (arr_out);
}
