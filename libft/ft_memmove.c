/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:54:46 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/05 15:51:57 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*mv_from_end(unsigned char *dest, const unsigned char *src,
				size_t n)
{
	while (n > 0)
	{
		*(dest + n - 1) = *(src + n - 1);
		n--;
	}
	return (dest);
}

static void	*mv_from_start(unsigned char *dest, const unsigned char *src,
				size_t n)
{
	int	offset;

	offset = n;
	while (n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	return (dest - offset);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_src;
	unsigned char	*cast_dest;

	if (dest == NULL || src == NULL)
		return (dest);
	cast_src = (unsigned char *)src;
	cast_dest = (unsigned char *)dest;
	if (n == 0 || cast_dest == cast_src)
		return (cast_dest);
	else if (cast_dest > cast_src)
		return (mv_from_end(cast_dest, cast_src, n));
	return (mv_from_start(cast_dest, cast_src, n));
}
