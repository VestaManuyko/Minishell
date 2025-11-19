/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:06:57 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 13:08:40 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include <minishell.h>

char **arr_merge(char **arr1, char **arr2)
{
	int s1;
	int s2;
	char **arr_out;
	char **arr_ptr;
	
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

int	correct_quotes(char **str)
{
	int i;
	int quote;
	
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
char *rebuild_equal(char *str1, char *str2, int quotes)
{
	char *out;
	char *tmp;

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

char **split_byequal(char *str)
{
	char 	*equal_ptr;
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

static char **clear_export(char **arr, t_arr *env)
{
	char	**tmp;
	char	**arr_inter;
	char	**arr_out;
	int		i;
	char	*str;
	
	i = 0;
	arr_out = NULL;
	while (arr[i] != NULL)
	{
		str = str_expand(dollar, env, arr[i], 1);
		if (str == NULL)
			return (arr_free(arr), NULL);
		arr_inter = split_byequal(str);
		free(str);
		if (arr_inter == NULL)
			return (arr_free(arr), NULL);
		tmp = arr_out;
		arr_out = arr_merge(arr_out, arr_inter);
		if (arr_out == NULL)
			return (arr_free(arr), arr_free(arr_inter), NULL);
		free(tmp);
		free(arr_inter);
		i++;
	}
	return (arr_out);
}

// static char **clear_export(char **arr)
// {
// 	int i;
// 	int j;
// 	size_t len;
// 	char *str;

// 	i = 1;
// 	while (arr[i] != NULL)
// 	{
// 		if (ft_strchr(arr[i], '=') != NULL)
// 		{
// 			j = 0;
// 			len = strlen(arr[i]);
// 			str = (char *)ft_calloc(len + 3, sizeof(char));
// 			if (!str)
// 				return (NULL);
// 			while (arr[i][j] != '=')
// 			{
// 				str[j] = arr[i][j];
// 				j++;	
// 			}
// 			str[j] = arr[i][j];
// 			j++;
// 			str[j++] = '"';
// 			while (arr[i][j - 1] != '\0')
// 			{
// 				str[j] = arr[i][j - 1];
// 				j++;	
// 			}
// 			str[j] = '"';
// 		}
// 		free(arr[i]);
// 		arr[i] = str;
// 		str = NULL;
// 		i++;
// 	}
// 	return (arr);
// }

static char	**clear_dollar(char **arr, t_arr *env)
{
	char	*line;
	char	*line_d;
	char	**arr_in;
	char	**arr_out;

	arr_in = arr_deepcpy(arr);
	line = arr_to_str(arr_in, 1);
	if (line == NULL)
		return (0);
	line_d = str_expand(dollar, env, line, 1);
	free(line);
	if (line_d == NULL)
		return (0);
	arr_out = str_split_by_set(line_d, MS_BLANKS, 1);
	free(line_d);
	if (arr_out == NULL)
		return (NULL);
	return (arr_out);
}

static int	clear_quotes(char **arr, t_arr *env)
{
	int		i;
	char	*line;

	i = 0;
	while (arr[i] != NULL)
	{
		line = str_expand(quotes, env, arr[i], 0);
		if (line == NULL)
			return (0);
		free(arr[i]);
		arr[i] = line;
		i++;
	}
	return (1);
}

int	cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;
	char	**arr;

	if (ft_strncmp((char *)proc->prog->arr[0], "export", 6) == 0)
		arr = clear_export((char **)proc->prog->arr, env);
	else
		arr = clear_dollar((char **)proc->prog->arr, env);
	if (arr == NULL)
		return (0);
	if (!clear_quotes(arr, env))
		return (arr_free(arr), 0);
	tar_free(proc->prog);
	tar = tar_init(arr, free);
	arr_free(arr);
	if (tar == NULL)
		return (0);
	proc->prog = tar;
	return (1);
}
