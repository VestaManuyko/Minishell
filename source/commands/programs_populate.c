/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_populate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:44:48 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 13:38:31 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_arr	*split_commands(char *str)
{
	t_arr	*cmds;
	char	**arr;

	arr = str_split_by_set(str, "|", true);
	if (arr == NULL)
		return (NULL);
	cmds = tar_init(arr, free);
	arr_free(arr);
	if (cmds == NULL)
		return (NULL);
	if (cmds->size == 0)
		return (tar_free(cmds), NULL);
	return (cmds);
}

int	programs_populate(t_shell *sh)
{
	t_arr	*cmds;
	int		i;

	if (!cmd_validate_pipes(sh->cmd_line))
		return (0);
	cmds = split_commands(sh->cmd_line);
	if (cmds == NULL)
		return (0);
	sh->count = cmds->size;
	sh->items = programs_init(cmds->size);
	if (sh->items == NULL)
		return (tar_free(cmds), 0);
	i = 0;
	while (i < cmds->size)
	{
		sh->items[i].id = i;
		if (i == cmds->size -1)
			sh->items[i].go_to = end;
		if (!cmd_str2prog(&sh->items[i], cmds->arr[i], sh))
			return (tar_free(cmds), programs_free(sh->items, cmds->size), 0);
		i++;
	}
	tar_free(cmds);
	return (1);
}
