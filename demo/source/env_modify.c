/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:21:21 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 18:30:58 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_environment.h"
#include <minishell.h>

void display_envupdate(t_shell *sh, char *str)
{
	int id = -1;

	if (env_update(sh->env, str))
	{
		id = env_getid(sh->env->arr, env_getkey(str));
		if (id != -1)
			printf("%s\n",sh->env->arr[id]);
		else 
			printf("Error no id found");
		printf("size: %zd\n", sh->env->size);
	}
	
}


int main(int ac, char **av, char **env)
{

	t_shell sh;
	
	init_shell(&sh, env);
	while (1)
	{
		if (get_command(&sh))
		{
			display_envupdate(&sh, sh.cmd_line);
			free(sh.cmd_line);
		}
	}
	return (0);
}
/*
	char str[] = "cat";
	display_envupdate(&sh, str);
	
	char str2[] = "cat=dog";
	display_envupdate(&sh, str2);
	char *str3 = ft_strdup("cat=dog$cat");
	display_envupdate(&sh, str3);
	free(str3);
	*/