/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:02:05 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:15:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of the character 'c'
 *  (converted to an unsigned char)
 * in the first 'n' bytes of the memory area pointed to by 's'.
 *
 * @param s - Pointer to the memory area to be searched.
 * @param c - Character to be located.
 * @param n - Number of bytes to be searched.
 * @return A pointer to the first occurrence of 'c' in the memory area pointed
 *  to by 's',
 *         or NULL if the character is not found within the first 'n' bytes.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uns_s;
	unsigned char	uns_c;

	uns_s = (unsigned char *)s;
	uns_c = c;
	while (n > 0)
	{
		if (*uns_s == uns_c)
			return (uns_s);
		uns_s++;
		n--;
	}
	return (NULL);
}
