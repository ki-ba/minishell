/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:55:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 14:01:22 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern int	g_signal;

void	sigint_handler(int sig);
void	sig_handler_cmd(int sig);
void	sig_handler_redir(int sig);
void	update_signals(int cmd);
void	init_signals(void);

#endif
