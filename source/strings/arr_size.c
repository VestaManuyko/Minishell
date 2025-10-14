/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:22:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:28:36 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

ssize_t	arr_size(char **arr)
{
	ssize_t	i;

	i = 0;
	if (arr == NULL)
		return (-1);
	while (arr[i++] != NULL)
		;
	return (i);
}
