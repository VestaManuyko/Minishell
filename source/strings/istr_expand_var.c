/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   istr_expand_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:35:12 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 13:53:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_connectivity(char *str)
{
	size_t	len;
	int		conn;

	conn = 0;
	if (ft_strchr(MS_BLANKS, *str) == NULL)
		conn++;
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	if (ft_strchr(MS_BLANKS, str[len - 1]) == NULL)
	{
		if (conn == 0)
			conn = 2;
		else
			conn = 3;
	}
	return (conn);
}

/* to try:
 * find last $ sign, check if the next is a null then remove it 
 * from the string 
*/
char	*set_value(t_istr *tmp, int item, int max, t_shell *sh)
{
	char	*line;


	if (tmp->type == 0 && item < max && tmp->str[0] == '$' && tmp->len == 1)
		line = ft_strdup("");
	else
		line = str_expand(dollar, tmp->str, 0, sh);
	return (line);
}

int	istr_expand_var(t_arr *istr, t_shell *sh)
{
	int		i;
	char	*line;
	t_istr	*tmp;

	i = 0;
	while (i < istr->size)
	{
		tmp = istr->arr[i];
		if (tmp->type != '\'')
		{
			line = set_value(tmp, i, istr->size - 1, sh);
			if (line == NULL)
				return (0);
			if (tmp->type == 0)
				tmp->connect = check_connectivity(line);
			else
				tmp->connect = 3;
			free(tmp->str);
			tmp->str = line;
			line = NULL;
		}
		i++;
	}
	return (1);
}
