/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr2str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:27:03 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 10:33:29 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>
#include <fcntl.h>

/* Small demonstrator to convert an array to a single string.
 */
int main(int ac, char **av)
{
	char	**arr = NULL;
	char	*line = NULL;
	int		i = 0;
	int		fd;

	if (ac != 3)
	{
		printf("usage: ./arr2str {0 | 1 include separator} {path to file}");
		return (1);
	}
	fd = open(av[2], O_RDONLY);
	arr = (char **)ft_calloc(20, sizeof(char *));
	arr[0] = get_next_line(fd);
	/* get at most 18 lines from any file targeted as the first parameter in the command call*/
	while (i < 20 && arr[i] != NULL)
	{
		i++;
		arr[i] = get_next_line(fd);
	}
	if (arr[i]!= NULL)
		free (arr[i]);
	arr[i] = NULL;
	i = 0;
	while (arr[i])
	{
		printf("--------------------------\n");
		printf("%s", arr[i]);
		i++;
	}
	/* convert the array to a single string */
	line = arr_to_str(arr, ft_atoi(av[1]));
	printf("|||||||||| arr2str  |||||||||||||||||\n%s", line);
	free(line);
	return (0);
}
