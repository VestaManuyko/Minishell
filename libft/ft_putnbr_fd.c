/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:40:42 by fpaglia           #+#    #+#             */
/*   Updated: 2025/04/30 15:11:56 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str[50];
	int		i;
	int		sign;

	if (n == 0)
	{
		str[0] = '0';
		write(fd, &str[0], 1);
		return ;
	}
	sign = 1 - (2 * (n < 0));
	i = 0;
	while (n != 0 && i++ >= 0)
	{
		str[i] = ((n % 10) * sign) + '0';
		n /= 10;
	}
	if (sign == -1 && i++)
		str[i] = '-';
	i++;
	while (--i > 0)
		write(fd, &str[i], 1);
}
