/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:55:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/04/29 17:18:29 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intalloc(int n, char **str)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	*str = (char *)malloc((i + 1) * sizeof(char));
	if (*str == NULL)
		return (-1);
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		chrs;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	chrs = intalloc(n, &str);
	if (chrs == -1)
		return (NULL);
	str[chrs] = 0;
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		chrs--;
		str[chrs] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
