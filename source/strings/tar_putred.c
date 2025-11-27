/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putred.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:29:51 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 16:00:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_putred(t_arr *arr, char *str, char next, t_reder *d)
{
	t_red	*item;

	item = red_str2struct(str, next, d->sh);
	if (item == NULL)
		return (0);
	if (!tar_linkone(arr, item))
		return (0);
	return (1);
}
