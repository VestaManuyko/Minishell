/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:48:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 15:55:41 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_structs.h"
#include <minishell.h>

char	*set_end(t_pipe val)
{
	char	*line;

	line = NULL;
	if (val == end)
		line = ft_strdup("end");
	else
		line = ft_strdup("ispipe");
	if (line == NULL)
		return (NULL);
	return (line);
}

void	print_a_prog(t_prog pr)
{
	int		i;
	t_red	*tmp;
	char	*line;

	i = -1;
	printf("\n==================>> PROG id:%2d <<==================\n", pr.id);
	line = set_end(pr.go_to);
	if (line != NULL)
		printf("go_to: 		%s \n", line);
	free(line);
	printf("redirections: 	\n");
	while (++i < pr.redirect->size)
	{
		tmp = (t_red *)pr.redirect->arr[i];
		if (tmp->type == out_append || tmp->type == out_create)
			printf("                fo: %s\n", tmp->val);
		else
			printf("                fi: %s\n", tmp->val);
	}
	printf("\n------------------->> ARRAY <<---------------------\n");
	arr_print((char **)pr.prog->arr);
	printf("\n");
}

void	programs_print(t_shell sh)
{
	int	i;

	i = 0;
	while (i < sh.count)
	{
		print_a_prog(sh.items[i]);
		i++;
	}
}
