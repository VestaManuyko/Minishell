/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:55:22 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:20:16 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*newstr(char const *s1, size_t in, size_t out)
{
	char	*str;
	size_t	j;

	str = (char *)ft_calloc((out - in + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (j < out - in)
	{
		str[j] = s1[j + in];
		j++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	in;
	size_t	out;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	in = 0;
	while (s1 && is_inset(s1[in], set))
		in++;
	out = ft_strlen(s1);
	if (in < out)
	{
		while (s1 && is_inset(s1[out - 1], set))
			out--;
	}
	str = newstr(s1, in, out);
	if (str == NULL)
		return (NULL);
	return (str);
}
