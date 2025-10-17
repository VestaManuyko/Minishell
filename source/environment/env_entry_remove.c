/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:55:27 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 11:01:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_entry_remove(t_arr *env, char *str)
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
	if (id != -1)
		tar_popone(env, id);
	free(key);
	free(exp_str);
	return (1);
}
