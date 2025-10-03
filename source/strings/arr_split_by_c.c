/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_split_by_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:43:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/03 12:21:21 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	evaluate_quote(char c, bool eval_quote)
{
	int	value;

	if (eval_quote == false)
		return (0);
	value = str_isquoted(c);
	return (value);
}

char	*ft_strncpy(char *src, size_t len)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
static char **set_array(char *str, char c, bool eval_quote)
{
	int		i;
	int		items;
	char	**arr;

	i = 0;
	items = 0;
	while (str[i])
	{
		if (evaluate_quote(str[i], eval_quote) == 0
			&& str[i] != c && (str[i+1] == c || str[i+1] == 0))
			items++;
		i++;
	}
	arr = (char **)ft_calloc(items + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (arr);
}
/*
static char *find_end(char *str, char c, bool eval_quote)
{
	
}
*/
char	**arr_split_by_c(char *str, char c, bool eval_quote)
{
	char	**arr;
	char	*end;
	int		i;
	int		quote;

	arr = set_array(str, c, eval_quote);
	if (arr == NULL)
		return (NULL);
	i = 0;
	quote = 0;
	while (1)
	{
		while (evaluate_quote(*str, eval_quote) == 0 && *str == c)
			str++;
		if (*str == '\0')
			break;
		end = str + 1;
		while (1)
		{
			quote = evaluate_quote(*end, eval_quote);
			if (quote == 0 && (*end == c || *end == 0))
				break;
			end++;
		}
		arr[i] = ft_strncpy(str, (size_t)(end - str));
		if (arr[i] == NULL)
			return (arr_free(arr), NULL);
		str = end;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
