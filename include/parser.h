/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:02:32 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 21:28:16 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define BASES_BUFFER_SIZE 128
# define REALLOC_FACTOR 2
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "rt_typedef.h"
# include "element.h"
# include "get_next_line.h"
# include "rt_conversions.h"

static const char	delims[3] = " \t";

struct s_elem_base
{
	t_elem_type	type;
	char		**args;
};

// Scene_reader.c
struct s_elem_base	*get_scene(const char *filename);

// Utility functions
char	**free_strarray(char ***array);
int		rt_realloc(unsigned char **buf, size_t *bufsize, int factor);
char	**rt_split(char const *s, const char *c);

// Line_parser.c
int	parse_line(const char *line, struct s_elem_base *elem);

#endif