/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manovill <manovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:36:37 by manovill          #+#    #+#             */
/*   Updated: 2019/10/11 20:37:08 by manovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			j;

	i = -1;
	j = ft_strlen(s1);
	while (s2[i++ + 1] && (i < n))
		s1[j++] = s2[i];
	s1[j] = '\0';
	return (s1);
}
