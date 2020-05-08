#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <chrono>

class TIME{

public:

   static std::chrono::duration<double, std::milli> delta;
   static std::chrono::duration<double, std::milli> last_tick;
   static std::chrono::duration<double, std::milli> time;

};



#endif // TIMER_H_INCLUDED
