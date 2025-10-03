/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:29:16 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/03 12:36:13 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
//delete later upon adding libft.h
size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	size_t		i;
	char		*dup;

	len = 0;
	while (s[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sum_len;
	char	*str;
	size_t	i;
	size_t	j;

	sum_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sum_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = 0;
	return (str);
}
// char *get_prompt gets the USER env variable and appends it with 
// the shell_prompt, so that readline may display prompt as example:
//USER/minishell>
// return value = prompt to be displayed or NULL upon errors;
//NOTE: should be freed later;
static char	*get_prompt(char **env)
{
	char	*user;
	char	*temp_prompt;
	char	*prompt;

	user = ft_strdup(getenv("USER"));
	if (!user)
	{
		user = ft_strdup("");
		if (!user)
			return (NULL);
	}
	temp_prompt = strdup("/minishell>");
	if (!temp_prompt)
		return (NULL);
	prompt = ft_strjoin(user, temp_prompt);
	free(user);
	free (temp_prompt);
	return (prompt);
}

int main(int argc, char **argv, char **env)
{
    //schell struct and others to be defined and initialised
	char	*line;
    char	*prompt;
	//consider adding prompt to the struct so that in can be freed upon exit
	prompt = get_prompt(env);
	if (!prompt)
	{
		perror("Error");
		return (1);
	}
	while (1)
	{
		line = readline(prompt);
	}
}
