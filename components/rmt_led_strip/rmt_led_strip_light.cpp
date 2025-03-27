#include "rmt_led_strip_light.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Setting up RMT LED Strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);
}

void RMTLedStripLight::write_state(light::LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);
  ESP_LOGD(TAG, "Setting color R:%.2f G:%.2f B:%.2f", r, g, b);

  // TODO: implement RMT writing here
  // This is where you'd send the color to your LEDs using RMT
}

}  // namespace rmt_led_strip
}  // namespace esphome
