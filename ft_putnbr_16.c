#include "ft_printf.h"

void	ft_putnbr_unsignedint_base(unsigned int n, char *base)
{
	unsigned int	nbr;

	if (n == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (n >= 16)
		ft_putnbr_unsignedint_base((n / 16), base);
	nbr = base[n % 16];
	write (1, &nbr, 1);
}
