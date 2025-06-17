#include "minishell.h"
#include <signal.h>

char	*cmd = NULL;

// TODO: return (130)
void	ctrl_c(pid_t pid, int fd)
{
	// int	err;
	(void) pid;
	(void) fd;
	printf("\n");
	cmd = readline("ZINZINSHELL $");
	// err = kill(pid, SIGINT);
	// set env->? to 130, somehow...
}

void	signals_handler(int sig, siginfo_t *info, void *context)
{
	(void) context;
	if (sig == SIGINT)
		ctrl_c(info->si_pid, info->si_fd);
}

char	*init_signals(void)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;
	
	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT); //ctrl + c;
	sigaddset(&s_si.sa_mask, SIGQUIT); //ctrl + \;
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = &signals_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGIO, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
	return (cmd);
}
