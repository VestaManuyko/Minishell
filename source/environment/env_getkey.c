/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 18:46:41 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*env_getkey(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (ft_isdigit(*str))
		return (NULL);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	key = ft_strncpy(str, i);
	if (key == NULL)
		return (NULL);
	return (key);
}
