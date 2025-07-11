#include "minishell.h"
#include <signal.h>

int g_signal;

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_signal = sig;
}

void	sig_handler_cmd(int sig)
{
	g_signal = sig;
	rl_on_new_line();
}

void	update_signals(int cmd)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;

    sigemptyset(&s_sa.sa_mask); 
    sigemptyset(&s_si.sa_mask); 
    sigaddset(&s_sa.sa_mask, SIGINT); 
    sigaddset(&s_si.sa_mask, SIGQUIT);
    s_sa.sa_flags = SA_SIGINFO;
    s_si.sa_flags = SA_SIGINFO;
	s_sa.sa_handler = &sig_handler_cmd;
    if (cmd)
		s_si.sa_handler = &sig_handler_cmd;
    else
		s_si.sa_handler = SIG_IGN;
    sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
}

void	init_signals(void)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;

	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT); 
	sigaddset(&s_si.sa_mask, SIGQUIT);
	s_sa.sa_flags = SA_SIGINFO;
    s_si.sa_flags = SA_SIGINFO;
	s_sa.sa_handler = &sigint_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
}
