/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tar_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:57:29 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:29:12 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arr_cpystr(char **src, char ***dest, int dest_capacity)
{
	int	i;

	i = 0;
	if (src == NULL || *dest == NULL)
		return (-1);
	while (src[i] != NULL)
	{
		if (dest_capacity <= i)
			return (arr_free(*dest), 0);
		(*dest)[i] = ft_strdup(src[i]);
		if ((*dest)[i] == NULL)
			return (arr_free(*dest), 0);
		i++;
	}
	(*dest)[i] = NULL;
	return (1);
}

t_arr	*tar_init(char **src)
{
	t_arr	*tarr;

	tarr = (t_arr *)ft_calloc(1, sizeof(t_arr));
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
	tarr->arr = (char **)ft_calloc(tarr->capacity, sizeof(char *));
	if (tarr->arr == NULL)
		return (free(tarr), NULL);
	if (src != NULL)
	{
		if (arr_cpystr(src, &tarr->arr, tarr->capacity) == 0)
			return (NULL);
	}
	return (tarr);
}
