#pragma once
#ifdef __OBJC__
#import <Foundation/Foundation.h>
#else // !__OBJC__
#include <stdarg.h>

#endif // __OBJC__
extern float get_mouse_x();
extern float get_mouse_y();
#ifdef __OBJC__
@interface Interop : NSObject {
}
@end
#endif // __OBJC__
