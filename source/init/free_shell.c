/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:02:53 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:36:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_shell(t_shell *sh)
{
	int i;

	i = 0;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	if (sh->env != NULL)
	{
		arr_free(sh->env->arr);
		free(sh->env);
	}
	while (i < sh->count)
	{
		if (sh->items + i != NULL)
			free_prog(sh->items[i]);
	}
	sh->items = NULL;
	sh = NULL;
}