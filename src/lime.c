#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "daemon.h"
#include "utils.h"

int main(int argc, char **argv){
    // check for permissions
    if (!has_ax_access()){
        print_permission_msg();
        exit(1);
    }
    if (argc == 1){
        print_help();
        exit(1);
    } else {
        if (argc >= 2){
            if (strncmp(argv[1], "run", 51) == 0){
                if (argc == 3){
                    run_macro(argv[2]);
                } else {
                    printf("Expected argument file got nothing\n");
                    exit(1);
                }
            } else if (strncmp(argv[1], "--version", 51) == 0){
                print_version();
            }else {
                printf("Unknown Command %s\n", argv[1]);
            }
        } else {
            print_help();
            exit(1);
        }
    }
}
