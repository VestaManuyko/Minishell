/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_manipulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:46:14 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 10:50:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_tarr(t_arr *tar)
{	
	printf("===============================================================\n");
	arr_print((char**)tar->arr);
	printf("tarr\nsize: %zu, capacity: %zu\n", tar->size, tar->capacity);
}
/* Demo how to grow and shrink a t_arr of type char** 
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_arr	*sys_env;
	char	*line = ft_strdup("HELLO LOVELY PEOPLE");
	sys_env = tar_init(env, free);
	print_tarr(sys_env);
	tar_popone(sys_env, 5);
	print_tarr(sys_env);
	tar_putstr(sys_env, line);
	tar_putstr(sys_env, line);
	print_tarr(sys_env);
	arr_free((char**)sys_env->arr);
	free(sys_env);
	free(line);
	return (0);
}
