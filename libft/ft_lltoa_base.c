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

static int	intalloc(long long n, char **str, int base)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	*str = (char *)ft_calloc((i + 1), sizeof(char));
	if (*str == NULL)
		return (-1);
	return (i);
}

static int	intalloc_unsigned(unsigned long long n, char **str, int base)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	*str = (char *)ft_calloc((i + 1), sizeof(char));
	if (*str == NULL)
		return (-1);
	return (i);
}

char	*ft_lltoa_base(long long n, char *base)
{
	char				*str;
	int					chrs;
	int					sign;
	unsigned long long	un;

	sign = 1 + ((n < 0) * -2);
	un = ((unsigned long long)n) * sign;
	chrs = intalloc(n, &str, ft_strlen(base));
	if (chrs == -1)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (un != 0)
	{
		chrs--;
		str[chrs] = base[un % ft_strlen(base)];
		un /= ft_strlen(base);
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char	*ft_lltoa_base_unsigned(unsigned long long n, char *base)
{
	char				*str;
	int					chrs;

	chrs = intalloc_unsigned(n, &str, ft_strlen(base));
	if (chrs == -1)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		chrs--;
		str[chrs] = base[n % ft_strlen(base)];
		n /= ft_strlen(base);
	}
	return (str);
}
