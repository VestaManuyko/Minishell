/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:20:15 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 18:38:56 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

void display_envupdate(t_shell *sh, char *str)
{
	char *exp_quotes;
	char *exp_dollar;

		exp_dollar = str_expand(dollar, sh->env, str,1);
		exp_quotes = str_expand(quotes, sh->env, exp_dollar,0);
		// exp_quotes = str_expand(quotes, sh->env, str,0);
		free(exp_dollar);
		printf("%s\n", exp_quotes);
		free(exp_quotes);
}

/* Demonstrate how the string is cleared by the dollars and quotes*/
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
	free(sh.cmd_line);
	arr_free((char**)sh.env->arr);
	free(sh.env);
	return (0);
}
