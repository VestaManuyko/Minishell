/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_populate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:44:48 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 15:58:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_arr	*split_commands(char *str)
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

/*
 * Checks for input containing only spaces or empty input
 * If only spaces or empty returns 1, otherwise 0.
*/
static int	is_only_space(char	*line, t_shell *sh)
{
	size_t	i;

	i = 0;
	if (!*line)
		return (1);
	while (line[i] == ' ')
		i++;
	if (i == ft_strlen(line))
		return (sh->status = 0, 1);
	return (0);
}

int	programs_populate(t_shell *sh)
{
	t_arr	*cmds;
	int		i;

	if (is_only_space(sh->cmd_line, sh) || !cmd_validate_pipes(sh->cmd_line, sh))
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
		if (!cmd_str2prog(&sh->items[i], cmds->arr[i], sh, cmds))
			return (tar_free(cmds), 0);
		i++;
	}
	if (!create_pipes(sh))
		return (ft_putendl_fd(ER_PIPE, 2), tar_free(cmds), 0);
	return (tar_free(cmds), 1);
}
