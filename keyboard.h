#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#if defined __linux__ || defined __APPLE__
    #include "Platform/Linux/keyboard.h"
#endif // __linux__

#ifdef _WIN32
    #include "Platform/Windows/keyboard.h"
#endif // _WIN32

#endif // KEYBOARD_H_INCLUDED
