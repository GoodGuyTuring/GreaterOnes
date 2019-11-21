#include <stdio.h>
#include "shell.h"

int main() {
    char ** splitted_array;
    char input[] = "Hallo  Welt,   hier ist\nPeter\t!";
    splitted_array = shell_split(input);

    char ** current_pointer = splitted_array;
    while(*current_pointer!= NULL){
        char *string_tmp = *current_pointer;
        printf("%s\n", string_tmp);
        current_pointer++;
    }
    return 0;
}