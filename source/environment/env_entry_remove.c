/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:55:27 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 14:08:48 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_entry_remove(t_arr *env, char *str)
{
	int		id;
	char	*key;

	key = env_getkey(str);
	if (key == NULL)
		return (0);
	id = env_getid((char **)env->arr, key);
	if (id != -1)
		tar_popone(env, id);
	free(key);
	return (1);
}
