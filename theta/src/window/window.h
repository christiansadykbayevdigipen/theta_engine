#pragma once

#include "core.h"

#include <string>

struct theta_rendering_context;
struct theta_input_system;

/*
@brief A window in Theta is where all the rendering goes to.
*/
typedef struct theta_window{
    void* uninterpreted_data;
    theta_api api;
    struct theta_rendering_context* context;

    BOOL (*close_requested)(struct theta_window*);
    void (*update)(struct theta_window*);
    void (*destroy)(struct theta_window*);
    void (*create_input_callbacks)(struct theta_window*, struct theta_input_system* input_system);
    void (*change_title)(struct theta_window*, const char* new_title);
}theta_window;

namespace theta
{
    class IWindow 
    {
    public:
        virtual ~IWindow() = default;

        virtual void Init(u32 width, u32 height, const std::string& title, theta_api api) = 0;
        virtual bool CloseRequested() = 0;
        virtual void Update() = 0;
        virtual void CreateInputCallbacks(struct theta_input_system* inputSystem) = 0;
        virtual void ChangeTitle(const std::string& newTitle) = 0;
        virtual theta_api GetApi()=0;

        static Ref<IWindow> CreateWindow(u32 width, u32 height, const std::string& title, theta_api api);
    };
}