/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:10:06 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/29 13:18:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av)
{
	int fd;
	if (ac != 2)
		return ( printf("usage: validfile.out {filename}"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		cmd_perror(ER_MINI, av[1], strerror(errno));
	else 
		printf("file opened successfully");
	close(fd);
	return (0);
}