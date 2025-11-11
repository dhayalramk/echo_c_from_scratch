# echo_c_from_scratch

Small C implementation of a simple `echo`-like program for learning C and CLI basics.

## Features implemented
- Print all command-line arguments separated by a space.
- `-n` : do not output the trailing newline.
- `-e` : interpret backslash escapes `\n`, `\t`, `\\`.

(It's intentionally minimal — you can extend it later to match all POSIX `echo` behaviours.)

## Prerequisites (Fedora / RHEL)
You already installed the needed packages:

```bash
sudo dnf install -y nmap-ncat
sudo dnf install -y gcc
````

`nmap-ncat` is optional (handy for basic testing over network if you want).

## Build

From the repo root:

```bash
# single compile
gcc -Wall -Wextra -g -pedantic -o myecho myecho.c

# or with optimization
gcc -O2 -Wall -Wextra -o myecho myecho.c
```

Notes:

* I replaced the duplicate `-Wall -Wall` with `-Wall -Wextra`.
* `-g` is useful while debugging; `-O2` for release.

## Usage

```bash
./myecho [OPTIONS] [ARGUMENTS...]
```

Examples:

```bash
./myecho Hello world
# -> Hello world

./myecho -n NoNewline
# -> NoNewline␣(no trailing newline)

./myecho -e "Line1\nLine2\tTabbed"
# -> Line1
#    Line2    Tabbed
```

## Testing ideas

* Basic CLI:

  ```bash
  ./myecho a b c
  ```
* With escapes:

  ```bash
  ./myecho -e "foo\nbar"
  ```
* Test network piping (using `ncat` or `nc`):

  ```bash
  printf "hi there\n" | ./myecho received:
  ```

  (Or set up `ncat` server/client if you want to send data across machines.)

## Next improvements (ideas)

* Add support for `-E` (explicitly disable escapes), POSIX compatibility
* Support quoted-argument parsing unchanged (shell handles this mostly)
* Add long-option parsing with `getopt_long`
* Add unit tests / CI to compile and run a few scenarios

## License

Add any license you want (MIT, Apache2, etc.)

````

---

# `myecho.c` — small, corrected implementation

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Simple echo implementation
 * Supports:
 *  -n : no trailing newline
 *  -e : interpret some backslash escapes: \n, \t, \\, \r
 *
 * This is intentionally minimal and educational.
 */

static void print_with_escapes(const char *s) {
    for (const char *p = s; *p; ++p) {
        if (*p == '\\') {
            ++p;
            if (!*p) break;
            switch (*p) {
                case 'n': putchar('\n'); break;
                case 't': putchar('\t'); break;
                case 'r': putchar('\r'); break;
                case '\\': putchar('\\'); break;
                default:
                    /* Unknown escape — print backslash and char literally */
                    putchar('\\');
                    putchar(*p);
            }
        } else {
            putchar(*p);
        }
    }
}

int main(int argc, const char *argv[]) {
    bool opt_n = false;
    bool opt_e = false;
    int i = 1;

    /* parse leading options (very simplistic) */
    for (; i < argc; ++i) {
        if (argv[i][0] != '-') break; /* not an option */
        if (strcmp(argv[i], "-n") == 0) {
            opt_n = true;
            continue;
        } else if (strcmp(argv[i], "-e") == 0) {
            opt_e = true;
            continue;
        }
        /* unknown option or a plain argument starting with '-' -> treat as arg */
        break;
    }

    /* print remaining args separated by space */
    for (int j = i; j < argc; ++j) {
        if (opt_e) {
            print_with_escapes(argv[j]);
        } else {
            fputs(argv[j], stdout);
        }

        if (j != argc - 1) putchar(' ');
    }

    if (!opt_n) putchar('\n');

    return 0;
}
````

### Why this version?

* The loop starts at `argv[1]` and checks `i < argc` (so `argv[0]` is the program path as usual).
* I handled a common bug: accidentally assigning inside the `if` (e.g., `if (i = argc - 1)`) — the code above is correct and safe.
* The escape interpreter is kept simple and deterministic.

## Build with Makefile

To compile and test automatically:

```bash
make        # build myecho
make test   # run basic validation
make clean  # remove compiled binaries

