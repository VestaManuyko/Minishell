/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:51:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 13:44:47 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	char	*line;
	t_arr	*sys_env;

	if (ac != 2)
	{
		printf("usage: getenvval.out {env_key}\n");
		return (0);
	}
	sys_env = tar_init(env);
	if (!env_getvalue((char**)sys_env->arr, &line, env_getid((char**)sys_env->arr, av[1])))
		return (arr_free((char**)sys_env->arr), free(sys_env), 0);
	printf("value for: %s >> %s\n", av[1], line);
	free(line);
	arr_free((char**)sys_env->arr);
	free(sys_env);
	return (0);
}
