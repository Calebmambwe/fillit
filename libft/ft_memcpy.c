/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manovill <manovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:06:42 by manovill          #+#    #+#             */
/*   Updated: 2019/10/13 18:50:51 by manovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmp_dst;
	char	*tmp_src;

	if (n == 0 || dst == src)
		return (dst);
	tmp_dst = (char *)dst;
	tmp_src = (char *)src;
	while (--n)
		*tmp_dst++ = *tmp_src++;
	*tmp_dst = *tmp_src;
	return (dst);
}
