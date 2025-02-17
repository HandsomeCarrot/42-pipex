/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:27:03 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:42 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the number of digits in an integer.
 *
 * This function determines the length of an integer by counting the number
 * of digits it contains. It handles both positive and negative integers.
 *
 * @param i The integer whose length is to be calculated.
 * @return The number of digits in the integer.
 */
static int	num_len(int i)
{
	long int	l;
	int			len;

	l = i;
	len = 1;
	if (i < 0)
		len++;
	while (l > 9 || l < -9)
	{
		l /= 10;
		len++;
	}
	return (len);
}

/**
 * @brief Prints an integer from the variable argument list.
 *
 * This function retrieves an integer from the provided variable argument list
 * and prints it to the standard output.
 *
 * @param args The variable argument list containing the integer to be printed.
 * @return The number of characters printed.
 */
int	print_int(va_list args)
{
	int	i;

	i = va_arg(args, int);
	ft_putnbr_fd(i, 1);
	return (num_len(i));
}
