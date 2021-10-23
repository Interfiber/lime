#include "utils.h"
#include <Carbon/Carbon.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int has_ax_access(){
  const void *keys[] = { kAXTrustedCheckOptionPrompt };
  const void *values[] = { kCFBooleanTrue };
  CFDictionaryRef options = CFDictionaryCreate(NULL, keys, values, array_count(keys), &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
  bool result = AXIsProcessTrustedWithOptions(options);
  CFRelease(options);
  return result; 
}
