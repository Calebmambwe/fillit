/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manovill <manovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:32:59 by manovill          #+#    #+#             */
/*   Updated: 2019/10/13 19:00:53 by manovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*h;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	h = (char *)s1;
	if (!(s2_len = ft_strlen(s2)))
		return (h);
	i = 0;
	while (h[i])
	{
		j = 0;
		while (s2[j] && s2[j] == h[i + j])
			j++;
		if (j == s2_len)
			return (&h[i]);
		i++;
	}
	return (NULL);
}
