/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:11:53 by vpoka             #+#    #+#             */
/*   Updated: 2024/12/09 16:15:33 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(va_list args)
{
	void			*ptr;
	unsigned long	num;
	int				len;

	ptr = va_arg(args, void *);
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	num = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	len = 2;
	put_hex(num, &len, "0123456789abcdef");
	return (len);
}
