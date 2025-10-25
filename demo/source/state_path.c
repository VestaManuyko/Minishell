/* The goal of this demo is to evaluate if the given path is
 * a directory, a file or doesn't exist at all.
 */

 #include "libft.h"
#include "ms_structs.h"
#include <stdio.h>
#include <sys/stat.h>
 #include <minishell.h>

 int main(int ac, char **av, char **env)
 {
	int ret;
	struct stat info;
	t_shell sh;
	
	init_shell(&sh, env);
	get_command(&sh);
	char *line = ft_strtrim(sh.cmd_line, MS_BLANKS);
	ret = lstat(line, &info);
	for (size_t i = 0; i < strlen(sh.cmd_line); i++)
    	printf("%02X ", (unsigned char)sh.cmd_line[i]);
	printf("' (len=%zu)\n", strlen(sh.cmd_line));
	if (ret == -1)
		perror("stat");
	else
		printf("%d\n", ret);
	return (0);
 }