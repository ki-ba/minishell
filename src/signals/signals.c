#include "minishell.h"
#include <signal.h>
#include <termios.h>

int g_return = 0;

// TODO: return (130)
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_return = 130;
}

void	sig_handler_redir(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	g_return = 130;
}

void	update_signals(int redir)
{
	struct sigaction	s_sa;

	sigemptyset(&s_sa.sa_mask); 
	sigaddset(&s_sa.sa_mask, SIGQUIT);
	s_sa.sa_flags = SA_SIGINFO;
	if (redir)
		s_sa.sa_handler = &sig_handler_redir;
	else
		s_sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
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
	s_sa.sa_handler = &sigint_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
}
