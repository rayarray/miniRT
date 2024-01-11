/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:01:56 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:43 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif
# ifndef LINE_SIZE
#  define LINE_SIZE 80
# endif
# include <stdlib.h>

typedef struct s_reader
{
	unsigned int		head;
	unsigned int		tail;
	const int			fd;
	char				*buf;
}						t_reader;

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

t_list	*ft_lstnew(void *content);

void	ft_lstdelone(t_list **lst, void *comparee, int (*matcher)(void*, void*),
			void (*del)(void*));

void	*ft_lstsearch(t_list *lst, void *comparee,
			int (*matcher)(void*, void*));

int		reader_match(int *fd, t_reader *reader);

size_t	reallocate_string(char **c, size_t oldsize, size_t newsize);

char	*get_next_line(int fd);

#endif
