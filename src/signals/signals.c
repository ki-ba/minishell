#include "minishell.h"
#include <signal.h>
#include <termios.h>

int g_return = 0;

// TODO: return (130)
void	sigs_handler(int sig)
{
	// struct termios termi;
	// if (sig == SIGINT)
	// {
	// 	printf("\n");
	// 	rl_replace_line("", 2);
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// }
	// if (sig == SIGQUIT)
	// {
	// 	tcgetattr(STDERR_FILENO, &termi);
	// 	termi.c_lflag &= ~ECHOCTL;
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &termi);
	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	// termi.c_lflag &= ECHOCTL;
	// }
	(void) sig;
	printf("\nzinzinshell $");
	g_return = 130;
}

// void	update_signals(void)
// {
// 	struct sigaction	s_sa;

// 	sigemptyset(&s_sa.sa_mask);
// 	sigaddset(&s_sa.sa_mask, SIGINT); 
// 	sigaddset(&s_sa.sa_mask, SIGQUIT);
// 	s_sa.sa_flags = SA_SIGINFO;
// 	s_sa.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &s_sa, NULL);
// 	sigaction(SIGQUIT, &s_sa, NULL);
// }

// void	init_signals(void)
// {
// 	struct sigaction	s_sa;

// 	sigemptyset(&s_sa.sa_mask);
// 	sigaddset(&s_sa.sa_mask, SIGINT); 
// 	sigaddset(&s_sa.sa_mask, SIGQUIT);
// 	s_sa.sa_flags = SA_SIGINFO;
// 	s_sa.sa_handler = &sigs_handler;
// 	sigaction(SIGINT, &s_sa, NULL);
// 	sigaction(SIGQUIT, &s_sa, NULL);
// }

void	init_signals(void)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;

	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT); 
	sigaddset(&s_si.sa_mask, SIGQUIT);
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_handler = &sigs_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
}
