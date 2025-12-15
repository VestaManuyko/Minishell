/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_addstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:45:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 13:10:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Demo on how to buid a t_arr with any structure. 
 * In this case we use a t_red but could be any!!!
 * please note a more accurate representation of the real t_red struct is 
 * demonstrated in tar_putred_
 */
int main(int ac, char **av, char **env)
{
	t_arr *test;
	t_red *item;
	int i = 0;
	
	(void)ac;
	(void)av;
	/*important set which is the free function for the ites of the array!!*/
	test = tar_init(NULL, red_free);
	while (env[i] != NULL)
	{ 
		item = (t_red *)ft_calloc(1, sizeof(t_red));
		if (item == NULL)
			return (tar_free(test), 0);
		/* here I'm just leveraging the env array to feed some string*/
		item->raw = ft_strdup(env[i]);
		/* here I'm assigning one of the 4 types as an example */
		item->type = i % 4;
		/* here the built item is linked in the array */
		tar_linkone(test, item);
		i++;
	}
	i = 0; 
	while (i < test->size)
	{
		printf("type: %d, string: %.50s \n", ((t_red *)test->arr[i])->type, ((t_red *)test->arr[i])->raw);
		i++;
	}
	tar_free(test);
}
