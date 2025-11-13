#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>

void handler(int signum)
{
	int i = 0;

	if (signum == SIGUSR1)
	{
		while (i < 2147483640)
		{
			printf("still alive!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			i++;
		}
	}
	if (signum == SIGUSR2)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		while (readline("> "));
	}
	else
		return ;
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_flags = 0;
	sigfillset(&sa.sa_mask);

	sa.sa_handler = handler;
	printf("PID: %d\n", getpid());
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);    
	while(1)
		pause();
}
