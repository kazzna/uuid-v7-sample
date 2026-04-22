#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Hello from C!\n");
    
    if (argc > 1) {
        printf("Arguments passed:\n");
        for (int i = 1; i < argc; i++) {
            printf("  [%d] %s\n", i, argv[i]);
        }
    }
    
    return EXIT_SUCCESS;
}
