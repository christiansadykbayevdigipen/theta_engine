#include "window.h"

#if defined(THETA_PLATFORM_SHARED)
#include "platform/shared/shared_window.h"
#endif

theta_window* theta_window_init(u32 width, u32 height, const char* title, theta_api api) {
    THETA_PROFILE();
    #if defined(THETA_PLATFORM_SHARED)
    return theta_window_init_shared_window(width, height, title, api);
    #endif
}