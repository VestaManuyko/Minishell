/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:45:00 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 12:58:15 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Given a prefix and a number, generates a paths with the following schema:
 * prefixprocidnbr
 * RETURNS
 * the allocated string or Null in case of error.
 */
char	*create_filename(int nbr, char *prefix)
{
	char	*path;
	char	*temp;
	char	*filename;

	temp = ft_itoa(nbr);
	if (temp == NULL)
		return (NULL);
	path = ft_strjoin(prefix, temp);
	free(temp);
	if (!path)
		return (NULL);
	temp = ft_itoa(getpid());
	if (temp == NULL)
		return (free(path), NULL);
	filename = ft_strjoin(path, temp);
	free(temp);
	free(path);
	if (filename == NULL)
		return (NULL);
	return (filename);
}
