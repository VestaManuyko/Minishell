/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:21:13 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 10:27:03 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

void	safefree(char *str)
{
	if (str != NULL)
		free(str);
}

static int	gnl_realloc(char **line, int new_size, int size)
{
	char	*str;
	int		i;

	str = (char *)malloc(new_size);
	if (str == NULL)
		return (safefree(*line), 0);
	i = -1;
	while (++i < new_size)
		str[i] = 0;
	i = 0;
	if (*line != NULL)
	{
		while (i < size)
		{
			str[i] = (*line)[i];
			i++;
		}
	}
	str[i] = 0;
	safefree(*line);
	*line = str;
	return (1);
}

static int	check_state(t_gnl *gnl, int fd)
{
	if (gnl->b_id >= gnl->b_len)
	{
		gnl->b_len = read(fd, &gnl->buff, BUFFER_SIZE);
		gnl->b_id = 0;
		if (gnl->b_len <= 0)
		{
			if (gnl->l_ch > 0)
				return (0);
			else
				return (-1);
		}
	}
	if (gnl->b_id + 1 >= gnl->l_cap)
	{
		if (gnl->l_cap == 0)
			gnl->l_cap = 128;
		else
			gnl->l_cap *= 2;
		if (!gnl_realloc(&gnl->line, gnl->l_cap, gnl->l_ch))
			return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {0};
	int				state;

	gnl.line = NULL;
	gnl.l_ch = 0;
	gnl.l_cap = 0;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		state = check_state(&gnl, fd);
		if (state == -1)
			return (NULL);
		if (state == 0)
			return (gnl.line);
		gnl.line[gnl.l_ch++] = gnl.buff[gnl.b_id];
		if (gnl.buff[gnl.b_id++] == '\n')
			break ;
		gnl.line[gnl.l_ch] = 0;
	}
	return (gnl.line);
}
