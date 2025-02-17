/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:23:24 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:29 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints a string from the variable argument list.
 *
 * This function retrieves a string argument from the provided va_list
 * and prints it. It is typically used as part of a custom printf
 * implementation.
 *
 * @param args The variable argument list containing the string to print.
 * @return The number of characters printed.
 */
int	print_str(va_list args)
{
	const char	*str;
	int			len;

	str = va_arg(args, const char *);
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else
	{
		len = ft_strlen(str);
		ft_putstr_fd((char *)str, 1);
		return (len);
	}
}
