/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:00:11 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/09 13:05:10 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] != 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			last = i;
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)(s + i));
	else if (c != 0 && last != -1)
		return ((char *)(s + last));
	return (NULL);
}
