#include "ft_printf.h"

int	ft_ifconversion(char c, va_list *arg, int l)
{
	if ((c == 'i') || (c == 'd'))
		l = l + ft_conversion_di(va_arg(*arg, int));
	if ((c == 'x') || (c == 'X') || (c == 'u'))
		l = l + ft_conversion_uxx(va_arg (*arg, unsigned int), c);
	if (c == 's')
		l = l + ft_conversion_s(va_arg(*arg, char *));
	if (c == 'c')
		l = l + ft_conversion_c(va_arg(*arg, int));
	if (c == 'p')
		l = l + ft_conversion_p(va_arg(*arg, void *));
	if (c == '%')
	{
		write (1, "%", 1);
		l++;
	}
	return (l);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		l;
	va_list	arg;

	i = 0;
	l = 0;
	va_start (arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			l = ft_ifconversion(format[i], &arg, l);
		}
		else
		{
			write (1, &format[i], 1);
			l++;
		}
		i++;
	}
	va_end(arg);
	return (l);
}
