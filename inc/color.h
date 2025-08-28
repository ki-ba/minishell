/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:39:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/26 15:56:18 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

//Background color
# define BG_BLACK   "\001\e[40m\002"
# define BG_RED     "\001\e[41m\002"
# define BG_GREEN   "\001\e[42m\002"
# define BG_YELLOW  "\001\e[43m\002"
# define BG_BLUE    "\001\e[44m\002"
# define BG_MAGENTA "\001\e[45m\002"
# define BG_CYAN    "\001\e[46m\002"
# define BG_WHITE   "\001\e[47m\002"

# define BG_BRIGHT_BLACK   "\001\e[100m\002"
# define BG_BRIGHT_RED     "\001\e[101m\002"
# define BG_BRIGHT_GREEN   "\001\e[102m\002"
# define BG_BRIGHT_YELLOW  "\001\e[103m\002"
# define BG_BRIGHT_BLUE    "\001\e[104m\002"
# define BG_BRIGHT_MAGENTA "\001\e[105m\002"
# define BG_BRIGHT_CYAN    "\001\e[106m\002"
# define BG_BRIGHT_WHITE   "\001\e[107m\002"

//text color
# define FG_BLACK   "\001\e[30m\002"
# define FG_RED     "\001\e[31m\002"
# define FG_GREEN   "\001\e[0;32m\002"
# define FG_YELLOW  "\001\e[33m\002"
# define FG_BLUE    "\001\e[34m\002"
# define FG_MAGENTA "\001\e[35m\002"
# define FG_CYAN    "\001\e[36m\002"
# define FG_WHITE   "\001\e[37m\002"

# define FG_BRIGHT_BLACK   "\001\e[90m\002"
# define FG_BRIGHT_RED     "\001\e[91m\002"
# define FG_BRIGHT_GREEN   "\001\e[92m\002"
# define FG_BRIGHT_YELLOW  "\001\e[93m\002"
# define FG_BRIGHT_BLUE    "\001\e[94m\002"
# define FG_BRIGHT_MAGENTA "\001\e[95m\002"
# define FG_BRIGHT_CYAN    "\001\e[96m\002"
# define FG_BRIGHT_WHITE   "\001\e[97m\002"

//other text modifier
# define BOLD 	"\001\e[1m\002"
# define ITALIC "\001\e[3m\002"

//reset text
# define RESET 	"\001\e[0m\002"

#endif
