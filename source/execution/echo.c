/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:00:41 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/14 09:57:01 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	only_n(char *str)
{
	while (*str != 0)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

char	**find_flags(char **arr, int *flag)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (!(arr[i][0] == '-' && only_n(&arr[i][1])))
			return (&arr[i]);
		*flag = 0;
		i++;
	}
	return (&arr[i]);
}

int	bltn_echo(t_arr *args, t_shell *sh)
{
	char	**print_ptr;
	int		flag;

	(void)sh;
	flag = 1;
	if (args->size <= 1)
		write(1, "\n", 1);
	else
	{
		print_ptr = find_flags((char **)&args->arr[1], &flag);
		arr_print(print_ptr, ' ', flag);
	}
	return (1);
}
