/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:39:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/21 12:39:58 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

//Background color
# define BG_BLACK   "\033[40m"
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"

# define BG_BRIGHT_BLACK   "\033[100m"
# define BG_BRIGHT_RED     "\033[101m"
# define BG_BRIGHT_GREEN   "\033[102m"
# define BG_BRIGHT_YELLOW  "\033[103m"
# define BG_BRIGHT_BLUE    "\033[104m"
# define BG_BRIGHT_MAGENTA "\033[105m"
# define BG_BRIGHT_CYAN    "\033[106m"
# define BG_BRIGHT_WHITE   "\033[107m"

//text color
# define FG_BLACK   "\033[30m"
# define FG_RED     "\033[31m"
# define FG_GREEN   "\033[0;32m"
# define FG_YELLOW  "\033[33m"
# define FG_BLUE    "\033[34m"
# define FG_MAGENTA "\033[35m"
# define FG_CYAN    "\033[36m"
# define FG_WHITE   "\033[37m"

# define FG_BRIGHT_BLACK   "\033[90m"
# define FG_BRIGHT_RED     "\033[91m"
# define FG_BRIGHT_GREEN   "\033[92m"
# define FG_BRIGHT_YELLOW  "\033[93m"
# define FG_BRIGHT_BLUE    "\033[94m"
# define FG_BRIGHT_MAGENTA "\033[95m"
# define FG_BRIGHT_CYAN    "\033[96m"
# define FG_BRIGHT_WHITE   "\033[97m"

//other text modifier
# define BOLD 	"\033[1m"
# define ITALIC "\033[3m"

//reset text
# define RESET 	"\033[0m"

#endif
