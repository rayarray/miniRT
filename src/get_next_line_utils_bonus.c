/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:01:50 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if ((new_node) == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->content = content;
	return (new_node);
}

int	reader_match(int *fd, t_reader *reader)
{
	return (*fd == reader->fd);
}

void	ft_lstdelone(t_list **lst, void *comparee, int (*matcher)(void*, void*),
		void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL || (*matcher) == NULL || (*del) == NULL
		|| comparee == NULL)
		return ;
	if ((*matcher)(comparee, (*lst)->content))
	{
		(*del)((*lst)->content);
		(*lst)->content = NULL;
		temp = *lst;
		*lst = ((*lst)->next);
		temp->next = NULL;
		free(temp);
	}
	else if ((*lst)->next != NULL)
		ft_lstdelone(&(*lst)->next, comparee, (*matcher), (*del));
}

void	*ft_lstsearch(t_list *lst, void *comparee, int (*matcher)(void*, void*))
{
	if (lst == NULL)
		return (NULL);
	if ((*matcher)(comparee, lst->content))
		return (lst->content);
	return (ft_lstsearch(lst->next, comparee, (*matcher)));
}

size_t	reallocate_string(char **c, size_t oldsize, size_t newsize)
{
	size_t	i;
	char	*new_c;

	if (c == NULL)
		return (0);
	new_c = malloc (sizeof(char) * newsize);
	if (new_c == NULL)
		return (0);
	i = 0;
	while (i < oldsize)
	{
		new_c[i] = (*c)[i];
		i++;
	}
	free(*c);
	*c = new_c;
	return (newsize);
}
