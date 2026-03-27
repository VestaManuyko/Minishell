/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:00:14 by fpaglia           #+#    #+#             */
/*   Updated: 2025/04/24 22:27:22 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast_s;

	cast_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*cast_s == (unsigned char)c)
			return (cast_s);
		cast_s++;
		n--;
	}
	return (NULL);
}
