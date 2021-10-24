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

int keycode_for_char(const char* keycode)
{
  int output = 4; 
  if (strcmp(keycode, "f") == 0){
    output = kVK_ANSI_F;
  } else {
    printf("invalid key\n");
  }
  return output;
}
