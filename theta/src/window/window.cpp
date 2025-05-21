#include "window.h"

#if defined(THETA_PLATFORM_SHARED)
#include "platform/shared/shared_window.h"
#endif

namespace theta
{
    Ref<IWindow> IWindow::CreateWindow(u32 width, u32 height, const std::string& title, theta_api api)
    {
        THETA_PROFILE();
        #if defined(THETA_PLATFORM_SHARED)
        auto ref = CreateRef<SharedWindow>();
        ref->Init(width, height, title, api);
        return ref;
        #endif

        return nullptr;
    }
}