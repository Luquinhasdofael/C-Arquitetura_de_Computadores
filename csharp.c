#include <stdio.h>
#include <string.h>
int main(void) {
    int i; int k;

    char string[100];


    scanf("%d", &k);

    getchar();


    fgets(string, sizeof(string), stdin);


    for (i = 0; i < strlen(string); i++) {
        if (string[i] % 2 == 0) {
            string[i] = string[i] - k;
        } else {
            string[i] = string[i] + k;
        }
    }
    printf("%s\n", string);
    return 0;
}