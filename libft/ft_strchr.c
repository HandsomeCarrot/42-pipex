/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:50:40 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/08 21:45:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the character c in the string s.
 *
 * This function searches for the first occurrence of the character c
 *  (an unsigned char)
 * in the string pointed to by s. The terminating null character is considered
 *  to be part
 * of the string, so if c is '\0', the function will return a pointer to the
 *  terminator.
 *
 * @param s The string to be searched.
 * @param c The character to be located.
 * @return A pointer to the first occurrence of the character c in the
 *  string s, or NULL if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	char	*result;

	result = (char *)s;
	while (*result)
	{
		if (*result == (char)c)
			return (result);
		result++;
	}
	if (*result == (char)c)
		return (result);
	return (NULL);
}

/*#include <stdio.h>
int main(void)
{
	char *str = "AbcdeFghIjkLmnOpQrstuvwxYz";
	printf("%s\n", ft_strchr(str, 'F'));
}*/
