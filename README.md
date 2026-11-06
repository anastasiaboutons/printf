*This project has been created as part of the 42 curriculum by anrassou.*

# ft_printf

## Description

ft_printf is a project of the 42 common core. The goal is to recode the `printf()` function of the libc, and to learn how variadic functions work in C: functions that can receive a variable number of arguments.

The project creates a static library, `libftprintf.a`, which contains the function:

```c
int ft_printf(const char *format, ...);
```

It writes the format string on the standard output, replaces each conversion with its argument, and returns the number of characters written. As the subject requires, it does not implement the buffer management of the original `printf()`: the characters are written directly with `write`.

The handled conversions are:

| Conversion | Argument read with `va_arg` | What is written |
| --- | --- | --- |
| `%c` | `int` | One character |
| `%s` | `char *` | A string, or `(null)` if the pointer is `NULL` |
| `%p` | `void *` | The address in lowercase hexadecimal after `0x`, or `(nil)` if the pointer is `NULL` |
| `%d` | `int` | A signed number in base 10 |
| `%i` | `int` | A signed number in base 10 |
| `%u` | `unsigned int` | An unsigned number in base 10 |
| `%x` | `unsigned int` | A number in lowercase hexadecimal |
| `%X` | `unsigned int` | A number in uppercase hexadecimal |
| `%%` | No argument | A percent sign |

The repository contains:

* `ft_printf.c`: the main function and the function that chooses the conversion.
* `conversion.c`: one function for each type of conversion.
* `count_l.c`: counts the digits of a number in a given base.
* `ft_putnbr_16.c`, `ft_putnbr_unsignedint.c`, `ft_putnbr_unsignedlong_16.c`: write unsigned numbers.
* `ft_printf.h`: the header, with the prototypes of all the functions.
* `libft/`: my Libft, with its own Makefile.
* `Makefile`: compiles the Libft and the project, and builds `libftprintf.a`.

Library description detailed:

### Main functions

#### ft_printf

`int ft_printf(const char *format, ...);`
Reads the format string and writes it on the standard output, replacing each conversion with the matching argument.

* `format`: the string to write, with its conversions.
* `...`: the values of the conversions.
* Returns the number of characters written.

#### ft_ifconversion

`int ft_ifconversion(char c, va_list *arg, int l);`
Looks at the letter after the `%`, reads the next argument with the right type, and calls the matching conversion function.

* `c`: the letter of the conversion.
* `arg`: the address of the `va_list` of `ft_printf`, so that each read moves the real position in the arguments.
* `l`: the number of characters already written.
* Returns `l` plus the number of characters written by the conversion.

### Conversion functions

#### ft_conversion_c

`int ft_conversion_c(int s);`
Writes one character.

* `s`: the character. It arrives as an `int`, because a `char` passed through `...` is promoted to `int`.
* Returns `1`.

#### ft_conversion_s

`int ft_conversion_s(char *s);`
Writes a string, or `(null)` if `s` is `NULL`.

* `s`: the string to write.
* Returns the number of characters written.

#### ft_conversion_di

`int ft_conversion_di(int s);`
Writes a signed number in base 10 with `ft_putnbr_fd`, then counts its characters, the minus sign included.

* `s`: the number to write.
* Returns the number of characters written.

#### ft_conversion_uxx

`int ft_conversion_uxx(unsigned int s, char c);`
Writes an unsigned number, choosing the base from the letter of the conversion.

* `s`: the number to write.
* `c`: the letter of the conversion: `u`, `x` or `X`.
* Returns the number of characters written.

#### ft_conversion_p

`int ft_conversion_p(void *s);`
Writes an address in lowercase hexadecimal after `0x`, or `(nil)` if `s` is `NULL`.

* `s`: the address to write.
* Returns the number of characters written.

### Helper functions

#### ft_putnbr_unsignedint_base

`void ft_putnbr_unsignedint_base(unsigned int n, char *base);`
Writes an unsigned number in the base given by the string `base`.

* `n`: the number to write.
* `base`: the string of digits of the base.
* Returns nothing.

#### ft_putnbr_unsigned

`void ft_putnbr_unsigned(unsigned int n);`
Writes an unsigned number in base 10.

* `n`: the number to write.
* Returns nothing.

#### ft_putnbr_unsignedlong_16

`void ft_putnbr_unsignedlong_16(unsigned long n, char *base);`
Writes an `unsigned long` in the base given by the string `base`. It is used for the addresses.

* `n`: the number to write.
* `base`: the string of digits of the base.
* Returns nothing.

#### count_l

`int count_l(unsigned int s, unsigned int nbrbase);`
Counts the digits needed to write a number in a given base.

* `s`: the number.
* `nbrbase`: the size of the base: `10` or `16`.
* Returns the number of digits.

## Algorithm and data structure

### Algorithm

`ft_printf` goes through the format string once, from the first character to the last, with an index `i`:

1. `va_start` places the `va_list` on the first variable argument.
2. If the character is not a `%`, it is written with `write`, and the counter increases by `1`.
3. If the character is a `%`, the index moves to the next letter, and `ft_ifconversion` handles the conversion. Its result becomes the new value of the counter.
4. At the end of the string, `va_end` closes the `va_list`, and the counter is returned.

There are two separate positions: `i` moves in the format string, and the `va_list` moves in the arguments. Each `va_arg` returns the next argument and moves to the following one, so nothing counts the arguments: each conversion of the format reads exactly one argument, except `%%`, which reads none.

Numbers are written with recursion. To write a number in a base, the function first calls itself with `n` divided by the size of the base, then writes the digit given by `n` modulo the size of the base. The digit on the right is calculated first but must be written last, and recursion gives this order without storing the digits.

### Choices

* **One function for each conversion**: the code stays short, and each function respects the limits of the Norm.
* **The same function for `%d` and `%i`**: they write the same result.
* **The same function for `%u`, `%x` and `%X`**: the three receive an `unsigned int`, and only the base changes.
* **`unsigned long` for `%p`**: an address uses 8 bytes, so it does not fit in an `unsigned int`, which uses 4 bytes. A `void *` cannot be used directly either, because calculations such as `/` and `%` are not allowed on a pointer.
* **The address of the `va_list`**: `ft_ifconversion` receives `va_list *` so that the position moves in `ft_printf` too, and not only in a copy.
* **`-2147483648` as a special case in `ft_conversion_di`**: its positive value does not fit in an `int`, so it cannot be turned into a positive number.

### Data structure

The project does not need a complex data structure, because the format is read once and the characters are written immediately:

* The format string is read directly, with an index.
* The `va_list` keeps the position in the variable arguments.
* A string such as `"0123456789abcdef"` is used as a lookup table: the digit calculated is the index of the character to write. One function can therefore write any base, and `x` and `X` only differ by the string they receive.
* An `int` counter keeps the number of characters written.

No memory is allocated with `malloc` by the conversions, so there is nothing to free.

## Instructions

To compile the library, run at the root of the repository:

```bash
make
```

This compiles the Libft and creates `libftprintf.a`. Other rules:

* `make clean`: removes the object files (`.o`) of the project and of the Libft.
* `make fclean`: also removes `libftprintf.a` and `libft.a`.
* `make re`: removes everything and compiles again.

To use the library, include the header in a program:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("%s has %d conversions", "ft_printf", 9);
	return (0);
}
```

Then compile the program with the library:

```bash
cc main.c libftprintf.a
```

## Resources

* The manual pages in the terminal: `man 3 printf` and `man 3 stdarg`.
* The Linux manual pages online.
* The project subject.

### AI usage

AI (Claude) was used:

* to write this README;
* to explain concepts: variadic functions.
