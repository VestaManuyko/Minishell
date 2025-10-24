/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:05:42 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 11:10:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tar_print_char(t_arr *tar)
{
	int	i;

	i = 0;
	while (i < tar->size)
	{
		printf("%s\n", (char *)tar->arr[i]);
		i++;
	}
}
