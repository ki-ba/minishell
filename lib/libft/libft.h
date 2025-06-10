/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:06:45 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/10 12:20:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include "fcntl.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef enum bool
{
	FALSE,
	TRUE
}	t_bool;

// PRINTF INCLUDES

# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"
# define DECIMAL_BASE "0123456789"

# define FTPRINTF_FORMAT_SPECIFIERS "cspdiuxX"

# define SIGNED_FORMAT_SPECIFIERS "di"
# define UNSIGNED_FORMAT_SPECIFIERS "Xxu"

# define NUMERICAL_FORMAT_SPECIFIERS "diuxXp"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_iswhitespace(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_c(char str[], char c);
size_t				ft_strnlen(const char *str, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char big[], const char little[],
						size_t len);
int					ft_atoi(const char *nptr);
int					ft_atoi_base(const char *nptr, const char *base);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_isnumber(char c);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_striteri(char *s, void (f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_printf(const char *format, ...);
int					ft_is_in(const char c, const char *str);
int					ft_put_ul_base(unsigned long nbr, char *base, int size);
int					ft_putchar(char c);
int					ft_putnbr_base(int nbr, char *base, int size);
t_bool				ft_str_is_alnum(char str[]);
t_bool				ft_str_is_non_empty(char str[]);
void				ft_print_arr(char **arr);
void				ft_free_arr(char **arr);
int					get_arr_length(char **arr);
char				**duplicate_arr(char **arr);
void				str_arr_suffix(char **arr, char *suffix);
void				ft_multifree(int n_simple, int n_arr, ...);
char				*ft_concat(size_t n, ...);
void				heap_add_suffix(const char *suffix, char **s1);
char				*create_random_str(size_t len);

/* get_next_line.c */
char				*join_to_line(char *line[], char buffer[]);
char				*get_next_line(int fd);

/* get_next_line_utils.c */
char				*ft_strchr(const char *s, int c);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strnjoin(char *s1, char *s2, size_t n);
char				*ft_strncpy(char dst[], const char src[], size_t n);
#endif
