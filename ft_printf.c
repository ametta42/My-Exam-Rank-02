#include <stdarg.h>
#include <unistd.h>

#define min(A, B) (A < B ? A : B)
#define max(A, B) (A > B ? A : B)
#define ft_isnbr(A) ((A >= '0' && A <= '9') ? A : 0)

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_nbrlen(long long nbr, int base)
{
	int i = 1;
	while (nbr /= base)
		i++;
	return (i);
}

void	ft_putnbr_base(long long nbr, int *printed, char *ref_base, int base)
{
	if (nbr >= base)
	{
		ft_putnbr_base(nbr / base, printed, ref_base, base);
		ft_putnbr_base(nbr % base, printed, ref_base, base);
	}
	else
	{
		write(1, &ref_base[nbr], 1);
		printed++;
	}
}

void	ft_printnbr(long long nbr, int *printed, int width, int precs, char *ref_base)
{
	int base = ft_strlen(ref_base);
	int len = ft_nbrlen(nbr, base);

	if (nbr < 0)
		width--;
	while (width > (precs != -1 ? max(precs, len) : len))
	{
		write(1, " ", 1);
		width--;
		(*printed)++;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		(*printed)++;
		nbr = -nbr;
	}
	else if (nbr == 0 && precs == 0)
	{
		while (width > 0)
		{
			write(1, " ", 1);
			width--;
			(*printed)++;
		}
		return ;
	}
	while (precs > len)
	{
		write(1, "0", 1);
		(*printed)++;
		precs--;
	}
	ft_putnbr_base(nbr, printed, ref_base, base);
}

int		ft_printf(char *format, ...)
{
	va_list arg;
	int printed = 0, width, precs;

	va_start(arg, format);
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			format++;
			printed++;
		}
		else
		{
			format++;
			width = 0, precs = -1;
			while (ft_isnbr(*format))
			{
				width = width * 10 + (*format - '0');
				format++;
			}
			if (*format == '.')
			{
				format++;
				precs = 0;
				while (ft_isnbr(*format))
				{
					precs = precs * 10 + (*format + '0');
					format++;
				}
			}
			if (*format == 's')
			{
				char *str = va_arg(arg, char *);
				if (!str)
					str = "(null)";
				int len = ft_strlen(str);
				while (width > (precs != -1 ? min(len, precs) : len))
				{
					write(1, " ", 1);
					printed++;
					width--;
				}
				write(1, str, (precs != -1 ? min(len, precs) : len));
				printed += (precs != -1 ? min(len, precs) : len);
				format++;
			}
			else if (*format == 'd')
			{
				ft_printnbr(va_arg(arg, int), &printed, width, precs, "0123456789");
				format++;
			}
			else if (*format == 'x')
			{
				ft_printnbr(va_arg(arg, unsigned), &printed, width, precs, "0123456789abcdef");
				format++;
			}
			else
				printed = -1;
		}
		if (printed == -1)
			return (-1);
	}
	va_end(arg);
	return(printed);
}
