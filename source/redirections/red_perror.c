/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:49:05 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/26 14:58:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	red_perror(char token)
{
	ft_putstr_fd(ER_SINTAX, 2);
	if (token == '\n' || token == '\0')
		ft_putstr_fd("Newline", 2);
	else
		ft_putchar_fd(token, 2);
	ft_putendl_fd("'", 2);
}
