#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/addressable_light.hpp"
#include "esphome/core/gpio.h"

namespace esphome {
namespace rmt_led_strip {

class RMTLedStripLight : public light::AddressableLight {
 public:
  void setup() override;

  void set_pin(GPIOPin *pin) { pin_ = pin; }
  void set_num_leds(uint16_t num_leds) { num_leds_ = num_leds; }
  void set_chipset(const std::string &chipset) { chipset_ = chipset; }
  void set_rgb_order(const std::string &order) { rgb_order_ = order; }
  void set_rmt_channel(uint8_t channel) { rmt_channel_ = channel; }

 protected:
  GPIOPin *pin_;
  uint16_t num_leds_;
  std::string chipset_;
  std::string rgb_order_;
  uint8_t rmt_channel_;
};

}  // namespace rmt_led_strip
}  // namespace esphome
