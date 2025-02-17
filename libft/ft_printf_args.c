/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:29:11 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:53 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints a formatted argument based on the format specifier.
 *
 * This function processes the format specifier pointed to by `format` and
 * retrieves the corresponding argument from the `args` list. It then prints
 * the argument according to the specified format.
 *
 * @param format A pointer to the format specifier string. The pointer is
 *               updated to point to the character following the format
 *  specifier.
 * @param args   A va_list of arguments to be formatted and printed.
 *
 * @return The number of characters printed.
 */
int	print_arg(const char **format, va_list args)
{
	size_t	arg_len;

	arg_len = 0;
	if (**format == 'c')
		arg_len = print_char(args);
	else if (**format == 's')
		arg_len = print_str(args);
	else if (**format == 'p')
		arg_len = print_ptr(args);
	else if (**format == 'd' || **format == 'i')
		arg_len = print_int(args);
	else if (**format == 'u')
		arg_len = print_uint(args);
	else if (**format == 'x' || **format == 'X')
		arg_len = print_hex(args, **format);
	else if (**format == '%')
		arg_len = print_percent();
	else if (**format == '\0')
		return (-1);
	if (**format != '\0')
		(*format)++;
	return (arg_len);
}
