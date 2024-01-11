/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:32:14 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 18:01:40 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ret;

	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (str);
	ret = str;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	*str = 0;
	return (ret);
}
