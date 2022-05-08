/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:34:31 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/08 23:59:58 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*verif(char *s);

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, char *src, size_t size);

char	*ft_strnldup(char *s1);

char	*ft_strdup(const char *s1);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

#endif

