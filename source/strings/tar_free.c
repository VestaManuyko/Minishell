/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 09:55:23 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	voidarr_free(void **arr, void (*u_free)(void *item))
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		u_free(arr[i]);
		i++;
	}
	free(arr);
}

void	tar_free(t_arr *tar)
{
	if (tar == NULL)
		return ;
	if (tar->arr != NULL)
		voidarr_free(tar->arr, tar->u_free);
	free(tar);
	tar = NULL;
}
