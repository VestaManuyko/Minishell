/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenvval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:51:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 15:07:15 by fpaglia          ###   ########.fr       */
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
	line = env_getvalue(sys_env->arr, env_getid(sys_env->arr, av[1]));
	printf("value for: %s >> %s\n", av[1], line);
	free(line);
	arr_free(sys_env->arr);
	free(sys_env);
	return (0);
}
