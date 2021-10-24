#include "daemon.h"
#include "minIni.h"
#include "utils.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <stdlib.h>
#include <unistd.h>

void run_macro(char* file){
    char name[500];
    char rate_str[500];
    long rate = 0;
    char *ptr;
    printf("Loading macro from file: %s\n", file);
    ini_gets("macro", "name", "undefined", name, array_count(name), file);
    ini_gets("macro", "rate", "0", rate_str, array_count(rate_str), file);
    printf("Current rate: %s\n", rate_str);
    printf("Starting macro...\n");
    rate = strtol(rate_str, &ptr, 10);
    while (true){
      usleep(rate * 1000);
      click_key(keycode_for_char("f"));
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
