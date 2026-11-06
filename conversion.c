#include "ft_printf.h"

int	ft_conversion_di(int s)
{
	int	l;

	l = 0;
	ft_putnbr_fd (s, 1);
	if (s == -2147483648)
		return (11);
	if (s < 0)
	{
		l++;
		s = s * -1;
	}
	if ((s >= 0) && (s <= 9))
		return (l + 1);
	while (s >= 10)
	{
		s = s / 10;
		l++;
	}
	l++;
	return (l);
}

int	ft_conversion_uxx(unsigned int s, char c)
{
	if (c == 'x')
	{
		ft_putnbr_unsignedint_base(s, "0123456789abcdef");
		return (count_l(s, 16));
	}
	if (c == 'X')
	{
		ft_putnbr_unsignedint_base(s, "0123456789ABCDEF");
		return (count_l(s, 16));
	}
	if (c == 'u')
	{
		ft_putnbr_unsigned(s);
		return (count_l(s, 10));
	}
	return (0);
}

int	ft_conversion_s(char *s)
{
	if (s == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_conversion_c(int s)
{
	write(1, &s, 1);
	return (1);
}

int	ft_conversion_p(void *s)
{
	unsigned long	news;
	int				l;

	if (s == NULL)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	news = (unsigned long)s;
	write(1, "0x", 2);
	l = 2;
	ft_putnbr_unsignedlong_16(news, "0123456789abcdef");
	if (news <= 15)
		return (l + 1);
	while (news >= 16)
	{
		news = news / 16;
		l++;
	}
	l++;
	return (l);
}
