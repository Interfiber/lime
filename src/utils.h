#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include "cJSON.h"

// usefull function
#define array_count(a) (sizeof((a)) / sizeof(*(a)))

int has_ax_access();
int keycode_for_char(const char* keycode);
void setup_shutdown_hotkey();
cJSON* parse_macro_file(char* data);
