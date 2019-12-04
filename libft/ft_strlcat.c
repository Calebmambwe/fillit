/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manovill <manovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:02:54 by manovill          #+#    #+#             */
/*   Updated: 2019/10/11 21:03:31 by manovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t max)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i] && i < max)
		i++;
	while (src[j] && (i + j + 1) < max)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < max)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
