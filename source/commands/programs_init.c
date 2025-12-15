/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:41:24 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 13:38:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_prog	*programs_init(int count)
{
	t_prog	*proc;

	proc = (t_prog *)ft_calloc(count, sizeof(t_prog));
	if (proc == NULL)
		return (NULL);
	return (proc);
}
