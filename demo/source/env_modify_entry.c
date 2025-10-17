/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:21:21 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:54:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_environment.h"
#include "ms_strings.h"
#include <minishell.h>



void display_envupdate(t_shell *sh, char *str)
{
	int id = -1;
	char *exp_str;
	char *exp_$;
	char *key;

	if (env_entry_update(sh->env, str))
	{
		exp_$ = str_expand(dollar, sh->env, str);
		exp_str = str_expand(dollar, sh->env, exp_$);
		free(exp_$);
		key = env_getkey(exp_str);
		free(exp_str);
		id = env_getid((char**)sh->env->arr, key);
		free(key);
		if (id != -1)
			printf("%s\n",(char*)sh->env->arr[id]);
		else 
			printf("Error no id found\n");
		printf("size: %zd\n", sh->env->size);
	}
	else
		perror("minishell: export");
}


int main(int ac, char **av, char **env)
{

	t_shell sh;
	
	(void)ac;
	(void)av;
	init_shell(&sh, env);
	while (1)
	{
		if (get_command(&sh))
		{
			display_envupdate(&sh, sh.cmd_line);
			free(sh.cmd_line);
		}
	}
	free_shell(&sh);
	return (0);
}
