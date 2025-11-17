/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:24:12 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/14 12:24:28 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_cwd(char *str)
{
	size_t	len;

	if (!str || !(*str))
		return (1);
	len = ft_strlen(str);
	if (*str == ':')
		return (1);
	else if (str[len - 1] == ':')
		return (-1);
	return (0);
}

static char	**arr_alloc(char **src)
{
	int		capacity;
	char	**arr;

	if (src == NULL)
		capacity = 1;
	else
		capacity = arr_size(src);
	arr = (char **)ft_calloc(capacity + 2, sizeof(char *));
	return (arr);
}

static char	**add_cwd(char **src, int cwd_in)
{
	int		i;
	char	**arr;
	char	*cwd;

	if (cwd_in == 0)
		return (src);
	arr = arr_alloc(src);
	cwd = getcwd(NULL, 0);
	if (arr == NULL || cwd == NULL)
		return (NULL);
	i = 0;
	if (cwd_in == 1)
		arr[i++] = cwd;
	while (src && src[i - (cwd_in == 1)] != NULL)
	{
		arr[i] = src[i - (cwd_in == 1)];
		i++;
	}
	if (src == NULL || cwd_in == -1)
		arr[i] = cwd;
	free(src);
	arr[i + (cwd_in == -1)] = NULL;
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
			return (g_return = errno, NULL);
	}
	arr = add_cwd(arr, cwd_in);
	free(value);
	return (arr);
}
