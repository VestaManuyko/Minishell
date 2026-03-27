/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:59:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:19:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	d = (char *)ft_calloc((s_len + 1), sizeof(char));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	return (d);
}
