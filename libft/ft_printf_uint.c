/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:03:30 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs an unsigned integer to the standard output.
 *
 * This function takes an unsigned integer as input and prints it to the
 * standard output. It handles the conversion of the integer to its string
 * representation and ensures that the entire number is printed correctly.
 *
 * @param u The unsigned integer to be printed.
 */
static void	put_uint(unsigned int u)
{
	if (u > 9)
	{
		put_uint(u / 10);
	}
	ft_putchar_fd(('0' + (u % 10)), 1);
}

/**
 * @brief Prints an unsigned integer from the variable argument list.
 *
 * This function retrieves an unsigned integer from the provided
 * variable argument list and prints it.
 *
 * @param args The variable argument list containing the unsigned integer
 *  to print.
 * @return The number of characters printed.
 */
int	print_uint(va_list args)
{
	unsigned int	u;
	int				len;

	u = va_arg(args, unsigned int);
	put_uint(u);
	len = 1;
	while (u > 9)
	{
		u /= 10;
		len++;
	}
	return (len);
}
