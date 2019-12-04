/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manovill <manovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:37:08 by manovill          #+#    #+#             */
/*   Updated: 2019/10/13 19:01:55 by manovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char	*h;
	size_t	s2_len;
	size_t	j;
	size_t	i;

	h = (char *)s1;
	if (!(s2_len = ft_strlen(s2)))
		return (h);
	if (ft_strlen(s1) < s2_len || len < s2_len)
		return (NULL);
	i = 0;
	while (h[i] && i <= len - s2_len)
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
