/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:49 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs a hexadecimal representation of a number.
 *
 * This function takes an integer number and converts it to its hexadecimal
 * representation using the provided base. The length of the output is
 * updated in the provided length pointer.
 *
 * @param num The integer number to be converted to hexadecimal.
 * @param len Pointer to an integer where the length of the output will be
 *  stored.
 * @param base The base string to be used for conversion
 *  (e.g., "0123456789abcdef" for lowercase).
 */
void	put_hex(unsigned long num, int *len, char *base)
{
	if (num == 0)
		return ;
	put_hex((num / 16), len, base);
	(*len)++;
	ft_putchar_fd(base[(num % 16)], 1);
}

/**
 * @brief Prints a hexadecimal number.
 *
 * This function retrieves an argument from the provided va_list and prints it
 * as a hexadecimal number. The format of the hexadecimal output is determined
 * by the character 'c'. Typically, 'c' can be 'x' for lowercase hexadecimal
 * or 'X' for uppercase hexadecimal.
 *
 * @param args A va_list containing the arguments.
 * @param c A character specifying the format of the hexadecimal output.
 *
 * @return The number of characters printed.
 */
int	print_hex(va_list args, const char c)
{
	int				len;
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	len = 0;
	if (c == 'x')
		put_hex(num, &len, "0123456789abcdef");
	else
		put_hex(num, &len, "0123456789ABCDEF");
	return (len);
}
