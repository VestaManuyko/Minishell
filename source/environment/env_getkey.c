/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/12/15 16:59:19 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_getkey(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (NULL);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (NULL);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (NULL);
		i++;
	}
	key = ft_strncpy(str, i);
	if (key == NULL)
		return (NULL);
	return (key);
}
