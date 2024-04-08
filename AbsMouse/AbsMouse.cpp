#include "AbsMouse.h"
#include <unistd.h>
#include <cmath>
#include <iostream>

void AbsMouse::begin() {
  this->mouse.begin();
  while (!this->mouse.isConnected()) usleep(300000);
  this->mouse.click();
  usleep(100000);
  this->reset();
  usleep(200000);
}

void AbsMouse::reset() {
  for (int i = 0; i < 8; i++) {
    this->mouse.move(-127, 0);
    usleep(REST_TIME);
  }
  for (int i = 0; i < 8; i++) {
    this->mouse.move(0, 127);
    usleep(REST_TIME);
  }
  this->now_x = 0;
  this->now_y = 0;
}

void AbsMouse::move(signed char x, signed char y) {
  this->mouse.move(x, y);
}

void AbsMouse::moveTo(int x, int y) {
  int small_step_x = floor((x - this->now_x) / SMALL_STEP);
  int small_step_y = floor((y - this->now_y) / SMALL_STEP);
  this->now_x += small_step_x * SMALL_STEP;
  this->now_y += small_step_y * SMALL_STEP;
  // As the mouse would accelerate,
  // keep moving a short distance for couple times to ensure every the speed would be nearly the same
  // y-axis first instead of x-axis to prevent the bottom home line disturb
  for (int i = 0; i < abs(small_step_y); i++) {
    this->move(0, -SMALL_STEP * (small_step_y > 0 ? 1 : -1));
    usleep(REST_TIME);
  }
  for (int i = 0; i < abs(small_step_x); i++) {
    this->move(SMALL_STEP * (small_step_x > 0 ? 1 : -1), 0);
    usleep(REST_TIME);
  }
}

void AbsMouse::press() {
  this->mouse.press();
}

void AbsMouse::pressAt(int x, int y) {
  this->moveTo(x, y);
  this->mouse.press();
}

void AbsMouse::release() {
  this->mouse.release();
}

void AbsMouse::releaseAt(int x, int y) {
  this->moveTo(x, y);
  this->mouse.release();
}

void AbsMouse::click() {
  this->mouse.click();
}

void AbsMouse::clickAt(int x, int y) {
  this->moveTo(x, y);
  this->mouse.click();
}