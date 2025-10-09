/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 11:26:36 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*str_clearquotes(t_arr *env, char *str)
{
	char	*end;
	t_arr	*expand;
	char	*line;
	char	*line2;
	int		quotes;

	expand = tar_init(NULL);
	if (expand == NULL)
		return (NULL);
	quotes = 0;
	end = str;
	while (1)
	{
		quotes = str_isquoted(*end);
		if (*str == '\0')
			break ;
		else if (*str == '$' && quotes != '\'') 
		{
			if (*(str + 1) == '?' || *(str + 1) == '$')
			{
				line = ft_strdup("<< $$ and $? TO BE ADDED!!!>>");
				if (line == NULL)
					return (arr_free(expand->arr), free(expand), NULL);
				if (tar_putone(expand, line) == -1)
					return (arr_free(expand->arr), free(expand), free(line), NULL);
				free(line);
				str = str + 2;
				end++;
			}
			else
			{
				end = str + 1;
				while (*(end +1) != '\0' && *(end +1) != '\'' && *(end +1) != '"' && !ft_isspace(*(end+1)))
					end++;
				line = ft_strncpy(str + 1, end - str );
				if (line == NULL)
					return (arr_free(expand->arr), free(expand), NULL);
				line2 = env_getvalue(env->arr, env_getid(env->arr, line));
				if (line2 != NULL)
				{
					if (tar_putone(expand, line2) == -1)
						return (arr_free(expand->arr), free(expand), free(line), free(line2), NULL);
				}
				free(line);
				if (line2 != NULL)
					free(line2);
				if (quotes != 0)
					str = end + 2;
				else	
					str = end + 1;
			}
		}
		else if (*(end + 1) == quotes || (*(end + 1) == '$' && quotes != '\'' )
				|| (quotes == 0 && ft_strchr("\'\"", *(end + 1)) != NULL))
		{	
			if (str + 1 < end || str + 1 == end + 1) 
			{
				if (*str == quotes)
					str++;
				line = ft_strncpy(str, end - str + 1);
				if (line == NULL)
					return (arr_free(expand->arr), free(expand), NULL);
				tar_putone(expand, line);
				free(line);
			}
			if (*(end + 1) == quotes && quotes != '\0')
				str = end + 2;
			else
				str = end + 1;
		}
		end++;
	}
	line = arr_to_str(expand->arr);
	if (line == NULL)
		return (arr_free(expand->arr), free(expand), NULL);
	return (line);
}
