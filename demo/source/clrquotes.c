/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clrquotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:07:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 17:34:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>

int main(int ac, char **av, char **env)
{
	t_arr *myenv;
	char *line;
	char *q;

	(void)av;
	myenv = tar_init(env, free);
	if (ac != 1)
		printf("this demo takes no input data discarded!\n\n");
//	char example[] = "\"I am $USER\"' not $USER ' \"\"\"s\"o\"m\"'e'' 'randon envvar:\n $$ $LAN '$LANG :' $LANG\n";
//	char example[] = " $$ $LAN '$LANG :' $LANG";
//	char example[] = " ''\"\"$\"H\"'O'M\"E\"";
//	char example[] = "\"'$HOME'\"";
	char example[] = "$USER$TESTNOTFOUND$HOME$WTF$PWD";
	printf("%s\n===================================================\n", example);
	line =  str_expand(dollar, myenv, example);
	printf("%s", line);
	q = str_expand(quotes, myenv, line);
	free(line);
	tar_free(myenv);
	free(q);
	return (0);
}
