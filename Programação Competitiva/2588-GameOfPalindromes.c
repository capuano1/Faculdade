#include <stdio.h>
#include <string.h>

int main() {

    char str[1000];
    FILE *txt;
    txt = fopen("results.txt", "w");

    while (fgets(str, sizeof(str), stdin) != NULL) {
        int length, count = 0, impar = 0, par = 0, add = 0;
        int alphabet[26] = {0};
        char letters[26];

        length = strlen(str);
        if (str[length - 1] == '\n') {
            str[length - 1] = '\0'; // Remove o '\n' do final da string
            length--;
        }

        for (int i = 0; i < length; i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                if (alphabet[str[i] - 'a'] == 0) {
                    letters[count] = str[i];
                    count++;
                }
                alphabet[str[i] - 'a']++;
            } else if (str[i] >= 'A' && str[i] <= 'Z') {
                if (alphabet[str[i] - 'A'] == 0) {
                    letters[count] = str[i];
                    count++;
                }
                alphabet[str[i] - 'A']++;
            }
        }

        for (int i = 0; i < count; i++) {
            if (alphabet[letters[i] - 'a'] % 2 == 0) {
                par++;
            } else {
                impar++;
            }
        }

        while (1) {
            if (length % 2 == 0 && impar == 0) {
                printf("%i\n", add);
                fprintf(txt, "%i\n", add);
                break;
            }
            else if (length % 2 == 1 && impar == 1) {
                printf("%i\n", add);
                fprintf(txt, "%i\n", add);
                break;
            }
            else {
                length++;
                add++;
                impar--;
                par++;
            }
        }
    }
    fclose(txt);
    return 0;
}