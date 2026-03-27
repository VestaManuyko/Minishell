/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:00:55 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/09 13:22:44 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	if (size == 0 || dst_len >= size)
	{
		if (dst_len < size)
			return (dst_len + ft_strlen(src));
		return (size + ft_strlen(src));
	}
	i = 0;
	while (src[i] != 0 && (size - dst_len -1) > 0)
	{
		dst[dst_len + i] = src[i];
		i++;
		size--;
	}
	dst[dst_len + i] = 0;
	return (dst_len + ft_strlen(src));
}
