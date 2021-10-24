#include "daemon.h"
#include "minIni.h"
#include "utils.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void run_macro(char* file){
    char name[500];
    char rate_str[500];
    char press_keys[900];
    int i, j, cnt;
    long rate = 0;
    char *ptr;
    printf("Loading macro from file: %s\n", file);
    ini_gets("macro", "name", "undefined", name, array_count(name), file);
    ini_gets("macro", "rate", "0", rate_str, array_count(rate_str), file);
    ini_gets("macro", "press_keys", "n", press_keys, array_count(press_keys), file);
    printf("Current rate: %s\n", rate_str);
    printf("Starting macro...\n");
    rate = strtol(rate_str, &ptr, 10);
    // Split press_keys
    char splitStrings[40][40];

    j = 0;
    cnt = 0;
    for (i = 0; i <= (strlen(press_keys)); i++) {
        // if space or NULL found, assign NULL into splitStrings[cnt]
        if (press_keys[i] == '-' || press_keys[i] == '\0') {
            splitStrings[cnt][j] = '\0';
            cnt++; //for next word
            j = 0; //for next word, init index to 0
        }
        else {
            splitStrings[cnt][j] = press_keys[i];
            j++;
        }
    }
    while (true){
        char* press_keys_ptr = press_keys;
        for (i = 0; i < cnt; i++)
            click_key(keycode_for_char(splitStrings[i]));
        usleep(rate * 1000);
    }
}

// Key press utils
void press_key(int key){
    // Create a HID hardware event source
    CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    // Create a new keyboard press event
    CGEventRef evt = CGEventCreateKeyboardEvent(src, (CGKeyCode) key, true);

    // Post the keyboard event, then release the key
    CGEventPost (kCGHIDEventTap, evt);
    CFRelease (evt); CFRelease (src);
    usleep(60);
}
void release_key(int key){
      // Create an HID hardware event source
    CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    // Create a new keyboard key release event
    CGEventRef evt = CGEventCreateKeyboardEvent(src, (CGKeyCode) key, false);

    // Post keyboard event and release
    CGEventPost (kCGHIDEventTap, evt);
    CFRelease (evt); CFRelease (src);

    usleep(60);
}
void click_key(int key){
    press_key(key);
    release_key(key);
}
