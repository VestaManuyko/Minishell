/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_addstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:45:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 21:53:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		item->val = ft_strdup(env[i]);
		item->type = i % 4;
		tar_linkone(test, item);
		i++;
	}
	i = 0; 
	while (i < test->size)
	{
		printf("type: %d, string: %.50s \n", ((t_red *)test->arr[i])->type, ((t_red *)test->arr[i])->val);
		i++;
	}
	tar_free(test);
}
