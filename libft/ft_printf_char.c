/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:12:53 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_printf_char.c
 * @brief This file contains the implementation of the print_char function.
 *
 * The print_char function is responsible for printing a character
 * passed as an argument through a variadic list.
 *
* @param args A variadic list of arguments from which the character to be printed
 is extracted.
 *
 * @return The number of characters printed.
 */
int	print_char(va_list args)
{
	unsigned char	c;

	c = va_arg(args, int);
	write(1, &c, sizeof(unsigned char));
	return (1);
}
