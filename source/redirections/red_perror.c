/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:49:05 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 15:55:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include <minishell.h>

void	red_perror(char token, t_shell *sh)
{
	ft_putstr_fd(ER_SINTAX, 2);
	if (token == '\n' || token == '\0')
		ft_putstr_fd("Newline", 2);
	else
		ft_putchar_fd(token, 2);
	ft_putendl_fd("'", 2);
	sh->status = 2;
}
