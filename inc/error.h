/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:06:15 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 14:06:16 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

enum e_error
{
	SUCCESS = 0,
	ERR_ARGS = 301,
	ERR_PARSING,
	ERR_ALLOC,
	ERR_PRINT,
	ERR_FAIL
};

#endif
