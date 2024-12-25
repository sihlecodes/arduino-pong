#include "HardwareSerial.h"
#include <stdint.h>
#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
  Timer()
    : m_prev_tick_state(0), m_has_ticked(1),
      m_tick_interval(0), m_elapsed(0), m_start(0), m_last(0) {
  }

  Timer(int tick_interval) : Timer() {
      m_tick_interval = tick_interval;
  }

  void start() {
    m_last = m_start = millis();  
  }

  void update() {
    // m_last = millis();

    // bool tick_state = (get_elapsed() / m_tick_interval) % 2;

    // Serial.print("Interval: ");
    // Serial.print(m_tick_interval);

    // Serial.print("State: ");
    // Serial.println(tick_state);
    unsigned long current = millis();

    if (current - m_last >= m_tick_interval) {
      m_last = current;
      m_has_ticked = true;
      // Serial.print("Has ticked: ");
      // Serial.println(m_has_ticked);
    }
  }

  bool has_ticked() {
    if (!m_has_ticked)
      return false;
      
    m_has_ticked = false;
    return true;
  }

  unsigned long get_elapsed() {
    return millis() - m_start;
  }

  unsigned long get_delta() {
    unsigned long delta = millis() - m_last;
    m_last += delta;
    return delta;
  }

private:
  bool m_prev_tick_state;
  bool m_has_ticked;
  uint16_t m_tick_interval;
  unsigned long m_elapsed, m_start, m_last;
};

#endif