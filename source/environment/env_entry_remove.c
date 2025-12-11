/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:55:27 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/26 11:33:35 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	legit_envkey(char *str)
{
	while (*str)
	{
		if (!(ft_isalpha(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

int	env_entry_remove(t_arr *env, char *str)
{
	int		id;

	if (!legit_envkey(str))
		return (1);
	id = env_getid((char **)env->arr, str);
	if (id != -1)
		tar_popone(env, id);
	return (1);
}
