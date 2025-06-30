 #include "ft_printf.h"
 #include <stdlib.h>

 static void init_format(t_format *f)
 {
     f->flags_minus = 0;
     f->flags_zero = 0;
     f->flags_hash = 0;
     f->flags_space = 0;
     f->flags_plus = 0;
     f->width = 0;
     f->precision = -1;
     f->specifier = 0;
 }

 static void parse_format(const char *fmt, int *i, t_format *f)
 {
     init_format(f);
     (*i)++;
     while (fmt[*i] == '-' || fmt[*i] == '0' || fmt[*i] == '#' ||
            fmt[*i] == ' ' || fmt[*i] == '+')
     {
         if (fmt[*i] == '-')
             f->flags_minus = 1;
         else if (fmt[*i] == '0')
             f->flags_zero = 1;
         else if (fmt[*i] == '#')
             f->flags_hash = 1;
         else if (fmt[*i] == ' ')
             f->flags_space = 1;
         else if (fmt[*i] == '+')
             f->flags_plus = 1;
         (*i)++;
     }
     if (fmt[*i] >= '0' && fmt[*i] <= '9')
     {
         f->width = 0;
         while (fmt[*i] >= '0' && fmt[*i] <= '9')
             f->width = f->width * 10 + (fmt[(*i)++] - '0');
     }
     if (fmt[*i] == '.')
     {
         (*i)++;
         f->precision = 0;
         while (fmt[*i] >= '0' && fmt[*i] <= '9')
             f->precision = f->precision * 10 + (fmt[(*i)++] - '0');
     }
     f->specifier = fmt[*i];
 }

 static char *utoa_base(unsigned long long num, const char *base)
 {
     unsigned long long tmp = num;
     int base_len = ft_strlen((char *)base);
     int len = 1;
     while (tmp >= (unsigned long long)base_len)
     {
         tmp /= base_len;
         len++;
     }
     char *str = malloc(len + 1);
     if (!str)
         return NULL;
     str[len] = '\0';
     while (len--)
     {
         str[len] = base[num % base_len];
         num /= base_len;
     }
     return str;
 }

 static int put_chars(char c, int count)
 {
     int sum = 0;
     while (count-- > 0)
         sum += ft_putcharf(c);
     return sum;
 }

 static int handle_char(t_format *f, char c)
 {
     int sum = 0;
     int pad = f->width > 1 ? f->width - 1 : 0;
     if (f->flags_minus)
     {
         sum += ft_putcharf(c);
         sum += put_chars(' ', pad);
     }
     else
     {
         char fill = f->flags_zero ? '0' : ' ';
         sum += put_chars(fill, pad);
         sum += ft_putcharf(c);
     }
     return sum;
 }

 static int handle_str(t_format *f, char *s)
 {
     int sum = 0;
     int len, idx;
     if (!s)
         s = "(null)";
     len = ft_strlen(s);
     if (f->precision >= 0 && f->precision < len)
         len = f->precision;
     if (f->flags_minus)
     {
         for (idx = 0; idx < len; idx++)
             sum += ft_putcharf(s[idx]);
         sum += put_chars(' ', f->width - len);
     }
     else
     {
         sum += put_chars(' ', f->width - len);
         for (idx = 0; idx < len; idx++)
             sum += ft_putcharf(s[idx]);
     }
     return sum;
 }

 static int handle_int(t_format *f, int n)
 {
     int sum = 0;
     unsigned int un;
     char *str;
     int len, ppad, spad;
     char sign = 0;

     if (n < 0)
         un = -(long)n, sign = '-';
     else
         un = n;
     if (f->precision == 0 && n == 0)
         str = ft_strdup("");
     else
         str = ft_itoa(un);
     if (!str)
         return 0;
     len = ft_strlen(str);
     if (f->precision >= 0)
         ppad = f->precision > len ? f->precision - len : 0;
     else if (f->flags_zero && !f->flags_minus)
         ppad = f->width - (sign ? 1 : 0) - len;
     else
         ppad = 0;
     if (ppad < 0)
         ppad = 0;
     if (n < 0)
         sign = '-';
     else if (f->flags_plus)
         sign = '+';
     else if (f->flags_space)
         sign = ' ';
     else
         sign = 0;
     spad = f->width - (sign ? 1 : 0) - ppad - len;
     if (spad < 0)
         spad = 0;
     if (f->flags_minus)
     {
         if (sign)
             sum += ft_putcharf(sign);
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
         sum += put_chars(' ', spad);
     }
     else
     {
         sum += put_chars(' ', spad);
         if (sign)
             sum += ft_putcharf(sign);
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
     }
     free(str);
     return sum;
 }

 static int handle_uint(t_format *f, unsigned int n)
 {
     int sum = 0;
     char *str;
     int len, ppad, spad;

     if (f->precision == 0 && n == 0)
         str = ft_strdup("");
     else
         str = utoa_base(n, "0123456789");
     if (!str)
         return 0;
     len = ft_strlen(str);
     if (f->precision >= 0)
         ppad = f->precision > len ? f->precision - len : 0;
     else if (f->flags_zero && !f->flags_minus)
         ppad = f->width - len;
     else
         ppad = 0;
     if (ppad < 0)
         ppad = 0;
     spad = f->width - ppad - len;
     if (spad < 0)
         spad = 0;
     if (f->flags_minus)
     {
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
         sum += put_chars(' ', spad);
     }
     else
     {
         sum += put_chars(' ', spad);
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
     }
     free(str);
     return sum;
 }

 static int handle_hex(t_format *f, unsigned int n, const char *base, char prefix)
 {
     int sum = 0;
     char *str;
     int len, ppad, spad;
     int prefix_len = (f->flags_hash && n) ? 2 : 0;

     if (f->precision == 0 && n == 0)
         str = ft_strdup("");
     else
         str = utoa_base(n, base);
     if (!str)
         return 0;
     len = ft_strlen(str);
     if (f->precision >= 0)
         ppad = f->precision > len ? f->precision - len : 0;
     else if (f->flags_zero && !f->flags_minus)
         ppad = f->width - prefix_len - len;
     else
         ppad = 0;
     if (ppad < 0)
         ppad = 0;
     spad = f->width - prefix_len - ppad - len;
     if (spad < 0)
         spad = 0;
     if (f->flags_minus)
     {
         if (prefix_len)
         {
             sum += ft_putcharf('0');
             sum += ft_putcharf(prefix);
         }
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
         sum += put_chars(' ', spad);
     }
     else
     {
         sum += put_chars(' ', spad);
         if (prefix_len)
         {
             sum += ft_putcharf('0');
             sum += ft_putcharf(prefix);
         }
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
     }
     free(str);
     return sum;
 }

 static int handle_ptr(t_format *f, void *p)
 {
     unsigned long n = (unsigned long)p;
     int sum = 0;
     char *str;
     int len, ppad, spad;

     str = utoa_base(n, "0123456789abcdef");
     if (!str)
         return 0;
     len = ft_strlen(str);
     if (f->precision >= 0)
         ppad = f->precision > len ? f->precision - len : 0;
     else
         ppad = 0;
     spad = f->width - 2 - ppad - len;
     if (spad < 0)
         spad = 0;
     if (f->flags_minus)
     {
         sum += ft_putcharf('0');
         sum += ft_putcharf('x');
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
         sum += put_chars(' ', spad);
     }
     else
     {
         sum += put_chars(' ', spad);
         sum += ft_putcharf('0');
         sum += ft_putcharf('x');
         sum += put_chars('0', ppad);
         for (int i = 0; i < len; i++)
             sum += ft_putcharf(str[i]);
     }
     free(str);
     return sum;
 }

 static int handle_format(t_format *f, va_list args)
 {
     if (f->specifier == 'c')
         return handle_char(f, va_arg(args, int));
     if (f->specifier == 's')
         return handle_str(f, va_arg(args, char *));
     if (f->specifier == 'p')
         return handle_ptr(f, va_arg(args, void *));
     if (f->specifier == 'd' || f->specifier == 'i')
         return handle_int(f, va_arg(args, int));
     if (f->specifier == 'u')
         return handle_uint(f, va_arg(args, unsigned int));
     if (f->specifier == 'x')
         return handle_hex(f, va_arg(args, unsigned int), "0123456789abcdef", 'x');
     if (f->specifier == 'X')
         return handle_hex(f, va_arg(args, unsigned int), "0123456789ABCDEF", 'X');
     if (f->specifier == '%')
         return handle_char(f, '%');
     return 0;
 }

 int ft_printf(const char *format, ...)
 {
     va_list args;
     int sum = 0;
     int i = 0;
     t_format f;

     va_start(args, format);
     while (format[i])
     {
         if (format[i] == '%')
         {
             parse_format(format, &i, &f);
             sum += handle_format(&f, args);
             i++;
         }
         else
             sum += ft_putcharf(format[i++]);
     }
     va_end(args);
     return sum;
 }
