/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:51:53 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:14 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Validates the format argument.
 *
 * This function checks if the provided format string is a valid argument
 * for the printf function. It ensures that the format string adheres to
 * the expected structure and contains valid format specifiers.
 *
 * @param format The format string to be validated.
 * @return An integer indicating the validity of the format string.
 *         Returns 1 if the format is valid, 0 otherwise.
 */
static int	valid_arg(const char **format)
{
	const char	*specifiers;

	specifiers = "cspdiuxX%";
	if (**format == '%' && ft_strchr(specifiers, *(*format + 1)))
	{
		(*format)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Custom printf function to format and print data.
 *
 * This function mimics the behavior of the standard printf function,
 * allowing formatted output to the standard output stream.
 *
 * The only supported format specifiers are: c, s, d, i, u, x, X, % and p.
 *
 * @param format A constant character pointer to a null-terminated string
 *               that specifies the format of the output. The format string
 *               can contain ordinary characters, which are copied to the
 *               output, and format specifiers, which are replaced by the
 *               values of the corresponding arguments.
 * @param ...    A variable number of arguments that correspond to the format
 *               specifiers in the format string.
 *
 * @return The number of characters printed (excluding the null byte used to
 *         end output to strings), or a negative value if an output error
 *  occurs.
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		str_len;
	int		arg_len;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	str_len = 0;
	while (*format)
	{
		arg_len = 1;
		if (valid_arg(&format))
			arg_len = print_arg(&format, args);
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
		}
		if (arg_len < 0)
			str_len = -1;
		if (str_len >= 0)
			str_len += arg_len;
	}
	va_end(args);
	return (str_len);
}
