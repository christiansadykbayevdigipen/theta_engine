#include "window.h"

#if defined(THETA_PLATFORM_SHARED)
#include "platform/shared/shared_window.h"
#endif

void theta_window_init(theta_window* window, u32 width, u32 height, const char* title, theta_api api) {
    THETA_PROFILE();
    #if defined(THETA_PLATFORM_SHARED)
    theta_window_init_shared_window(window, width, height, title, api);
    #endif
}

BOOL theta_window_close_requested(theta_window* window) {
    #if defined(THETA_PLATFORM_SHARED)
    return theta_window_close_requested_shared_window(window);
    #endif

    return TRUE;
}

void theta_window_update(theta_window* window) {
    #if defined(THETA_PLATFORM_SHARED)
    return theta_window_update_shared_window(window);
    #endif
}

void theta_window_destroy(theta_window* window) {
    THETA_PROFILE();
    #if defined(THETA_PLATFORM_SHARED)
    return theta_window_destroy_shared_window(window);
    #endif
}