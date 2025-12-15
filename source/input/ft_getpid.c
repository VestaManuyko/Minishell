/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:45:54 by fpaglia           #+#    #+#             */
/*   Updated: 2025/12/15 17:57:01 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_getpid(void)
{
	int		fd;
	char	str[12];
	int		nbr;

	ft_bzero(str, 12);
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (cmd_perror(ER_MINI, "getpid", strerror(errno)), -1);
	read(fd, str, 11);
	close(fd);
	nbr = ft_atoi(str);
	return (nbr);
}
