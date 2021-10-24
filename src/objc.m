#import <Cocoa/Cocoa.h>
#import "objc.h"

int get_mouse_x(){
    NSPoint mouseLoc;
    mouseLoc = [NSEvent mouseLocation];
    return mouseLoc.x;
}
int get_mouse_y(){
    NSPoint mouseLoc;
    mouseLoc = [NSEvent mouseLocation];
    return mouseLoc.y;
}