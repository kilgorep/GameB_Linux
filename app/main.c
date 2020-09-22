#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
 
int main(int argc, char* argv[])
{
    if (argc == 2) {
        switch (toupper(argv[1][0])) {
            case 'A': {
                printf("Hello from ASCII Land!\n");
                break;
            }
            case 'U': {
                wprintf(L"Hello from Unicode Land!\n");
                break;
            }
            default: {
                printf("Error: use \'GameB a\' or \'GameB u\'.\n");
                break;
            }
        }
    } else {
        printf("Error: use \'GameB a\' or \'GameB u\'.\n");
    }

    return 0;
}