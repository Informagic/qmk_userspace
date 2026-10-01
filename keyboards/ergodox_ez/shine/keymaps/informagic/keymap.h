#ifndef KEYMAP_H
#define KEYMAP_H

#include QMK_KEYBOARD_H

#include "matrix.h"
#include "version.h"

#include "layers.h"
#include "neo2chars.h"

#include "disco.h"

bool process_record_user_shifted(uint16_t keycode, keyrecord_t *record);

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE,
  MAGIC_SPACE_LEFT,
  MAGIC_SPACE_RIGHT,

  DISCO_TOGGLE,

  HSV_172_255_255,
  HSV_86_255_128,

  NEO2_1,
  NEO2_2,
  NEO2_3,
  NEO2_4,
  NEO2_5,
  NEO2_6,
  NEO2_7,
  NEO2_8,
  NEO2_9,
  NEO2_0,
  NEO2_MINUS,
  NEO2_COMMA,
  NEO2_DOT
};

// bitmasks for modifier keys
#define MODS_NONE   0
#define MODS_SHIFT  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_CTRL   (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT    (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI    (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

#endif
