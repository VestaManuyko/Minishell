/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/16 17:58:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tar_free(t_arr *tar)
{
	if (tar == NULL)
		return ;
	if (tar->arr != NULL)
		arr_free(tar->arr);
	free(tar);	
}