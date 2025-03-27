#include "rmt_led_strip_light.h"
#include "esphome/components/light/addressable_light.hpp"
#include "driver/rmt_tx.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

// Príklad setup funkcie
void RMTLedStripLight::setup() {
  ESP_LOGI("rmt_led_strip", "Initializing LED strip on pin %d", pin_->get_pin());

  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);
}

}  // namespace rmt_led_strip
}  // namespace esphome
