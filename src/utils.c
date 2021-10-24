#include "utils.h"
#include <Carbon/Carbon.h>
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
    output = kVK_ANSI_E;
  } else if (strcmp(keycode, "e") == 0){
    output = kVK_ANSI_E;
  } else if (strcmp(keycode, "f") == 0){
    output = kVK_ANSI_F;
  } else if (strcmp(keycode, "w") == 0){
    output = kVK_ANSI_W;
  } else {
    printf("keycode is not supported\n");
    exit(1);
  }
  return output;
}
