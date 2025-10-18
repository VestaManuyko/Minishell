/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:24:40 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 23:24:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

t_red	*red_init(t_redtype type, char *str)
{
	t_red *item;

	item = (t_red *)calloc(1, sizeof(t_red));
	if (item == NULL)
		return (NULL);
	item->type = type;
	item->val = str;
	return (item);
}
