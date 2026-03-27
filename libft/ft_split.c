/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:26:54 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/06 16:05:08 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strcount(char const *s, char c, int i)
{
	int	count;

	count = 0;
	if (i == 0)
	{
		if (s[0] != c && s[0] != 0)
			count++;
	}
	while (s[i] != 0)
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != 0))
			count++;
		i++;
	}
	return (count);
}

static int	str_start(char const *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == 0)
		return (-1);
	else if (s[i] != c && s[i] != 0)
		return (i);
	while (s[i] != 0)
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != 0))
			return (i + 1);
		i++;
	}
	return (-1);
}

static char	*stralloc(char *start, char *end)
{
	char	*str;
	int		i;
	int		len;

	len = (end - start);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = *(start + i);
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	*ft_findchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return ((char *)(s + i));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*end;
	int		i;

	arr = (char **)malloc((strcount(s, c, 0) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (str_start(s, c) != -1)
	{
		s += str_start(s, c);
		end = ft_findchr(s, c);
		arr[i] = stralloc((char *)s, end);
		if (arr[i] == NULL)
		{
			while (i-- > 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		s = end;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
