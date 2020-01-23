/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 00:31:38 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/23 00:31:53 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static  char    *ft_putnbr_base(unsigned long nbr, int base,
		char *basecontent, char *result)
{
	unsigned        long    nb;

	nb = nbr;
	if (nb >= (unsigned     long)base)
	{
		ft_putnbr_base(nb / base, base, basecontent, result + 1);
		ft_putnbr_base(nb % base, base, basecontent, result);
	}
	else
		*result = basecontent[nb];
	return (result);
}

char                    *ft_itoa_base(unsigned long n, int base, int cap)
{
	char                            *result;
	unsigned long           nbr;
	char                            basecontent[16];
	int                                     size;

	if (cap == 1)
		ft_strcpy(basecontent, "0123456789ABCDEF");
	else
		ft_strcpy(basecontent, "0123456789abcdef");
	nbr = n;
	size = 1;
	while (nbr /= base)
		size++;
	if ((result = (char*)malloc(sizeof(char) * (size + 1))))
	{
		ft_bzero(result, size + 1);
		result = ft_putnbr_base(n, base, basecontent, result);
		return (ft_strrev(result));
	}
	return (NULL);
}
