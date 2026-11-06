#include "ft_printf.h"

void	ft_putnbr_unsigned(unsigned int n)
{
	unsigned int	nbr;

	if (n == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (n >= 10)
		ft_putnbr_unsigned(n / 10);
	nbr = (n % 10) + '0';
	write (1, &nbr, 1);
}
