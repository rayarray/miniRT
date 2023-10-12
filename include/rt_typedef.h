/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_typedef.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:45:14 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/11 20:14:56 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPEDEF_H
# define RT_TYPEDEF_H

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

/* // Vector == point in this project, right?
typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord; */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

#endif