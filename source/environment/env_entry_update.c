/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/19 15:11:41 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

static int	does_assign(char *str)
{
	int	assign;

	if (ft_strchr(str, '='))
		assign = 1;
	else
		assign = 0;
	return (assign);
}

int	env_entry_update(t_arr *env, char *str)
{
	int		id;
	char	*key;
	int		assign;

	assign = does_assign(str);
	key = env_getkey(str);
	if (key == NULL)
		return (0);
	id = env_getid((char **)env->arr, key);
	free(key);
	if (id == -1)
	{
		if (!tar_putstr(env, str))
			return (0);
	}
	else if (assign)
	{
		key = ft_strdup(str);
		if (key == NULL)
			return (0);
		free(env->arr[id]);
		env->arr[id] = key;
	}
	return (1);
}
