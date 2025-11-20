/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:17:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/20 13:17:55 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_exit(t_arr *args, t_shell *sh)
{
	int		i;
	char	*str;

	i = 0;
	printf("exit\n");
	if (args->size > 2)
		return (cmd_perror(ER_MINI, "exit", "too many arguments"), 0);
	if (args->size == 1)
		clean_exit(0, sh, sh->status);
	str = (char *)args->arr[1];
	if (!str[i])
	{
		cmd_perror(ER_EXIT, str, "numeric argument required");
		clean_exit(0, sh, 2);
	}
	while (str[i])
	{
		if (isalpha(str[i++]))
		{
			cmd_perror(ER_EXIT, str, "numeric argument required");
			clean_exit(0, sh, 2);
		}
	}
	return (clean_exit(0, sh, ft_atoi(str)), 1);
}
