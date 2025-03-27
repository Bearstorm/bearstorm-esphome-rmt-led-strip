#include "rmt_led_strip_light.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Initializing RMT LED Strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);
}

void RMTLedStripLight::write_state(light::LightState *state) {
  auto call = state->current_values;
  float r = call.get_red();
  float g = call.get_green();
  float b = call.get_blue();
  float brightness = call.get_brightness();

  ESP_LOGD(TAG, "Setting LED color R:%.2f G:%.2f B:%.2f Brightness: %.2f", r, g, b, brightness);

  // Tu môžeš neskôr pridať kód pre posielanie dát do pásika cez RMT

  // Zatiaľ žiadna RMT logika – len debug info
}

}  // namespace rmt_led_strip
}  // namespace esphome
