#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *format, ...);
int		ft_conversion_di(int s);
int		ft_conversion_uxx(unsigned int s, char c);
int		ft_conversion_s(char *s);
int		ft_conversion_c(int s);
int		ft_conversion_p(void *s);
void	ft_putnbr_unsignedint_base(unsigned int n, char *base);
void	ft_putnbr_unsigned(unsigned int n);
void	ft_putnbr_unsignedlong_16(unsigned long n, char *base);
int		count_l(unsigned int s, unsigned int nbrbase);
int		ft_ifconversion(char c, va_list *arg, int l);

#endif
