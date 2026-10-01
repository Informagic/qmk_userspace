#include "disco.h"
#include <stdlib.h>

bool disco_mode_enabled = false;
uint16_t animation_timer = 0;
struct disco_state disco_left  = {0};
struct disco_state disco_right = {0};

void check_disco_mode(uint16_t keycode, keyrecord_t *record) {
  if (disco_mode_enabled) {
    if (record->event.pressed) {
      if (record->event.key.row < 7) {
        disco_left.led_hue = rand() % 255;
        disco_left.animation_progress = 255;
        disco_left.animation_center_index = 30 - (record->event.key.row * 2 + 2);
        disco_left.num_keys_held_down++;

        for (uint8_t led_index = (uint8_t)RGBLIGHT_LED_COUNT / 2; led_index < (uint8_t)RGBLIGHT_LED_COUNT; led_index++) {
          rgblight_sethsv_at(
            disco_left.led_hue,
            255,
            DISCO_LED_VALUE(disco_left.animation_progress, led_index, disco_left.animation_center_index),
            led_index
          );
        }
      } else {
        disco_right.led_hue = rand() % 255;
        disco_right.animation_progress = 255;
        disco_right.animation_center_index = (13 - record->event.key.row) * 2 + 1;
        disco_right.num_keys_held_down++;

        for (uint8_t led_index = 0; led_index < (uint8_t)RGBLIGHT_LED_COUNT / 2; led_index++) {
          rgblight_sethsv_at(
            disco_right.led_hue,
            255,
            DISCO_LED_VALUE(disco_right.animation_progress, led_index, disco_right.animation_center_index),
            led_index
          );
        }
      }

    } else {
      if (record->event.key.row < 7) {
        if (disco_left.num_keys_held_down > 0) {
          disco_left.num_keys_held_down--;
        }
      } else {
        if (disco_right.num_keys_held_down > 0) {
          disco_right.num_keys_held_down--;
        }
      }
    }
  }
}

void decrease_brightness(void) {
  if (
    disco_mode_enabled &&
    (disco_left.animation_progress > 0 || disco_right.animation_progress > 0) &&
    timer_elapsed(animation_timer) > 20
  ) {
    animation_timer = timer_read();

    if (disco_left.num_keys_held_down == 0 && disco_left.animation_progress > 0) {
      disco_left.animation_progress -= 5;

      for (uint8_t led_index = (uint8_t)RGBLIGHT_LED_COUNT / 2; led_index < (uint8_t)RGBLIGHT_LED_COUNT; led_index++) {
        rgblight_sethsv_at(
          disco_left.led_hue,
          255,
          DISCO_LED_VALUE(disco_left.animation_progress, led_index, disco_left.animation_center_index),
          led_index
        );
      }
    }

    if (disco_right.num_keys_held_down == 0 && disco_right.animation_progress > 0) {
      disco_right.animation_progress -= 5;

      for (uint8_t led_index = 0; led_index < (uint8_t)RGBLIGHT_LED_COUNT / 2; led_index++) {
        rgblight_sethsv_at(
          disco_right.led_hue,
          255,
          DISCO_LED_VALUE(disco_right.animation_progress, led_index, disco_right.animation_center_index),
          led_index
        );
      }
    }
  }
}
