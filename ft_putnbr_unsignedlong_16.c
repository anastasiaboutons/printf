#include "ft_printf.h"

void	ft_putnbr_unsignedlong_16(unsigned long n, char *base)
{
	unsigned long	nbr;

	if (n == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (n >= 16)
		ft_putnbr_unsignedlong_16((n / 16), base);
	nbr = base[(n % 16)];
	write (1, &nbr, 1);
}
