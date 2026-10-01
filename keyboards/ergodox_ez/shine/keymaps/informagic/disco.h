#ifndef DISCO_H
#define DISCO_H

#include QMK_KEYBOARD_H

rgblight_config_t rgblight_config;
bool disable_layer_color;

struct disco_state {
  uint8_t led_hue;
  uint8_t animation_progress; // 255 at beginning of animation, decrements down to 0
  uint8_t animation_center_index;
  uint8_t num_keys_held_down;
};

bool disco_mode_enabled;
uint16_t animation_timer;
struct disco_state disco_left;
struct disco_state disco_right;

// Absolute value of (a - b) for unsigned values
#define DIST(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

// Easing function defined from 0 to 255 (rather than 0.0 to 1.0)
#define CUBIC_EASE(x) ((uint32_t)(x) * (x) * (x) / 255 / 255)

// Calculates the led value (brightness). leds closer to the "animation center led" are brighter.
#define DISCO_LED_VALUE(animation_progress, led_index, animation_center_index) ( \
  CUBIC_EASE(animation_progress) * \
  5 / (5 + DIST(led_index, animation_center_index)) \
)

void check_disco_mode(uint16_t keycode, keyrecord_t *record);

void decrease_brightness(void);

#endif
