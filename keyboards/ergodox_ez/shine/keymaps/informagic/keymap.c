#include "keymap.h"

/* TODO: Use US International keymap in order to prevent some of the more common letters to be sent as Unicode */

const uint32_t PROGMEM unicode_map[] = {
  [NEO2_L1_AND_2_AE_LOWERCASE] = 0x00e4,
  [NEO2_L1_AND_2_AE_UPPERCASE] = 0x00c4,
  [NEO2_L1_AND_2_OE_LOWERCASE] = 0x00f6,
  [NEO2_L1_AND_2_OE_UPPERCASE] = 0x00d6,
  [NEO2_L1_AND_2_UE_LOWERCASE] = 0x00fc,
  [NEO2_L1_AND_2_UE_UPPERCASE] = 0x00dc,
  [NEO2_L1_AND_2_SS_LOWERCASE] = 0x00df,
  [NEO2_L1_AND_2_SS_UPPERCASE] = 0x1e9e,
  [NEO2_L1_AND_2_BULLET] = 0x2022,
  [NEO2_L1_AND_2_DEGREE] = 0x00b0,
  [NEO2_L1_AND_2_SECTION] = 0x00a7,
  [NEO2_L1_AND_2_ANGLEQUOTE_RIGHT] = 0x00bb,
  [NEO2_L1_AND_2_ANGLEQUOTE_LEFT] = 0x00ab,
  [NEO2_L1_AND_2_EURO] = 0x20ac,
  [NEO2_L1_AND_2_DOUBLEQUOTE_LOW] = 0x201e,
  [NEO2_L1_AND_2_DOUBLEQUOTE_LEFT] = 0x201c,
  [NEO2_L1_AND_2_DOUBLEQUOTE_RIGHT] = 0x201d,
  [NEO2_L1_AND_2_DASH_EN] = 0x2013,
  [NEO2_L1_AND_2_DASH_EM] = 0x2014,
  [NEO2_L1_AND_2_DEAD_ACUTE] = 0x0301,
  [NEO2_L1_AND_2_DEAD_GRAVE] = 0x0300,
  [NEO2_L1_AND_2_DEAD_CIRCUMFLEX] = 0x0302,
  [NEO2_L1_AND_2_DEAD_CEDILLA] = 0x0327,
  [NEO2_L1_AND_2_DEAD_TILDE] = 0x0303,
  [NEO2_L1_AND_2_DEAD_CARON] = 0x030c
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  | ́ /c  |           | ̀ /̃   |   6  |   7  |   8  |   9  |   0  |   -/—  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | ̂ /c    |   X  |   V  |   L  |   C  |   W  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
  [NEO2_LAYER_1_AND_2] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,              NEO2_1,         NEO2_2,         NEO2_3,         NEO2_4,         NEO2_5,         NEO2_ACUTE_CEDILLA,                             NEO2_GRAVE_TILDE,   NEO2_6,         NEO2_7,         NEO2_8,         NEO2_9,         NEO2_0,         NEO2_MINUS,
    NEO2_CIRCUMFLEX_CARON,  KC_X,           KC_V,           KC_L,           KC_C,           KC_W,           KC_TRANSPARENT,                                 KC_TRANSPARENT,     KC_K,           KC_H,           KC_G,           KC_F,           KC_Q,           NEO2_SS,
    KC_TAB,                 KC_U,           KC_I,           KC_A,           KC_E,           KC_O,                                                                               KC_S,           KC_N,           KC_R,           KC_T,           KC_D,           KC_Y,
    MO(1),                  NEO2_UE,        NEO2_OE,        NEO2_AE,        KC_P,           KC_Z,           KC_HYPR,                                        KC_MEH,             KC_B,           KC_M,           NEO2_COMMA,     NEO2_DOT,       KC_J,           MO(1),
    KC_LEFT_GUI,            KC_TRANSPARENT, KC_TRANSPARENT, KC_UP,          KC_DOWN,                                                                                                            KC_LEFT,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT,             DISCO_TOGGLE,   LAG(KC_EQUAL), LAG(KC_MINUS),
                                                                                                                                KC_HOME,        KC_PAGE_UP,
                                                                            MT(MOD_LSFT, KC_SPACE), MT(MOD_LCTL, KC_DELETE),    KC_END,         KC_PGDN,       MT(MOD_RALT, KC_BSPC), MT(MOD_RSFT, KC_SPACE)
  ),
  [NEO2_LAYER_3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_TRANSPARENT,
    KC_TRANSPARENT, NEO2_L3_ELLIPSIS, KC_UNDS,        KC_LBRC,        KC_RBRC,        KC_CIRC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_EXLM,        KC_LABK,        KC_RABK,        KC_EQUAL,       KC_AMPR,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_BSLS,        KC_SLASH,       KC_LCBR,        KC_RCBR,        KC_ASTR,                                                                        KC_QUES,        KC_LPRN,        KC_RPRN,        KC_MINUS,       KC_COLN,        KC_AT,
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_PIPE,        KC_TILD,        KC_GRAVE,       KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PLUS,        KC_PERC,        KC_DQUO,        KC_QUOTE,       KC_SCLN,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_MS_UP, KC_MS_DOWN,                                                                                                 KC_MS_LEFT, KC_MS_RIGHT, KC_MS_BTN1, KC_MS_BTN2, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, HSV_172_255_255,LAG(KC_8), KC_TRANSPARENT,
                                                                                                                    HSV_86_255_128, KC_TRANSPARENT,
                                                                                    S(KC_ENT),        RGB_VAD,        RGB_VAI, KC_TRANSPARENT, RGB_HUI, S(KC_ENT)
  ),
  [NEO2_LAYER_4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, NEO2_L4_FEMININE_ORDINAL, NEO2_L4_MASCULINE_ORDINAL, KC_NO, NEO2_L4_MIDDLE_DOT, NEO2_L4_BRITISH_POUND, NEO2_L4_CURRENCY_SIGN,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, NEO2_L4_INV_EXCLAMATION, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 NEO2_L4_INV_QUESTIONMARK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,                                                                                                     KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
  ),
};

const uint16_t PROGMEM combo0[] = { MT(MOD_LSFT, KC_SPACE), MT(MOD_RSFT, KC_SPACE), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ENTER),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_172_255_255:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_sethsv(172,255,255);
        #endif
      }
      return false;
    case HSV_86_255_128:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_sethsv(86,255,128);
        #endif
      }
      return false;
  }

  return process_record_user_shifted(keycode, record);
}

// Special remapping for keys with different keycodes/macros when used with shift modifiers.
bool process_record_user_shifted(uint16_t keycode, keyrecord_t *record) {
  uint8_t active_modifiers = get_mods();
  uint8_t shifted = active_modifiers & MODS_SHIFT;

  // Early return on key release
  if(!record->event.pressed) {
    return true;
  }

  if(shifted) {
    clear_mods();

    switch(keycode) {
      case NEO2_1:
        // degree symbol
        send_unicode_string("°");
        break;
      case NEO2_2:
        // section symbol
        send_unicode_string("§");
        break;
      case NEO2_3:
        SEND_STRING("Life, the Universe, and Everything.\n");
        break;
      case NEO2_4:
        // right angled quote
        send_unicode_string("»");
        break;
      case NEO2_5:
        // left angled quote
        send_unicode_string("«");
        break;
      case NEO2_6:
        // dollar sign
        SEND_STRING("$");
        break;
      case NEO2_7:
        // euro sign
        send_unicode_string("€");
        break;
      case NEO2_8:
        // low9 double quote
        send_unicode_string("„");
        break;
      case NEO2_9:
        // left double quote
        send_unicode_string("“");
        break;
      case NEO2_0:
        // right double quote
        send_unicode_string("”");
        break;
      case NEO2_MINUS:
        // em dash
        send_unicode_string("—");
        break;
      case NEO2_COMMA:
        // en dash
        send_unicode_string("–");
        break;
      case NEO2_DOT:
        // bullet
        send_unicode_string("•");
        break;
      default:
        set_mods(active_modifiers);
        return true;
    }

    set_mods(active_modifiers);
    return false;
  } else {
    switch(keycode) {
      case NEO2_1:
        SEND_STRING(SS_TAP(X_1));
        break;
      case NEO2_2:
        SEND_STRING(SS_TAP(X_2));
        break;
      case NEO2_3:
        SEND_STRING(SS_TAP(X_3));
        break;
      case NEO2_4:
        SEND_STRING(SS_TAP(X_4));
        break;
      case NEO2_5:
        SEND_STRING(SS_TAP(X_5));
        break;
      case NEO2_6:
        SEND_STRING(SS_TAP(X_6));
        break;
      case NEO2_7:
        SEND_STRING(SS_TAP(X_7));
        break;
      case NEO2_8:
        SEND_STRING(SS_TAP(X_8));
        break;
      case NEO2_9:
        SEND_STRING(SS_TAP(X_9));
        break;
      case NEO2_0:
        SEND_STRING(SS_TAP(X_0));
        break;
      case NEO2_MINUS:
        SEND_STRING(SS_TAP(X_MINS));
        break;
      case NEO2_COMMA:
        SEND_STRING(SS_TAP(X_COMMA));
        break;
      case NEO2_DOT:
        SEND_STRING(SS_TAP(X_DOT));
        break;
      default:
        return true;
    }

    return false;
  }
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;
};

void keyboard_post_init_user(void) {
  layer_state_set_user(layer_state);
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  check_disco_mode(keycode, record);
}

void matrix_init_user(void) {
  animation_timer = timer_read();
}

void matrix_scan_user(void) {
    decrease_brightness();
}
