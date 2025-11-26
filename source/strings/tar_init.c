/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:57:29 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/26 09:49:00 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

static int	arr_cpystr(char **src, char ***dest, int dest_capacity)
{
	int	i;

	i = 0;
	if (src == NULL || *dest == NULL)
		return (0);
	while (src[i] != NULL)
	{
		if (dest_capacity <= i)
			return (arr_free(*dest), 0);
		(*dest)[i] = ft_strdup(src[i]);
		if ((*dest)[i] == NULL)
		{
			arr_free(*dest);
			*dest = NULL;
			return (0);
		}
		i++;
	}
	(*dest)[i] = NULL;
	return (1);
}

static void	set_dimensions(t_arr *tarr, char **src)
{
	if (src != NULL)
	{
		tarr->size = arr_size(src);
		tarr->capacity = tarr->size + 1;
	}
	else
	{
		tarr->size = 0;
		tarr->capacity = 8;
	}
}

t_arr	*tar_init(char **src, void (*u_free)(void *item))
{
	t_arr	*tarr;

	if (u_free == NULL)
		return (NULL);
	tarr = (t_arr *)ft_calloc(1, sizeof(t_arr));
	if (tarr == NULL)
		return (NULL);
	tarr->u_free = u_free;
	set_dimensions(tarr, src);
	tarr->arr = (void **)ft_calloc(tarr->capacity, sizeof(void *));
	if (tarr->arr == NULL)
		return (free(tarr), NULL);
	if (src != NULL)
	{
		if (arr_cpystr(src, (char ***)&tarr->arr, tarr->capacity) == 0)
			return (tar_free(tarr), NULL);
	}
	return (tarr);
}
