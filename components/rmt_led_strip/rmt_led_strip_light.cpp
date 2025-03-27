#include "rmt_led_strip_light.h"
#include "driver/rmt_tx.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Initializing LED strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  // Inicializuj adresovateľný LED pás
  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);

  // TODO: Pridať RMT ovládanie (zatiaľ len základ)
}

}  // namespace rmt_led_strip
}  // namespace esphome
