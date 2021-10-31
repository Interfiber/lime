#include "daemon.h"
#include "utils.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "objc.h"

void* worker(void* args){
    setup_shutdown_hotkey();
    pthread_exit(NULL);
}

void run_macro(char* file){
    char* rate_str;
    char* press_keys = NULL;
    char* failsafe_str;
    char* mouseclicks_str;
    char* frontmost_str;
    int i, j, cnt;
    char *rate_ptr;
    char *failsafe_ptr;
    char *mouseclick_ptr;
    printf("Starting background service...\n");
    // Spawn background thread
    pthread_t worker_ptid;
    pthread_create(&worker_ptid, NULL, &worker, pthread_self());
    printf("Loading macro from file: %s...\n", file);
    // read data from json file
    FILE *macro_file;
    macro_file =fopen (file, "rb");
    if (!macro_file){
        printf("Failed to open file!\n");
        exit(1);
    }
    char * macro_data = 0;
    long length;
    fseek (macro_file, 0, SEEK_END);
    length = ftell (macro_file);
    fseek (macro_file, 0, SEEK_SET);
    macro_data = malloc (length);
    if (macro_data){
        fread (macro_data, 1, length, macro_file);
    }
    fclose (macro_file);
    // Parse the data
    cJSON* macro = parse_macro_file(macro_data);
    // Declate parsing variables
    const cJSON *keys = NULL;
    const cJSON *macro_rate = NULL;
    const cJSON *macro_failsafe = NULL;
    const cJSON *macro_clicks = NULL;
    const cJSON *macro_frontmost = NULL;
    keys = cJSON_GetObjectItemCaseSensitive(macro, "press_keys");
    macro_rate = cJSON_GetObjectItemCaseSensitive(macro, "rate");
    macro_failsafe = cJSON_GetObjectItemCaseSensitive(macro, "failsafe");
    macro_clicks = cJSON_GetObjectItemCaseSensitive(macro, "click_mouse");
    macro_frontmost = cJSON_GetObjectItemCaseSensitive(macro, "frontmost_executable_name");
    // parse press_keys
    if (cJSON_IsString(keys) && (keys->valuestring != NULL)){
        press_keys = keys->valuestring;
    } else {
        // The default value
        press_keys = "undefined";
    }
    
    // parse rate
    if (cJSON_IsString(macro_rate) && (macro_rate->valuestring != NULL)){
        rate_str = macro_rate->valuestring;
    } else {
        // The default value
        // you can set this to a string because we convert it later.
        rate_str = "900";
    }

    // parse failsafe
    if (cJSON_IsString(macro_failsafe) && (macro_failsafe->valuestring != NULL)){
        failsafe_str = macro_rate->valuestring;
    } else {
        // The default value
        // you can set this to a string because we convert it later.
        failsafe_str = "0";
    }
    // parse mouseclicks
    if (cJSON_IsString(macro_clicks) && (macro_clicks->valuestring != NULL)){
        mouseclicks_str = macro_clicks->valuestring;
    } else {
        // The default value
        // you can set this to a string because we convert it later.
        mouseclicks_str = "0";
    }
    // parse frontmost
    if (cJSON_IsString(macro_frontmost) && (macro_frontmost->valuestring != NULL)){
        frontmost_str = macro_frontmost->valuestring;
    } else {
        frontmost_str = "undefined";
    }
    // Convert types
    long rate = strtol(rate_str, &rate_ptr, 10);
    long failsafe = strtol(failsafe_str, &failsafe_ptr, 10);
    long mouseclicks = strtol(mouseclicks_str, &mouseclick_ptr, 10);
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
        } else {
            splitStrings[cnt][j] = press_keys[i];
            j++;
        }
    }
    printf("Starting macro...\n");
    int looptime = 0;
    printf("Fail safe is: %ld\n", failsafe);
    printf("Rate is: %s\n", rate_str);
    printf("Mouse clicks: %ld\n", mouseclicks);
    printf("=== Macro Output ===\n");
    while (true){
        // press keys
        if (strcmp(frontmost_str, "undefined") != 0){
            char* frontmost = get_frontmost_app();
            if (strstr(frontmost, frontmost_str) == NULL){
                continue;
            }
        }
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
