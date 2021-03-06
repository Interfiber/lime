#include "cli.h"
#include <stdio.h>

void print_help(){
    printf("lime - Macro creation engine for mac\n");
    printf("Commands:\n");
    printf("   run <file>      Run the macro located inside <file>\n");
    printf("   --version       Print version info for lime\n");
}
void print_version(){
    printf("Version info: \n");
    printf("Current license: MIT\n");
    printf("Release tag: v1.1.0\n");
    printf("Version: 1.1.0\n");
}
void print_permission_msg(){
    printf("Hmmm... lime dosent seem to have accessibility permissions!\n");
    printf("Lime will require this to continue. Please grant them in System Preferences\n");
    printf("Why does lime need accessibility: https://github.com/Interfiber/lime#why-does-lime-require-accessibility\n");
}
