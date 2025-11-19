/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/17 15:59:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

static char	*check_input(t_shell *sh, char *str, int *assign)
{
	char	*exp_str;

	exp_str = str_clearquotes(str, 0, sh);
	if (exp_str == NULL)
		return (NULL);
	if (ft_strchr(exp_str, '='))
		*assign = 1;
	else
		*assign = 0;
	return (exp_str);
}

int	env_entry_update(t_arr *env, char *str, t_shell *sh)
{
	int		id;
	char	*exp_str;
	char	*key;
	int		assign;

	exp_str = check_input(sh, str, &assign);
	if (exp_str == NULL)
		return (0);
	key = env_getkey(exp_str);
	if (key == NULL)
		return (free(exp_str), 0);
	id = env_getid((char **)env->arr, key);
	free(key);
	if (id == -1)
	{
		if (!tar_putstr(env, exp_str))
			return (free(exp_str), 0);
		free(exp_str);
	}
	else if (assign)
	{
		free(env->arr[id]);
		env->arr[id] = exp_str;
	}
	return (1);
}
