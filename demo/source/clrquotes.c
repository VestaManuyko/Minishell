/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clrquotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:07:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 09:48:56 by fpaglia          ###   ########.fr       */
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
	char example[] = "\"I am $USER\"' not $USER ' some randon envvar:\n $$ $LAN '$LANG :' $LANG\n";
//	char example[] = " $$ $LAN $LANG";
	printf("%s\n===================================================\n", example);
	line =  str_clearquotes(myenv, example);
	printf("%s", line);
	return (0);
}
