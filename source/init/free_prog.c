/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:09:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 11:19:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>
#include <stdio.h>

void	free_prog(t_prog item)
{
	if (item.prog != NULL)
		arr_free(item.prog);
	if (item.f_stdin != NULL)
		free(item.f_stdin);
	if (item.f_stdout != NULL)
		free(item.f_stdout);
}