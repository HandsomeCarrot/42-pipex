/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:06:42 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:37 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints a percent sign.
 *
 * This function outputs a percent sign (%) to the standard output.
 *
 * @return The number of characters printed, which is always 1.
 */
int	print_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}
