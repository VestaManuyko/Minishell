
#include <minishell.h>

char *env_getkey(char *str)
{
	char *key;
	int i;
	
	i = 0;
	if (ft_isdigit(*str))
		return (NULL);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	key = ft_strncpy(str, i);
	if (key == NULL)
		return (NULL);
	return (key);	
}