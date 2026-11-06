#include "ft_printf.h"

int	count_l(unsigned int s, unsigned int nbrbase)
{
	int	l;

	l = 0;
	if (s <= nbrbase - 1)
		return (1);
	while (s >= nbrbase)
	{
		s = s / nbrbase;
		l++;
	}
	l++;
	return (l);
}
