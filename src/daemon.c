#include "daemon.h"
#include "minIni.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

void add_macro(char* file){
    char* name[500];
    long rate;
    printf("Loading macro from file: %s\n", file);
    ini_gets("macro", "name", "undefined", name, array_count(name), file);
    ini_getl("macro", "rate", 4, file);
    printf("Current rate: %ld", rate);
}
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
