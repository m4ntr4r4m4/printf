# ft_printf

![Language: C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![42 School](https://img.shields.io/badge/42-project-000000?logo=42&logoColor=white)
![Norm](https://img.shields.io/badge/norm-compliant-success)
![Static Analysis](https://img.shields.io/badge/analysis-scan--build-blueviolet)

> A from-scratch reimplementation of the C standard library `printf`, packaged as the static library `libftprintf.a`.

## About

`ft_printf` recreates the behaviour of the standard `printf` function in C. It parses a
format string at runtime, consumes a variable number of arguments with `<stdarg.h>`, and
writes formatted output to standard output, returning the number of bytes written.

This is a **42 School** project. Its purpose is to practice the fundamentals behind
formatted output: variadic functions, format-string parsing, base conversion, and field
padding (width / precision / flags). The code is organised as a small **dispatch +
handler** pipeline so that each conversion lives in its own focused function.

## Features

- **Conversions:** `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, and the literal `%%`
- **Flags:** `-` (left-justify), `0` (zero-pad), `#` (alternate form), ` ` (space), `+` (force sign)
- **Field modifiers:** minimum field **width** and **precision** (`.`)
- **Graceful NULL handling:** `%s` prints `(null)`, `%p` prints `(nil)`
- Built as a reusable static library, compiled `-Wall -Werror -Wextra` and clean under the 42 Norm

## Supported conversions

| Specifier | Description |
|-----------|-------------|
| `%c` | A single character |
| `%s` | A string of characters (`NULL` → `(null)`) |
| `%d` | A signed decimal integer |
| `%i` | A signed decimal integer (alias of `%d`) |
| `%u` | An unsigned decimal integer |
| `%x` | An unsigned integer in lowercase hexadecimal (`0-9`, `a-f`) |
| `%X` | An unsigned integer in uppercase hexadecimal (`0-9`, `A-F`) |
| `%p` | A pointer address in hex, prefixed `0x` (`NULL` → `(nil)`) |
| `%%` | A literal percent sign |

## Flags & modifiers

| Token | Meaning |
|-------|---------|
| `-` | Left-justify within the field width |
| `0` | Pad numbers with leading zeros instead of spaces |
| `#` | Alternate form — prefix non-zero hex with `0x` / `0X` |
| ` ` (space) | Prepend a space to non-negative signed numbers |
| `+` | Always print a sign (`+` or `-`) for signed numbers |
| `width` | Minimum number of characters to output |
| `.precision` | Max characters for strings / minimum digits for numbers |

## Build

The project compiles to the static library **`libftprintf.a`** using `gcc` with
`-Wall -Werror -Wextra -g`.

```bash
make          # build libftprintf.a (alias: make bonus)
make clean    # remove object files
make fclean   # remove object files and libftprintf.a
make re       # full rebuild (fclean + all)
make analyze  # run the Clang static analyzer (scan-build) into clang-analyzer-report/
```

> The library links against [`libft`](https://github.com/m4ntr4r4m4) — the build produces
> `libft.a` first and appends the `ft_printf` objects into the final archive.

## Usage

Include the header and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    ft_printf("Hello, %s!\n", "world");
    ft_printf("char: %c | int: %d | hex: %#x\n", 'A', 42, 255);
    ft_printf("padded: |%-10s|%05d|\n", "left", 7);
    ft_printf("pointer: %p\n", (void *)&len);

    len = ft_printf("returns the byte count\n");
    ft_printf("wrote %d bytes\n", len);
    return (0);
}
```

Compile and link your program with the library:

```bash
make
gcc main.c -L. -lftprintf -I includes -o demo
./demo
```

## API

```c
int ft_printf(const char *format, ...);
```

Writes the formatted output to standard output (file descriptor `1`) and returns the total
number of characters written.

## Project structure

```
printf/
├── Makefile                  # builds libftprintf.a (+ analyze target)
├── includes/
│   ├── ft_printf.h           # public prototype, t_format / t_ptr structs
│   └── libft.h               # libft dependency declarations
├── ft_printf.c               # entry point: main loop + conversion dispatch
├── parser.c                  # parse_format(): flags, width, precision, specifier
├── handlers_char_str.c       # handle_char / handle_str  (%c, %s)
├── handlers_num.c            # handle_int / handle_uint   (%d, %i, %u)
├── handlers_hex_ptr.c        # handle_hex / handle_ptr     (%x, %X, %p)
├── utils.c                   # utoa_base(), put_chars()
├── sum.c                     # ft_sum / ft_sum2: hex & pointer padding
├── source/
│   ├── ft_putcharf.c         # write a single character
│   └── ft_putstrf.c          # write a string (NULL-safe)
└── scripts/
    └── check_norm.py         # 42 Norm checker
```

## Author & acknowledgements

Developed by **m4ntr4** (`ahammoud`) as part of the **42 School** common core curriculum.
The project specification (`en.subject.pdf`) and coding standard (`norm.pdf`) are included
in the repository for reference.
