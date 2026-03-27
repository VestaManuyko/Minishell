/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:40:59 by fpaglia           #+#    #+#             */
/*   Updated: 2025/04/24 22:37:27 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cast_s;

	cast_s = (unsigned char *)s;
	while (n > 0)
	{
		*cast_s = (unsigned char)c;
		cast_s++;
		n--;
	}
	return (s);
}
