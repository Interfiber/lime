#import <Cocoa/Cocoa.h>
#import "objc.h"

float get_mouse_x(){
    CGEventRef event = CGEventCreate(NULL);
    NSPoint point = CGEventGetLocation(event);
    CFRelease(event);
    return (float)point.x;
}
float get_mouse_y(){
    CGEventRef event = CGEventCreate(NULL);
    NSPoint point = CGEventGetLocation(event);
    CFRelease(event);
    return (float)point.y;
}
void setup_hotkey(){
    // Listen for global hotkey here
}