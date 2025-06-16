#include "minishell.h"
#include <signal.h>

void	signals_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGIO)
		ctrl_d();
	else if (sig == SIGQUIT)
		ctrl_bs();
}

int	ctrl_c()
{

}

int	ctrl_d()
{

}

int	ctrl_bs()
{

}

int	init_signals()
{
	pid_t				pid;
	struct sigaction	s_sa;

	sigemptyset(&s_sa.sa.mask);
	sigaddset(&s_sa.sa_mask, SIGINT); //ctrl + c;
	sigaddset(&s_sa.sa_mask, SIGIO); //ctrl + d (??);
	sigaddset(&s_sa.sa_mask, SIGQUIT); //ctrl + \;
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = &signals_handler;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGIO, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
	pid = getpid();
	while (1) //probably inside readloop
		;
}
