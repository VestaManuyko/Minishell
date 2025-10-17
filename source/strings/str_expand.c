/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:29:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 16:43:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

char	*str_expand(int (*f)(t_quote *data, char *str), t_arr *env, char *str)
{
	char	*line;
	t_quote	data;

	if (str == NULL)
		return (NULL);
	if (*str == '\0')
		return (ft_strdup(""));
	line = NULL;
	data.expand = tar_init(NULL, free);
	data.env = env;
	data.quote = 0;
	if (data.expand == NULL)
		return (NULL);
	if (!f(&data, str))
		return (arr_free((char **)data.expand->arr), free(data.expand), NULL);
	if (data.expand->size != 0)
	{
		line = arr_to_str((char **)data.expand->arr);
		free(data.expand);
	}
	if (line == NULL)
		return (arr_free((char **)data.expand->arr), free(data.expand), NULL);
	return (line);
}
