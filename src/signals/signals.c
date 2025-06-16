#include "minishell.h"
#include <signal.h>


void	ctrl_c(pid_t pid, int fd)
{
	int	err;

	printf("hmm %d (%d) (ctrl-c)\n", pid, fd);
	err = kill(pid, SIGINT);
	// ft_exit(cmd, env);
	exit(0);
}

// TODO: sigio need fd
void	ctrl_d(pid_t pid, int fd)
{
	printf("idk how to check the char yet %d (%d) (ctrl-d)\n", pid, fd);
}

void	signals_handler(int sig, siginfo_t *info, void *context)
{
	(void) context;
	if (sig == SIGINT)
		ctrl_c(info->si_pid, info->si_fd);
	else if (sig == SIGIO)
		ctrl_d(info->si_pid, info->si_fd);
	
}

char	*init_signals(void)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;
	
	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT); //ctrl + c;
	sigaddset(&s_sa.sa_mask, SIGIO); //ctrl + d (??);
	sigaddset(&s_si.sa_mask, SIGQUIT); //ctrl + \;
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = &signals_handler;
	// s_si.sa_flags = SA_SIGINFO;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGIO, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
	return (NULL);
}
