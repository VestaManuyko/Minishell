/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_putinfostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:54:05 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/21 10:54:09 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tar_putinfostr(t_arr *arr, char *str, int value, int connect)
{
	t_istr	*item;

	item = ft_calloc(1, sizeof(t_istr));
	if (item == NULL)
		return (0);
	item->str = ft_strdup(str);
	item->type = value;
	item->connect = connect;
	item->len = ft_strlen(str);
	if (item->str == NULL)
		return (free(item), 0);
	if (!tar_linkone(arr, item))
		return (0);
	return (1);
}
