
#include "Display.h"
#import "AppKit/AppKit.h"

bool Display::IsRetinaDisplay()
{
    return 2 == int([[NSScreen mainScreen] backingScaleFactor]);
}
