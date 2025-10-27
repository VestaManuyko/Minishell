/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getpaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:24:12 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/27 14:25:00 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**env_getpaths(t_arr *env)
{
	char	*value;
	char	**arr;

	env_getvalue((char **)env->arr, &value,
		env_getid((char **)env->arr, "PATH"));
	if (value == NULL)
		return (NULL);
	arr = str_split_by_set(value, ":", 1);
	free(value);
	if (arr == NULL)
		return (NULL);
	return (arr);
}
