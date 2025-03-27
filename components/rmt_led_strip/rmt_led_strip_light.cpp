#include "rmt_led_strip_light.h"
#include "driver/rmt_tx.h"
#include "esp_log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Setting up RMT LED Strip on pin %d, %d LEDs", pin_->get_pin(), num_leds_);
  // Tu by si mohol použiť originálny RMT kód, tu len placeholder:
  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);
}

}  // namespace rmt_led_strip
}  // namespace esphome
