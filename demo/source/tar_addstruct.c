/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_addstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:45:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 18:35:08 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>

typedef enum e_red_t
{
	in_file,
	in_heredoc,
	out_new,
	out_append
} t_red_t;

typedef struct s_red
{
	t_red_t	type;
	char	*val;
} t_red;

void red_free(void *item)
{
	
	if (item == NULL)
		return ;
	if (((t_red *)item)->val != NULL)
		free(((t_red *)item)->val);
	free(item);
}

int main(int ac, char **av, char **env)
{
	t_arr *test;
	t_red *item;
	int i = 0;
	
	test = tar_init(NULL, red_free);
	while (env[i] != NULL)
	{ 
		item = (t_red *)calloc(1, sizeof(t_red));
		if (item == NULL)
			return (tar_free(test), 0);
		item->val = env[i];
		item->type = i % 4;
		tar_linkone(test, item);
		i++;
	}
	i = 0; 
	while (i < test->size)
	{
		printf("type: %d, string: %.50s ", ((t_red *)test->arr)[i].type, ((t_red *)test->arr)[i].val);
		i++;
	}
	tar_free(test);
}
