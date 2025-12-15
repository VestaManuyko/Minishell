/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:24:40 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/21 16:27:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_red	*red_init(t_redtype type, char *raw)
{
	t_red	*item;

	item = (t_red *)ft_calloc(1, sizeof(t_red));
	if (item == NULL)
		return (NULL);
	item->type = type;
	item->raw = raw;
	return (item);
}
