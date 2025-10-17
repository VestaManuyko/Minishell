/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 11:52:06 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_entry_update(t_arr *env, char *str)
{
	int		id;
	char	*exp_str;
	char	*key;

	exp_str = str_clearquotes(env, str);
	if (exp_str == NULL)
		return (0);
	key = env_getkey(exp_str);
	if (key == NULL)
		return (free(exp_str), 0);
	id = env_getid(env->arr, key);
	free(key);
	if (id == -1)
	{
		if (!tar_putone(env, exp_str))
			return (free(exp_str), 0);
		free(exp_str);
	}
	else
	{
		free(env->arr[id]);
		env->arr[id] = exp_str;
	}
	return (1);
}
