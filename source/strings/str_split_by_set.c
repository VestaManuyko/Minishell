/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_by_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:39:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 11:14:46 by fpaglia          ###   ########.fr       */
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

static char	**set_array(char *str, char *set, bool eval_quote)
{
	int		i;
	int		items;
	char	**arr;

	i = 0;
	items = 0;
	while (str[i])
	{
		if (evaluate_quote(str[i], eval_quote) == 0
			&& ft_strchr(set, str[i] == 0)
			&& (ft_strchr(set, str[i + 1]) != NULL || str[i + 1] == 0))
			items++;
		i++;
	}
	arr = (char **)ft_calloc(items + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (arr);
}

static char	*find_end(char *str, char *set, bool eval_quote)
{
	int		quote;
	char	*end;

	end = str + 1;
	quote = 0;
	while (1)
	{
		quote = evaluate_quote(*end, eval_quote);
		if (quote == 0 && (ft_strchr(set, *end) != NULL
				|| *end == 0))
			break ;
		end++;
	}
	return (end);
}

char	**str_split_by_set(char *str, char *set, bool eval_quote)
{
	char	**arr;
	char	*end;
	int		i;

	arr = set_array(str, set, eval_quote);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (1)
	{
		while (evaluate_quote(*str, eval_quote) == 0
			&& ft_strchr(set, *str) != NULL && *str != '\0')
			str++;
		if (*str == '\0')
			break ;
		end = find_end(str, set, eval_quote);
		arr[i] = ft_strncpy(str, (size_t)(end - str));
		if (arr[i] == NULL)
			return (arr_free(arr), NULL);
		str = end;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
