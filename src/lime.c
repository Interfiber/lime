#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "daemon.h"
#include "utils.h"

int main(int argc, char **argv){
    // check for permissons
    if (has_ax_access()){
        printf("Permissons: Granted!\n");
    } else {
        printf("Permissons: Not granted!\n");
    }
    if (argc == 1){
        print_help();
        exit(1);
    } else {
        if (argc >= 2){
            if (strncmp(argv[1], "new", 51) == 0){
                if (argc == 3){
                    add_macro(argv[2]);
                } else {
                    printf("Expected argument file got nothing\n");
                    exit(1);
                }
            } else {
                printf("Unknown Command %s\n", argv[1]);
            }
        } else {
            print_help();
            exit(1);
        }
    }
}
