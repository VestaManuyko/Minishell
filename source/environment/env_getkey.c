/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 10:34:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

char	*env_getkey(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (errno = EINVAL, NULL);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (errno = EINVAL, NULL);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (errno = EINVAL, NULL);
		i++;
	}
	key = ft_strncpy(str, i);
	if (key == NULL)
		return (NULL);
	return (key);
}
