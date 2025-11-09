#include "forth\libforth\libforth.h"
#include <stdio.h>


int main(void) {
    // No custom callbacks, so pass NULL for `calls`
    forth_t *f = forth_init(64 * 1024, stdin, stdout, NULL);
    if (!f) {
        fprintf(stderr, "Failed to init Forth\n");
        return 1;
    }

    // Run Forth interactively (reads from stdin)
    forth_run(f);

    forth_free(f);
    return 0;
}