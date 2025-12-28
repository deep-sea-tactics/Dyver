#ifndef H_WIDGET
#define H_WIDGET

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>

struct ui_pos_t 
{
    double x{0.0};
    double y{0.0};

    ui_pos_t(double ax, double ay) 
    {
        x = ax;
        y = ay;
    }
};

class widget_t 
{
public:
    auto get_pos() -> ui_pos_t& { return m_pos; }

private:
    ui_pos_t m_pos{0.0, 0.0};
};

#endif
