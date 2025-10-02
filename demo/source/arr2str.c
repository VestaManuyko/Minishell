/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr2str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:27:03 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/02 16:23:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	char	**arr = NULL;
	char	*line = NULL;
	int		i = 0;
	int		fd;

	if (ac != 2)
	{
		printf("usage: ./arr2str {path to file}");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	arr = (char **)ft_calloc(20, sizeof(char *));
	arr[0] = get_next_line(fd);
	while (i < 19 - 1 && arr[i] != NULL)
	{
		i++;
		arr[i] = get_next_line(fd);
	}
	i = 0;
	while (arr[i])
	{
		printf("--------------------------\n");
		printf("%s", arr[i]);
		i++;
	}
	line = arr_to_str(arr);
	printf("|||||||||| arr2str  |||||||||||||||||\n%s", line);
	free(line);
	return (0);
}
