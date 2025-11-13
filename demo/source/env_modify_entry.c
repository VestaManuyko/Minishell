/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:21:21 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 12:15:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

sig_atomic_t volatile g_return;


void display_envupdate(t_shell *sh, char *str)
{
	int id = -1;
	char *exp_str;
	char *exp_$;
	char *key;

	if (env_entry_update(sh->env, str))
	{
		/* this whole block is built just to find the key for printing purposes.
		 * all the work needed is executed in the previous line.
		 */
		exp_$ = str_expand(dollar, sh->env, str,1);
		exp_str = str_expand(dollar, sh->env, exp_$,0);
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

/* Demonstrates how the environments get modified by the function env_entry_update.
 * just pass a key or keyvalue pair to the shell to see how it's added.
 * imagine it should behave similarly to export ...
 * the only difference is that you don't have to use the export at the beginning..
 * as this is the built in function still to be added.
 * At prompt type any word.
 * if it's not found will be added in the environment
 * if it's found will update the environment.
 * example usage:
 *		myvar=$USER
 */
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
