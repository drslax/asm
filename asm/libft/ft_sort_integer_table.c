/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <anas.elouargui@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 07:00:22 by aelouarg          #+#    #+#             */
/*   Updated: 2018/09/04 07:09:06 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_integer_table(int *tab, int size)
{
	int		i;
	int		j;
	int		tmp;
	int		c;

	i = 0;
	while (i < size - 1)
	{
		j = i;
		c = j;
		while (j < size)
		{
			if (tab[c] > tab[j + 1])
				c = j + 1;
			j++;
		}
		tmp = tab[i];
		tab[i] = tab[c];
		tab[c] = tmp;
		i++;
	}
}
