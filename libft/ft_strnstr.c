/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:27:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/13 15:37:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isfullmatch(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (len < ft_strlen(little))
		return (0);
	i = 0;
	while (little[i] != 0)
	{
		if (little[i] != big[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (big && little && ft_strlen(little) == 0)
		return ((char *)big);
	if (len <= 0 || big == NULL || little == NULL )
		return (NULL);
	while (*big != 0 && len > 0)
	{
		if (*big == *little && isfullmatch(big, little, len))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
