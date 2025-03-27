#include "rmt_led_strip_light.h"
#include "driver/rmt_tx.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rmt_led_strip {

static const char *const TAG = "rmt_led_strip";

void RMTLedStripLight::setup() {
  ESP_LOGI(TAG, "Initializing RMT LED strip on pin %d with %d LEDs", pin_->get_pin(), num_leds_);

  this->effects_.reserve(4);
  this->addressable_traits_.set_max_power_color(255, 255, 255);
  this->addressable_traits_.set_supports_rgb(true);
  this->addressable_traits_.set_supports_brightness(true);
  this->addressable_traits_.set_supports_effects(true);
  this->set_light_output_count(this->num_leds_);

  // === RMT SETUP ===
  rmt_tx_channel_config_t tx_chan_config = {
      .gpio_num = pin_->get_pin(),
      .clk_src = RMT_CLK_SRC_DEFAULT,
      .resolution_hz = 10 * 1000 * 1000,  // 10 MHz
      .mem_block_symbols = 64,
      .trans_queue_depth = 4,
      .flags = {
          .invert_out = false,
          .with_dma = false,
      },
  };

  ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &rmt_channel_));
  ESP_ERROR_CHECK(rmt_enable(rmt_channel_));
}

void RMTLedStripLight::write_state(light::LightState *state) {
  float r, g, b;
  state->current_values_as_rgb(&r, &g, &b);

  uint8_t red = static_cast<uint8_t>(r * 255);
  uint8_t green = static_cast<uint8_t>(g * 255);
  uint8_t blue = static_cast<uint8_t>(b * 255);

  std::vector<uint8_t> buffer;
  buffer.reserve(num_leds_ * 3);

  for (int i = 0; i < num_leds_; ++i) {
    if (rgb_order_ == "GRB") {
      buffer.push_back(green);
      buffer.push_back(red);
      buffer.push_back(blue);
    } else if (rgb_order_ == "RGB") {
      buffer.push_back(red);
      buffer.push_back(green);
      buffer.push_back(blue);
    } else {
      buffer.push_back(green);  // fallback
      buffer.push_back(red);
      buffer.push_back(blue);
    }
  }

  // === WS2812 timing ===
  rmt_item32_t items[24 * 3 * num_leds_];
  size_t idx = 0;

  auto make_item = [](bool bit) {
    rmt_item32_t item{};
    if (bit) {
      item.duration0 = 9; item.level0 = 1;
      item.duration1 = 3; item.level1 = 0;
    } else {
      item.duration0 = 3; item.level0 = 1;
      item.duration1 = 9; item.level1 = 0;
    }
    return item;
  };

  for (uint8_t byte : buffer) {
    for (int bit = 7; bit >= 0; --bit) {
      items[idx++] = make_item(byte & (1 << bit));
    }
  }

  rmt_transmit_config_t tx_config = {
    .loop_count = 0,
    .flags = {
      .eot_level = 0,
    },
  };

  ESP_ERROR_CHECK(rmt_transmit(rmt_channel_, RMT_MEM_OWNER_TX, items, idx * sizeof(rmt_item32_t), &tx_config));
  rmt_tx_wait_all_done(rmt_channel_, portMAX_DELAY);
}

}  // namespace rmt_led_strip
}  // namespace esphome
