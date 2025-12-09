/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:14:19 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/12/09 18:14:20 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Get_filename sets the expand flag for the heredoc function if
 * quotes are found within the raw limiter value. Creates a string with
 * the temporary filename as follows:
 * "/tmp/heredoc_(int)1[pid]";
 * Then opens a write fd.
 * Return value:
 * NULL on errors, tmp_filename on success.
*/
static char	*get_filename(void)
{
	char		*tmp_filename;
	static int	nbr = 0;
	char		*path;
	char		*temp;

	if (nbr++ == 2147483645)
		nbr = 0;
	temp = ft_itoa(nbr);
	path = ft_strjoin("/tmp/heredoc_", temp);
	free(temp);
	temp = ft_itoa(getpid());
	tmp_filename = ft_strjoin(path, temp);
	free(temp);
	free(path);
	if (!tmp_filename)
		return (NULL);
	return (tmp_filename);
}

char	**create_files(int hd)
{
	int		i;
	char	**tmp_files;

	i = 0;
	tmp_files = malloc (hd * sizeof(char *));
	if (!tmp_files)
		return (0);
	while (i < hd)
		tmp_files[i++] = get_filename();
	return (tmp_files);
}
