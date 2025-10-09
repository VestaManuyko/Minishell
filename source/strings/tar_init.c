/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:57:29 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 13:04:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (-1);
	while (arr[i++] != NULL)
		;
	return (i);
}

t_arr	*tar_init(char **src)
{
	t_arr	*tarr;

	tarr = (t_arr *)malloc(sizeof(t_arr));
	if (tarr == NULL)
		return (NULL);
	if (src != NULL)
	{
		tarr->size = arr_size(src) - 1;
		tarr->capacity = tarr->size + 1;
	}
	else
	{
		tarr->size = 0;
		tarr->capacity = 8;
	}
	tarr->arr = (char **)malloc(tarr->capacity * sizeof(char *));
	if (tarr->arr == NULL)
		return (free(tarr), NULL);
	if (src != NULL)
	{
		if (arr_deepcpy(src, &tarr->arr, tarr->capacity) == 0)
			return (NULL);
	}
	return (tarr);
}
