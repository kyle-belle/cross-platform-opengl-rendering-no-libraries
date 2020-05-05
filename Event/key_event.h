#ifndef KEY_EVENT_H_INCLUDED
#define KEY_EVENT_H_INCLUDED

#include "event.h"

class Key_event : public Event{
    public:
        int key_code;
        inline int get_key_code(){return key_code;}

        Key_event(int key): key_code(key){}
};

class Key_press_event : public Key_event{
    public:
        bool repeat;

        inline bool is_repeated() const {return repeat;}

        Key_press_event(int key, bool repeated): Key_event(key), repeat(repeated){}

        virtual Event_type get_event_type() const override {
            return Event_type::key_press;
        }

        virtual const char* get_event_name()const override{
            return "KeyPress";
        }
};

class Key_release_event : public Key_event{
    public:
        Key_release_event(int key): Key_event(key){}

        virtual Event_type get_event_type() const override {
            return Event_type::key_release;
        }

        virtual const char* get_event_name()const override{
            return "KeyRelease";
        }
};

#endif // KEY_EVENT_H_INCLUDED
