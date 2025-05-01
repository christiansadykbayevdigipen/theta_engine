#include "window.h"

#if defined(THETA_PLATFORM_SHARED)
#include "platform/shared/shared_window.h"
#endif

void theta_window_init(theta_window* window, u32 width, u32 height, const char* title) {
    #if defined(THETA_PLATFORM_SHARED)
    theta_window_init_shared_window(window, width, height, title);
    #endif
}