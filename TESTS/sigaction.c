#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void	handler(int signum, siginfo_t *siginfo, void *context)
{
(void)siginfo;
(void)context;
	printf("SIGNUM = %d\n", signum);
	exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
(void)ac;
(void)av;
	struct sigaction a;

	a.sa_sigaction = &handler;
	a.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &a, NULL);
	sigaction(SIGQUIT, &a, NULL);
	sigaction(SIGFPE, &a, NULL);
	sigaction(SIGSEGV, &a, NULL);
	int b = 1 / 0;
//	int c = strlen(NULL);
//	printf("%d\n", c);
}
