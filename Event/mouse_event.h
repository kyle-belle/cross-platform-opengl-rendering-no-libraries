#ifndef MOUSE_EVENT_H_INCLUDED
#define MOUSE_EVENT_H_INCLUDED

#include "event.h"

class Mouse_move_event : public Event {

    public:

        float x_pos, y_pos;
        Mouse_move_event(float x, float y): x_pos(x), y_pos(y){}

        inline float get_x() const {return x_pos;}
        inline float get_y() const {return y_pos;}

        virtual Event_type get_event_type() const override {
            return Event_type::mouse_move;
        }

        virtual const char* get_event_name() const override{
            return "MouseMove";
        }


};

class Mouse_scroll_event : public Event{

    public:

        float x_offset, y_offset;

        Mouse_scroll_event(float x_off, float y_off): x_offset(x_off), y_offset(y_off){}

        inline float get_offset_x() const {return x_offset;}
        inline float get_offset_y() const {return y_offset;}

        virtual Event_type get_event_type() const override {
            return Event_type::mouse_scroll;
        }

        virtual const char* get_event_name() const override{
            return "MouseScroll";
        }
};

class Mouse_button_event : public Event{

    public:

        int button_code;

        Mouse_button_event(int button): button_code(button){}

        inline int get_button_code(){return button_code;}
};

class Mouse_press_event: public Mouse_button_event{

    public:

        bool repeat;

        Mouse_press_event(int button, bool repeated): Mouse_button_event(button), repeat(repeated){}

        inline bool is_repeated() const {return repeat;}

        virtual Event_type get_event_type() const override {
            return Event_type::mouse_button_press;
        }

        virtual const char* get_event_name() const override{
            return "MouseButtonPress";
        }
};

class Mouse_release_event: public Mouse_button_event{

    public:

        Mouse_release_event(int button): Mouse_button_event(button){}

        virtual Event_type get_event_type() const override {
            return Event_type::mouse_button_release;
        }

        virtual const char* get_event_name() const override{
            return "MouseButtonRelease";
        }
};

#endif // MOUSE_EVENT_H_INCLUDED
