#include "utils.h"
#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int has_ax_access(){
  const void *keys[] = { kAXTrustedCheckOptionPrompt };
  const void *values[] = { kCFBooleanTrue };
  CFDictionaryRef options = CFDictionaryCreate(NULL, keys, values, array_count(keys), &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
  bool result = AXIsProcessTrustedWithOptions(options);
  CFRelease(options);
  return result; 
}

int keycode_for_char(const char* keycode){
  int output = 4; 

  if (strcmp(keycode, "a") == 0){
    output = kVK_ANSI_A;
  } else if (strcmp(keycode, "b") == 0){
    output = kVK_ANSI_B;
  } else if (strcmp(keycode, "c") == 0){
    output = kVK_ANSI_C;
  } else if (strcmp(keycode, "d") == 0){
    output = kVK_ANSI_D;
  } else if (strcmp(keycode, "e") == 0){
    output = kVK_ANSI_E;
  } else if (strcmp(keycode, "f") == 0){
    output = kVK_ANSI_F;
  } else if (strcmp(keycode, "g") == 0){
    output = kVK_ANSI_G;
  } else if (strcmp(keycode, "h") == 0){
    output = kVK_ANSI_H;
  } else if (strcmp(keycode, "i") == 0){
    output = kVK_ANSI_I;
  } else if (strcmp(keycode, "j") == 0){
    output = kVK_ANSI_J;
  } else if (strcmp(keycode, "k") == 0){
    output = kVK_ANSI_K;
  } else if (strcmp(keycode, "l") == 0){
    output = kVK_ANSI_L;
  } else if (strcmp(keycode, "m") == 0){
    output = kVK_ANSI_M;
  } else if (strcmp(keycode, "n") == 0){
    output = kVK_ANSI_N;
  } else if (strcmp(keycode, "o") == 0){
    output = kVK_ANSI_O;
  } else if (strcmp(keycode, "p") == 0){
    output = kVK_ANSI_P;
  } else if (strcmp(keycode, "q") == 0){
    output = kVK_ANSI_Q;
  } else if (strcmp(keycode, "r") == 0){
    output = kVK_ANSI_R;
  } else if (strcmp(keycode, "s") == 0){
    output = kVK_ANSI_S;
  } else if (strcmp(keycode, "t") == 0){
    output = kVK_ANSI_T;
  } else if (strcmp(keycode, "u") == 0){
    output = kVK_ANSI_U;
  } else if (strcmp(keycode, "v") == 0){
    output = kVK_ANSI_V;
  } else if (strcmp(keycode, "w") == 0){
    output = kVK_ANSI_W;
  } else if (strcmp(keycode, "x") == 0){
    output = kVK_ANSI_X;
  } else if (strcmp(keycode, "y") == 0){
    output = kVK_ANSI_Y;
  } else if (strcmp(keycode, "z") == 0){
    output = kVK_ANSI_Z;
  } else if (strcmp(keycode, " ") == 0){
    output = kVK_Space;
  } else {
    printf("keycode is not supported\n");
    printf("Keycode is >>%s<<", keycode);
    exit(1);
  }
  return output;
}
bool pressed_esc = false;
bool pressed_quit = false;
static CGEventRef hotkey_event(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *reference){
  // The incoming keycode.
  uint32_t keycode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  unsigned short esc_code = kVK_Escape;
  unsigned short quit_code = kVK_ANSI_Q;
  if (keycode == esc_code){
   pressed_esc = true; 
  } else if (keycode == quit_code){
    pressed_quit = true; 
  } else {
    pressed_esc = false;
    pressed_quit = false;
  }
  if (pressed_esc && pressed_quit){
    printf("Shutting down lime...");
    exit(0);
  }
  return event;
}
void setup_shutdown_hotkey(){
  printf("Creating event tap\n");
  CFMachPortRef      event_tap;
  CGEventMask        event_mask;
  CFRunLoopSourceRef run_loop_src;
  event_mask = ((1 << kCGEventKeyDown) | (1 << kCGEventKeyUp));
  event_tap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, event_mask, hotkey_event, NULL);
  if(!event_tap){
    printf("Failed to create event tap!\n");
    exit(1);
  }
  // update the run loop
  run_loop_src = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, event_tap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), run_loop_src, kCFRunLoopCommonModes);
  // Enable the event tap
  CGEventTapEnable(event_tap, true);
  printf("Event tap enabled, and created.\n");
  CFRunLoopRun();
}
