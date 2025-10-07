/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:01 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 15:11:09 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_getvalue(char **arr, int id)
{
	char	*tmp;
	char	*str;

	if (id < 0)
		return (NULL);
	tmp = ft_strchr(arr[id], '=');
	if (tmp == NULL)
	{
		str = ft_strdup("");
		if (str == NULL)
			return (NULL);
		return (str);
	}
	str = ft_strdup(tmp + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}
