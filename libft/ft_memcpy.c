/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:42:26 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:14:05 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a block of memory from a source address to a destination address.
 *
 * @param dest The pointer to the destination address where the memory will be
 *  copied to.
 * @param src The pointer to the source address where the memory will be copied
 *  from.
 * @param n The number of bytes to be copied.
 * @return A pointer to the destination address.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			pos;
	unsigned char	*uns_dest;
	unsigned char	*uns_src;

	uns_dest = (unsigned char *)dest;
	uns_src = (unsigned char *)src;
	pos = 0;
	if (!dest && !src)
		return (NULL);
	while (pos < n)
	{
		uns_dest[pos] = uns_src[pos];
		pos++;
	}
	return (dest);
}

/* #include <stdio.h>
int	main(void)
{
	char arr[] = "Hello Brudi";
	char dest[50];
	ft_memcpy(dest, arr, 11 + 1);
	printf("%s\n", dest);
} */