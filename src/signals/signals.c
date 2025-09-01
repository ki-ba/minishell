/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:09:11 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/01 14:30:18 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include "prompt.h"
#include "color.h"

int	g_signal;

static void	sigint_handler(int sig)
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

static void	sig_handler_cmd(int sig)
{
	g_signal = sig;
	rl_on_new_line();
}

static void	sig_handler_redir(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_signal = sig;
}

void	update_signals(int cmd)
{
	struct sigaction	s_sa;
	struct sigaction	s_si;

	sigemptyset(&s_sa.sa_mask);
	sigemptyset(&s_si.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGINT);
	sigaddset(&s_si.sa_mask, SIGQUIT);
	s_sa.sa_flags = SA_RESTART;
	s_si.sa_flags = SA_RESTART;
	if (cmd)
	{
		s_sa.sa_handler = &sig_handler_cmd;
		s_si.sa_handler = &sig_handler_cmd;
	}
	else
	{
		s_sa.sa_handler = &sig_handler_redir;
		s_si.sa_handler = SIG_IGN;
	}
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
	s_sa.sa_flags = SA_RESTART;
	s_si.sa_flags = SA_RESTART;
	s_sa.sa_handler = &sigint_handler;
	s_si.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_si, NULL);
}
