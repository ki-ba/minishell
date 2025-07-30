/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:55:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 12:56:33 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sigint_handler(int sig);
void	sig_handler_cmd(int sig);
void	sig_handler_redir(int sig);
void	update_signals(int cmd);
void	init_signals(void);

#endif
