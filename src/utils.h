#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

// usefull function
#define array_count(a) (sizeof((a)) / sizeof(*(a)))

int has_ax_access();
int keycode_for_char(const char* keycode);
char* get_current_window();
