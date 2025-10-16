/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:29:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/16 10:12:21 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*str_expand(int (*f)(t_quote *data, char *str), t_arr *env, char *str)
{
	char	*line;
	t_quote	data;

	line = NULL;
	data.expand = tar_init(NULL);
	data.env = env;
	data.quote = 0;
	if (data.expand == NULL)
		return (NULL);
	if (!f(&data, str))
		return (arr_free(data.expand->arr), free(data.expand), NULL);
	line = arr_to_str(data.expand->arr);
	if (line == NULL)
		return (arr_free(data.expand->arr), free(data.expand), NULL);
	free(data.expand);
	return (line);
}

