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
