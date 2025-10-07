/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_manipulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:46:14 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 12:07:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_tarr(t_arr *tar)
{	
	printf("===============================================================\n");
	arr_print(tar->arr);
	printf("tarr\nsize: %d, capacity: %d\n", tar->size, tar->capacity);
}

int main(int ac, char **av, char **env)
{
	t_arr	*sys_env;
	char	*line = ft_strdup("HELLO LOVELY PEOPLE");
	sys_env = tar_init(env);
	print_tarr(sys_env);
	tar_popone(sys_env, 5);
	print_tarr(sys_env);
	tar_putone(sys_env, line);
	tar_putone(sys_env, line);
	print_tarr(sys_env);
	arr_free(sys_env->arr);
	free(sys_env);
	free(line);
	return (0);
}
