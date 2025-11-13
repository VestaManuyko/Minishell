/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:24:12 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/13 15:19:24 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include <minishell.h>

int check_cwd(char *str)
{
	size_t	len;
	
	if (!str)
		return (0);
	len = ft_strlen(str);
	if (*str == ':' || str[len - 1] == ':')
		return (1);
	return (0);
}

char	**add_cwd(char **src, int cwd_in)
{
	int		i;
	char	**arr;
	int		capacity;

	if (src == NULL)
		capacity = 1;
	else
		capacity = arr_size(src);
	arr = (char **)ft_calloc(capacity + 2, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (src && src[i] !=  NULL)
	{
		arr[i] = src[i];
		i++;
	}
	if (src == NULL || cwd_in)
		arr[i] = getcwd(NULL, 0);
	arr_print(arr);
	free(src);
	if (arr[i] == NULL)
		return (arr_free(arr), NULL);
	arr[++i] = NULL;
	return (arr);
}

char	**env_getpaths(t_arr *env)
{
	char	*value;
	char	**arr;
	int		cwd_in;

	arr = NULL;
	env_getvalue((char **)env->arr, &value,
		env_getid((char **)env->arr, "PATH"));
	cwd_in = check_cwd(value);
	if (value != NULL)
	{
		arr = str_split_by_set(value, ":", 1);
		free(value);
		value = NULL;
		if (arr == NULL)
			return (NULL);
	}
	free(value);
	arr = add_cwd(arr, cwd_in);
	return (arr);
}
