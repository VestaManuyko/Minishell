/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:25:53 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 15:28:47 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	correct_quotes(char **str)
{
	int	i;
	int	quote;

	i = 0;
	while ((*str)[i] != '=' && (*str)[i] != '\0')
	{
		quote = str_isquoted((*str)[i]);
		i++;
	}
	(*str)[i] = (char)quote;
	str_isquoted((*str)[i]);
	return (quote);
}

static char	*rebuild_equal(char *str1, char *str2, int quotes)
{
	char	*out;
	char	*tmp;

	if (quotes != 0)
	{
		str2[0] = (char)quotes;
		tmp = ft_strjoin(str1, "=");
		out = ft_strjoin(tmp, str2);
		free(tmp);
	}
	else
		out = ft_strjoin(str1, str2);
	return (out);
}

char	**split_byequal(char *str)
{
	char	*equal_ptr;
	char	*tmp_str;
	char	**arr;
	int		len;
	int		quotes;

	equal_ptr = ft_strchr(str, '=');
	if (equal_ptr == NULL)
		return (str_split_by_set(str, MS_BLANKS, 1));
	tmp_str = ft_strncpy(str, equal_ptr - str + 1);
	if (tmp_str == NULL)
		return (NULL);
	quotes = correct_quotes(&tmp_str);
	arr = str_split_by_set(tmp_str, MS_BLANKS, 1);
	if (arr == NULL)
		return (free(tmp_str), NULL);
	free(tmp_str);
	len = arr_size(arr);
	tmp_str = rebuild_equal(arr[len - 1], equal_ptr, quotes);
	if (tmp_str == NULL)
		return (arr_free(arr), NULL);
	free(arr[len -1]);
	arr[len - 1] = tmp_str;
	return (arr);
}
