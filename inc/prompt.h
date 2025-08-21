/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:01:23 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/21 14:17:09 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_minishell	t_minishell;

char	*err_code(int error);
char	*create_prompt(t_minishell *ms);
