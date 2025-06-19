#include "minishell.h"
#include <signal.h>

// TODO: return (130)
void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) info;
	(void) context;
	printf("\nzinzinshell $");
}

char	*init_signals(t_env_lst *env)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;

	(void) env; //? probably ok to erased
	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT); 
	sigaddset(&s_si.sa_mask, SIGQUIT);
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = &sigint_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
	return (NULL);
}
