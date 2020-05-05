#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "../macros.h"

enum class Event_type {
    none = 0,
    key_press, key_release, mouse_button_press, mouse_button_release, mouse_scroll, mouse_move
};

class Event{
    public:

        virtual Event_type get_event_type() const PURE_VIRTUAL;
        virtual const char* get_event_name() const PURE_VIRTUAL;
};

#endif // EVENT_H_INCLUDED
