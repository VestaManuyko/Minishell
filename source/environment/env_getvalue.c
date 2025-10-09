/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:01 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 14:35:57 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_getvalue(char **arr, char **str, int id)
{
	char	*tmp;

	if (id < 0)
	{
		*str = NULL;
		return (1);
	}
	tmp = ft_strchr(arr[id], '=');
	if (tmp == NULL)
	{
		*str = ft_strdup("");
		if (*str == NULL)
			return (0);
		return (1);
	}
	*str = ft_strdup(tmp + 1);
	if (*str == NULL)
		return (0);
	return (1);
}
