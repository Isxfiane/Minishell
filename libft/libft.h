/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyacoubi <nyacoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:59:17 by nyacoubi          #+#    #+#             */
/*   Updated: 2024/06/04 11:17:10 by nyacoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFFER_SIZE 1000

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
char	*edited_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*remove_part(char *linepart);
char	*pick_buffer(int fd, char *linepart);
int		ft_toupper(int c);
char	*extract_line(char *linepart);
void	ft_cpyforjoin(char *str, char *s1, char *s2, size_t i);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t	len);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *s, ...);
int		print_char(int c);
int		print_nbr(int n);
int		print_str(char *str);
int		argset(char argtype, va_list args);
int		print_uint(size_t n);
int		print_hexlow(size_t nbr);
int		print_hexup(size_t nbr);
int		count_fdigits(long long n);
int		count_hexdigits(size_t hexnbr);
int		print_ptr(size_t ptr);
int		argcheck(const char *s, va_list args);
void	free_tab(char **tab);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_tablen(char **tab);
int		err_print_char(int c);
int		err_print_str(char *str);
int		err_print_hexlow(size_t	nbr);
int		err_print_hexup(size_t nbr);
int		err_print_ptr(size_t ptr);
int		err_argset(char argtype, va_list args);
int		err_argcheck(const char *s, va_list args);
int		ft_printf_err(const char *s, ...);
int		err_print_uint(size_t nbr);
int		err_print_nbr(int nbr);
char	*ft_str2cpy(char *src, char *src2, char *dest, ssize_t lenbuff);
int		ft_strfind(char *str, char c);

#endif
