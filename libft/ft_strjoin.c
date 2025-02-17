/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:41:58 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 14:01:39 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Joins two strings together.
 *
 * @param s1 The first string to be joined.
 * @param s2 The second string to be joined.
 * @return The newly allocated string containing the joined strings,
 *         or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	result_len;
	size_t	pos;

	result_len = ft_strlen(s1) + ft_strlen(s2);
	if (result_len == 0)
		return (ft_strdup(""));
	result = malloc((result_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	pos = 0;
	while (s1[pos])
	{
		result[pos] = s1[pos];
		pos++;
	}
	while (*s2)
	{
		result[pos] = *s2;
		s2++;
		pos++;
	}
	result[pos] = '\0';
	return (result);
}

/*#include <stdio.h>
int	main(void)
{
	char *str = "Hello,";
	char *str2 = " Worlds!";
	printf("%s\n", ft_strjoin(str, str2));
}*/