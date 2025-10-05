/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:34:27 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/03 10:17:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	arr_print(char **arr)
{
	if (arr == NULL)
		return ;
	while (*arr != NULL)
	{
		printf("%s\n", *arr);
		arr++;
	}
}
