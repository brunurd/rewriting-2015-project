#include <BGIGame.h>

using namespace BGIGame;

double Timer::tick = 0;

Timer::Timer() {
    QueryPerformanceFrequency(&m_frequency);
    QueryPerformanceCounter(&m_startingTime);
}

Timer::~Timer() {
    QueryPerformanceCounter(&m_endingTime);
    tick = m_endingTime.QuadPart - m_startingTime.QuadPart;
//    tick *= 1000000;
    tick /= m_frequency.QuadPart;
}