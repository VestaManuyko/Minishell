/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:06:57 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/21 13:01:56 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include "ms_structs_support.h"
#include <minishell.h>
#include <time.h>

char	**split_byequal(char *str);
/*

static char	**clear_export(char **arr, t_arr *env)
{
	t_expo	ex;
	int		i;

	i = 0;
	ex.arr_out = NULL;
	while (arr[i] != NULL)
	{
		ex.str = str_expand(dollar, env, arr[i], 1);
		if (ex.str == NULL)
			return (arr_free(arr), NULL);
		ex.arr_inter = split_byequal(ex.str);
		free(ex.str);
		if (ex.arr_inter == NULL)
			return (arr_free(arr), NULL);
		ex.tmp = ex.arr_out;
		ex.arr_out = arr_merge(ex.arr_out, ex.arr_inter);
		if (ex.arr_out == NULL)
			return (arr_free(arr), arr_free(ex.arr_inter), NULL);
		free(ex.tmp);
		free(ex.arr_inter);
		i++;
	}
	return (ex.arr_out);
}
*/
int check_connectivity(char *str)
{	
	size_t	len;
	int		conn;
	
	conn = 0;
	if (ft_strchr(MS_BLANKS, *str) == NULL)
		conn++;
	len = ft_strlen(str);
	if (ft_strchr(MS_BLANKS, str[len - 1] ) == NULL)
	{
		if (conn == 0)
			conn = 2;
		else
		 	conn = 3;
	}
	return (conn);
}

int expand_var(t_arr *istr, t_arr *env)
{
	int		i;
	char	*line;
	t_istr	*tmp;

	i = 0;
	while (i < istr->size)
	{
		tmp = istr->arr[i];
		if (tmp->type != '\'')
		{
			line = str_expand(dollar, env, tmp->str, 0);
			if (line == NULL)
				return (0);
			if (tmp->type == 0)
				tmp->connect = check_connectivity(line);
			free(tmp->str);
			tmp->str = line;
			line = NULL;
		}
		i++;
	}
	return (1);
}

int append_or_connect(t_arr *arr, char *str, int connect)
{
	char *line;
	
	if (connect == 0)
		return (tar_putstr(arr, str));
	else
	{
		line = ft_strjoin(arr->arr[arr->size - 1], str);
		if (line == NULL)
			return (0);
		free(arr->arr[arr->size - 1]);
		arr->arr[arr->size - 1] = line;
	}
	return (1);	
}

int split_and_connect1st(t_arr *arr, t_istr *tmp)
{
	char	**tmparr;
	char	*line;
	int		i;
	
	tmparr = str_split_by_set(tmp->str, MS_BLANKS, 0);
	if (tmparr == NULL)
		return (0);
	if (tmp->connect == 1 || tmp->connect == 3)
	{
		line = ft_strjoin(arr->arr[arr->size - 1], tmparr[0]);
		if (line == NULL)
			return (arr_free(tmparr), 0);
		if (!tar_putstr(arr, line))
			return (arr_free(tmparr), 0);
	}
	i = (tmp->connect == 1 || tmp->connect == 3);
	while (tmparr[i] != NULL)
	{
		if (!tar_putstr(arr, tmparr[i]))
			return (arr_free(tmparr), 0);
		i++;
	}
	return (1);
}

int merge_by_connectivity(t_arr *arr, t_arr *istr)
{
	int		i;
	t_istr	*tmp;
	int		connect_last;
	
	i = 0;
	connect_last = 0;
	while (i < istr->size)
	{
		tmp = (t_istr *)istr->arr[i];
		if (tmp->type != 0)
		{
			if (!append_or_connect(arr, tmp->str, connect_last))
				return (0);
		}
		else
		{
			connect_last = (tmp->connect > 1);
			if (!split_and_connect1st(arr, tmp))
				return (0);
		}
		i++;
	}
	return (1);
}

t_arr	*clear_dollar(t_arr *arr, t_arr *env)
{
	t_arr	*strarr;
	t_arr	*tmp;
	int 	i;

	strarr = tar_init(NULL, free);
	if (strarr == NULL)
		return (NULL);
	i = 0;
	while (i < arr->size)
	{
		tmp = str_split_by_quote(arr->arr[i]);
		if (tmp == NULL)
			return (tar_free(strarr), NULL);
		if (!expand_var(tmp, env))
			return (tar_free(tmp), tar_free(strarr), NULL);
		if (!merge_by_connectivity(strarr, tmp))
			return (tar_free(tmp), tar_free(strarr), NULL);
		i++;
	}
	/*
	for each line
	if no quotes
		expand by dollar and split by blank
	else
		split it by quote (mark with quote type)
		expand everything according to the rules
		split by blank  (strings unquoted)
			if first char not blank mark it to connect with previous (if exist)
			if last char not blank mark it to connect back with next (if exist)
		for each resulting item, 
			join the one that require to be connected
	return the arr
	*/
	return (strarr);
}

// static int	clear_quotes(char **arr, t_arr *env)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		line = str_expand(quotes, env, arr[i], 0);
// 		if (line == NULL)
// 			return (0);
// 		free(arr[i]);
// 		arr[i] = line;
// 		i++;
// 	}
// 	return (1);
// }

int	cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;
	// char	**arr;

	
	// if (ft_strncmp((char *)proc->prog->arr[0], "export", 6) == 0)
	// 	arr = clear_export((char **)proc->prog->arr, env);
	// else
	tar = clear_dollar(proc->prog, env);
	if (tar == NULL)
		return (0);
	printf("after clearing dollar:\n");
	arr_print((char **)tar->arr, '\n', 1);
	// if (!clear_quotes(arr, env))
	// 	return (arr_free(arr), 0);
	tar_free(proc->prog);
	// printf("after clearing quotes:\n");
	// arr_print((char **)tar->arr, '\n', 1);
	// tar = tar_init(arr, free);
	// arr_free(arr);
	// if (tar == NULL)
	// 	return (0);
	proc->prog = tar;
	return (1);
}
