#include "rmt_led_strip_light.h"
#include "driver/rmt_tx.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Initializing LED strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  this->effects_.reserve(4);

  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);

  this->set_light_output_count(this->num_leds_);
}

void RMTLedStripLight::write_state(light::LightState *state) {
  auto color = state->current_values.get_color();
  float brightness = state->current_values.get_brightness();

  for (int i = 0; i < this->size(); i++) {
    this->addressable_set(i, color.red * 255, color.green * 255, color.blue * 255);
  }

  this->schedule_show();
}

}  // namespace rmt_led_strip
}  // namespace esphome
