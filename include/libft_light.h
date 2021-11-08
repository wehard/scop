/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_light.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:38:26 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:21:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIGHT_H
# define LIBFT_LIGHT_H

# include <stdlib.h>

char		**ft_strsplit(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcat(char *dest, char *src);
void		ft_putendl_fd(char const *s, int fd);
int			ft_nwords(char *str, char delim);
void		*ft_memcpy(void *dst, const void *src, size_t n);
double		ft_deg_to_rad(double deg);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char const *s, int fd);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
double		ft_strtod(char *s);
int			ft_isdigit(int c);
char		*ft_strtok(char *src, const char *delims);
void		ft_putendl(char const *s);
void		ft_putstr(char const *s);
void		*ft_memalloc(size_t size);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
void		ft_putchar(char c);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strstr(const char *haystack, const char *needle);

#endif
