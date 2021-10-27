#include "daemon.h"
#include "minIni.h"
#include "utils.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <objc/objc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "objc.h"

void run_macro(char* file){
    // create_overlay();
    char name[500];
    char rate_str[500];
    char press_keys[900];
    char failsafe_str[100];
    char mouseclicks_str[300];
    int i, j, cnt;
    char *rate_ptr;
    char *failsafe_ptr;
    char *mouseclick_ptr;
    printf("Loading macro from file: %s\n", file);
    ini_gets("macro", "name", "undefined", name, array_count(name), file);
    ini_gets("macro", "rate", "0", rate_str, array_count(rate_str), file);
    ini_gets("macro", "failsafe", "0", failsafe_str, array_count(failsafe_str), file);
    ini_gets("macro", "press_keys", "undefined", press_keys, array_count(press_keys), file);
    ini_gets("macro", "click_mouse", "0", mouseclicks_str, array_count(mouseclicks_str), file);
    printf("Current rate: %s\n", rate_str);
    printf("Starting macro...\n");
    long rate = strtol(rate_str, &rate_ptr, 10);
    // Split press_keys

    char splitStrings[40][40];
    // Convert failsafe
    long failsafe = strtol(failsafe_str, &failsafe_ptr, 10);
    // Convert mouseclicks
    long mouseclicks = strtol(mouseclicks_str, &mouseclick_ptr, 10);
    j = 0;
    cnt = 0;
    for (i = 0; i <= (strlen(press_keys)); i++) {
        // if space or NULL found, assign NULL into splitStrings[cnt]
        if (press_keys[i] == '-' || press_keys[i] == '\0') {
            splitStrings[cnt][j] = '\0';
            cnt++; //for next word
            j = 0; //for next word, init index to 0
        } else {
            splitStrings[cnt][j] = press_keys[i];
            j++;
        }
    }
    int looptime = 0;
    printf("Fail safe is: %ld\n", failsafe);
    printf("Mouse X: %f\n", get_mouse_x());
    printf("Mouse Y: %f\n", get_mouse_y());
    printf("=== Macro Output ===\n");
    while (true){
        // press keys
        if (failsafe != 0){
            if (looptime >= failsafe){
                printf("\nReached failsafe: exiting.\n");
                exit(0);
            }
        }
        if (strcmp(press_keys, "undefined") != 0){
            for (i = 0; i < cnt; i++){
             click_key(keycode_for_char(splitStrings[i]));
        }   
        }
        // click using the mouse
        if (mouseclicks != 0){
            int mouseclick_tick = 0;
            for(mouseclick_tick = 0; mouseclick_tick <= mouseclicks; mouseclick_tick += 1){
                press_mouse(get_mouse_x(), get_mouse_y());
            }
        }
        if (failsafe != 0){
            looptime += 1;
        }
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
void press_mouse(float x, float y){
    // Create MouseDown event
        CGEventRef click1_down = CGEventCreateMouseEvent(
            NULL, kCGEventLeftMouseDown,
            CGPointMake(x, y),
            kCGMouseButtonLeft
            );
        // Create MouseUp event
        CGEventRef click1_up = CGEventCreateMouseEvent(
                NULL, kCGEventLeftMouseUp,
                CGPointMake(x, y),
                kCGMouseButtonLeft
        );
        CGEventPost(kCGHIDEventTap, click1_down);
        usleep(2 * 1000);
        // Mouse up
        CGEventPost(kCGHIDEventTap, click1_up);
        usleep(2 * 1000);
        // Release the events
        CFRelease(click1_up);
        CFRelease(click1_down);
}
