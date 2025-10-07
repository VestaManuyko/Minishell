/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:17:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 14:57:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	match_key(char *str, char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '=' || str[i] == '\0')
		return (1);
	return (0);
}

int	env_getid(char **arr, char *key)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] == key[0] && match_key(arr[i], key))
			return (i);
		i++;
	}
	return (-1);
}
