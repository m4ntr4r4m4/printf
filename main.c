#include <stdio.h>
#include "ft_printf.h"
int		main()
{

	char	str[]= "hello ";
	char	str1[]= "my ";
	char	str2[]= "frind ";
	char	str3[]= "!";
	char 	*c = "x";
	char 	v = ' ';
	char 	b = '#';
	char 	n = '%';
	char 	m = 'y';
	
	ft_printf("%d hello%% %s  %x  %c %p\n", 42, "my frind!", 42  ,'x', &c);
	printf("%d hello%% %s %x %c %p\n", 42, "my frind!", 42 ,'x', &c);
//	ft_printf("%d%s%c%u\n", 42, "hello there", 'c', 42);
	return (0);

}
