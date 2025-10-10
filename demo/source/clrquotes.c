/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clrquotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:07:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/10 10:08:09 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	t_arr *myenv;
	char *line;

	myenv = tar_init(env);
	if (ac != 1)
		printf("this demo takes no input data discarded!\n\n");
//	char example[] = "\"I am $USER\"' not $USER ' \"\"\"s\"o\"m\"'e'' 'randon envvar:\n $$ $LAN '$LANG :' $LANG\n";
//	char example[] = " $$ $LAN '$LANG :' $LANG";
//	char example[] = " ''\"\"$\"H\"'O'M\"E\"";
	char example[] = "\"'$HOME'\"";
	printf("%s\n===================================================\n", example);
	line =  str_clearquotes(myenv, example);
	printf("%s", line);
	arr_free(myenv->arr);
	free(myenv);
	free(line);
	return (0);
}
