/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:34:27 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/13 15:49:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

void	arr_print(char **arr, char separator, int newline)
{
	if (arr == NULL)
		return ;
	while (*arr != NULL)
	{
		ft_putstr_fd(*arr, 1);
		if (*(arr + 1) != NULL)
			ft_putchar_fd(separator, 1);
		arr++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
