#include "rmt_led_strip_light.h"
#include "driver/rmt_tx.h"
#include "esp_log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Setting up RMT LED Strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  // Inicializuj efektové vlastnosti
  this->effects_.reserve(4);

  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);
}

light::AddressableLightTraits RMTLedStripLight::get_traits() {
  return this->addressable_traits_;
}

void RMTLedStripLight::write_state(light::LightState *state) {
  float red, green, blue;
  state->current_values_as_rgb(&red, &green, &blue);
  float brightness = state->current_values.get_brightness();

  uint8_t r = red * 255 * brightness;
  uint8_t g = green * 255 * brightness;
  uint8_t b = blue * 255 * brightness;

  ESP_LOGD(TAG, "Writing RGB: R=%d G=%d B=%d", r, g, b);

  // Vypíš na všetky LEDky túto farbu (statický mód)
  for (uint16_t i = 0; i < this->size(); i++) {
    this->at(i) = Color(r, g, b);
  }
  this->schedule_show();
}

}  // namespace rmt_led_strip
}  // namespace esphome
