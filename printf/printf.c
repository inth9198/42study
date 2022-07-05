
int	ft_printf(const char *s, ...)
{
	va_list args;
	int		st[3];
	char	*input;

	st[0] = 0;
	st[1] = 1;
	input = (char *)s;
	va_start(args, s);
	while (input[st[0]])
	{
		if (input[st[0]] == '%' && _check("cspdiuxX%", input[st[0] + 1], 1, 0))
		{
			if (_check("cdi", input[st[0] + 1], 1, 42))
				st[2] = va_arg(args, int);
			if (_check("uxX", input[st[0] + 1], 1, 42))
				st[2] = va_arg(args, unsigned int);
			st[1] += _print(input[st[0] + 1], args, st);
			st[0] += 2;
		}
		else
			st[1] += write(1, &input[st[0]++], 1);
	}
	va_end(args);
	return (st[i]);
}
