/* The goal of this demo is to evaluate if the given path is
 * a directory, a file or doesn't exist at all.
 */

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
	ret = stat(sh.cmd_line, &info);
	if (ret == -1)
		perror("stat");
	else
		printf("%d\n", ret);
	return (0);
 }