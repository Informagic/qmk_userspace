#include "keymap.h"

#ifdef CONSOLE_ENABLE
#include "print.h"

static const char *layer_name(uint8_t layer) {
    switch (layer) {
        case NEO2_LAYER_1_AND_2: return "BASE";
        case NEO2_LAYER_3:       return "NEO3";
        case NEO2_LAYER_4:       return "NEO4";
        case NEO2_LAYER_5:       return "NEO5";
        case NEO2_LAYER_6:       return "NEO6";
        case DE_NORMAL:          return "US";
        case FKEYS:              return "FN";
        default:                 return "UNKNOWN";
    }
}
#endif

static bool process_long_thumb_enter(uint16_t keycode, keyrecord_t *record);
static void arm_thumb_space_repeat(uint16_t keycode, keyrecord_t *record);
static void update_status_leds(layer_state_t state, uint8_t unicode_mode);

#define THUMB_REPEAT_TERM 200

static uint16_t left_thumb_last_tap  = 0;
static uint16_t right_thumb_last_tap = 0;

static bool left_thumb_repeat_armed  = false;
static bool right_thumb_repeat_armed = false;

static bool left_thumb_repeating  = false;
static bool right_thumb_repeating = false;

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
 * | ̂ /c    |   X  |   V  |   L  |   C  |   W  |  L4  |           |  L4  |   Y  |   U  |   I  |   O  |   P  |   \    |
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
    KC_ESCAPE,              NEO2_1,         NEO2_2,         NEO2_3,         NEO2_4,         NEO2_5,         NEO2_ACUTE_CEDILLA,                             NEO2_GRAVE_TILDE,   NEO2_6,         NEO2_7,         NEO2_8,         NEO2_9,             NEO2_0,        NEO2_MINUS,
    NEO2_CIRCUMFLEX_CARON,  KC_X,           KC_V,           KC_L,           KC_C,           KC_W,           MO(NEO2_LAYER_4),                               MO(NEO2_LAYER_4),   KC_K,           KC_H,           KC_G,           KC_F,               KC_Q,          NEO2_SS,
    KC_TAB,                 KC_U,           KC_I,           KC_A,           KC_E,           KC_O,                                                                                       KC_S,           KC_N,           KC_R,       KC_T,           KC_D,          KC_Y,
    MO(NEO2_LAYER_3),       NEO2_UE,        NEO2_OE,        NEO2_AE,        KC_P,           KC_Z,           KC_HYPR,                                        KC_MEH,             KC_B,           KC_M,           NEO2_COMMA,     NEO2_DOT,           KC_J,          MO(NEO2_LAYER_3),
    KC_LEFT_GUI,            MO(FKEYS),      KC_TRANSPARENT, KC_UP,          KC_DOWN,                                                                                                                            KC_LEFT,        KC_RIGHT,   KC_TRANSPARENT, MO(FKEYS), KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT,             DISCO_TOGGLE,   LAG(KC_EQUAL), LAG(KC_MINUS),
                                                                                                                                KC_HOME,        KC_PAGE_UP,
                                                                            THUMB_SPACE_LEFT, MT(MOD_LCTL, KC_DELETE),    KC_END,         KC_PGDN,       MT(MOD_RALT, KC_BSPC), THUMB_SPACE_RIGHT
  ),
  [NEO2_LAYER_3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_TRANSPARENT,
    KC_TRANSPARENT, NEO2_L3_ELLIPSIS, KC_UNDS,        KC_LBRC,        KC_RBRC,        KC_CIRC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_EXLM,        KC_LABK,        KC_RABK,        KC_EQUAL,       KC_AMPR,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_BSLS,        KC_SLASH,       KC_LCBR,        KC_RCBR,        KC_ASTR,                                                                        KC_QUES,        KC_LPRN,        KC_RPRN,        KC_MINUS,       KC_COLN,        KC_AT,
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_PIPE,        KC_TILD,        KC_GRAVE,       KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PLUS,        KC_PERC,        KC_DQUO,        KC_QUOTE,       KC_SCLN,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, MS_WHLD, MS_UP, MS_DOWN,                                                                                                 MS_LEFT, MS_RGHT, MS_BTN1, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, HSV_172_255_255,LAG(KC_8), KC_TRANSPARENT,
                                                                                                                    HSV_86_255_128, KC_TRANSPARENT,
                                                                                    S(KC_ENT),        UG_VALD,        UG_VALU, KC_TRANSPARENT, UG_HUEU, S(KC_ENT)
  ),
  [NEO2_LAYER_4] = LAYOUT_ergodox_pretty(
    KC_NO, NEO2_L4_FEMININE_ORDINAL, NEO2_L4_MASCULINE_ORDINAL, NEO2_L4_NUMERO_SIGN, NEO2_L4_MIDDLE_DOT, NEO2_L4_BRITISH_POUND, NEO2_L4_CURRENCY_SIGN,                   KC_NO,          KC_NO,                    KC_TAB, KC_PSLS,  KC_PAST,   KC_PMNS,     KC_NO,
    KC_NO, KC_PGUP,                  KC_BSPC,                   KC_UP,               KC_DEL,             KC_PGDN,               KC_TRNS,                                 KC_TRNS,        NEO2_L4_INV_EXCLAMATION,  KC_7,   KC_8,     KC_9,      KC_PLUS,     NEO2_L4_EN_DASH,
    KC_NO, KC_HOME,                  KC_LEFT,                   KC_DOWN,             KC_RGHT,            KC_END,                                                                                 NEO2_L4_INV_QUESTIONMARK, KC_4,   KC_5, KC_6,  KC_COMM,     KC_DOT,
    KC_NO, KC_ESC,                   KC_TAB,                    KC_INS,              KC_ENT,             C(KC_Z),               KC_NO,                                   KC_NO,          KC_COLN,                  KC_1,   KC_2,     KC_3,      KC_SCLN,     KC_NO,
    KC_NO, KC_TRNS,                  KC_NO,                     KC_NO,               KC_NO,                                                                                                                                        KC_NO,  KC_0, KC_NO, KC_TRNS, KC_NO,
                                                                                                                             KC_TRANSPARENT,        KC_TRANSPARENT,                          KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                                                        KC_TRANSPARENT,                          KC_TRANSPARENT,
                                                                                                     KC_TRANSPARENT,     KC_TRANSPARENT,        KC_TRANSPARENT,                          KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT
  ),
  [NEO2_LAYER_5] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [NEO2_LAYER_6] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, MS_LEFT,     MS_DOWN,     MS_RGHT,    KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MS_BTN1,     MS_BTN2,                                                                                                     KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
  ),
  [DE_NORMAL] = LAYOUT_ergodox_pretty(
    // Number row
    KC_ESC,
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
    KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,

    // QWERTY row
    KC_TAB,
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC,
    KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,

    // Home row
    KC_CAPS,
    KC_A, KC_S, KC_D, KC_F, KC_G,
    KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,

    // Shift row
    KC_LSFT,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO,
    KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,

    // Bottom wing
    KC_LGUI,
    MO(FKEYS),
    KC_LALT,
    KC_LEFT,
    KC_RIGHT,

    KC_UP,
    KC_DOWN,
    KC_RALT,
    MO(FKEYS),
    KC_RGUI,

    // Upper thumb keys
    KC_APP,
    KC_LGUI,
    KC_RALT,
    KC_RCTL,

    // Inner thumb keys
    KC_HOME,
    KC_PGUP,

    // Main thumb keys
    THUMB_SPACE_LEFT,
    MT(MOD_LCTL, KC_DEL),
    KC_END,
    KC_PGDN,
    MT(MOD_RALT, KC_BSPC),
    THUMB_SPACE_RIGHT
  ),
  [FKEYS] = LAYOUT_ergodox_pretty(
    // F1-F12; bootloader is deliberately FN + top-left
    QK_BOOT,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
    KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
    BASE_TOGGLE,

    // F13-F24
    KC_NO,
    KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
    KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
    KC_NO,

    // Central pair: Linux and Windows/WinCompose
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UC_LINX,
    UC_WINC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

    // Underglow/Disco on the left; media on the right
    KC_TRANSPARENT,
    UG_TOGG,
    UG_VALD,
    UG_VALU,
    UG_HUED,
    UG_HUEU,
    DISCO_TOGGLE,

    KC_MEDIA_PREV_TRACK,
    KC_MEDIA_PLAY_PAUSE,
    KC_MEDIA_NEXT_TRACK,
    KC_AUDIO_VOL_DOWN,
    KC_AUDIO_MUTE,
    KC_AUDIO_VOL_UP,
    KC_TRANSPARENT,

    // Bottom wing: FN keys must be transparent
    KC_NO,
    KC_TRANSPARENT,
    KC_NO,
    KC_NO,
    KC_NO,

    KC_NO,
    KC_NO,
    KC_NO,
    KC_TRANSPARENT,
    KC_NO,

    // Preserve thumb-cluster keys and modifiers
    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT,

    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT
    )
};

const uint16_t PROGMEM combo0[] = {
    THUMB_SPACE_LEFT,
    THUMB_SPACE_RIGHT,
    COMBO_END
};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_ENTER),
};

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case THUMB_SPACE_LEFT:
            if (record->event.pressed) {
                if (left_thumb_repeat_armed &&
                    timer_elapsed(left_thumb_last_tap) <= THUMB_REPEAT_TERM) {
                    left_thumb_repeat_armed = false;
                    left_thumb_repeating    = true;

                    register_code(KC_SPC);
                    return false;
                }

                left_thumb_repeat_armed = false;
            } else if (left_thumb_repeating) {
                unregister_code(KC_SPC);

                left_thumb_repeating   = false;
                left_thumb_last_tap    = timer_read();
                left_thumb_repeat_armed = true;

                return false;
            }
            break;

        case THUMB_SPACE_RIGHT:
            if (record->event.pressed) {
                if (right_thumb_repeat_armed &&
                    timer_elapsed(right_thumb_last_tap) <= THUMB_REPEAT_TERM) {
                    right_thumb_repeat_armed = false;
                    right_thumb_repeating    = true;

                    register_code(KC_SPC);
                    return false;
                }

                right_thumb_repeat_armed = false;
            } else if (right_thumb_repeating) {
                unregister_code(KC_SPC);

                right_thumb_repeating    = false;
                right_thumb_last_tap     = timer_read();
                right_thumb_repeat_armed = true;

                return false;
            }
            break;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (process_long_thumb_enter(keycode, record)) {
    return false;
  }

  arm_thumb_space_repeat(keycode, record);

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
    case DISCO_TOGGLE:
      if (record->event.pressed) {
          disco_mode_enabled = !disco_mode_enabled;

          if (disco_mode_enabled) {
              rgblight_enable_noeeprom();
              rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
          } else {
              rgblight_reload_from_eeprom();
          }
      }
      return false;
    case BASE_TOGGLE:
        if (record->event.pressed) {
            layer_invert(DE_NORMAL);
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

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(
        state,
        NEO2_LAYER_3,
        NEO2_LAYER_4,
        NEO2_LAYER_6
    );

    update_status_leds(state, default_layer_state);

#ifdef CONSOLE_ENABLE
    uprintf("LAYER:%s\n", layer_name(get_highest_layer(state)));
#endif

    return state;
}

void keyboard_post_init_user(void) {
  update_status_leds(layer_state, default_layer_state);
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

void unicode_input_mode_set_user(uint8_t input_mode) {
    update_status_leds(layer_state, input_mode);
}

static bool process_long_thumb_enter(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed || record->tap.count == 0) {
        return false;
    }

    uint8_t opposite_shift = 0;

    switch (keycode) {
        case THUMB_SPACE_LEFT:
            opposite_shift = MOD_BIT(KC_RSFT);
            break;

        case THUMB_SPACE_RIGHT:
            opposite_shift = MOD_BIT(KC_LSFT);
            break;

        default:
            return false;
    }

    uint8_t saved_mods = get_mods();

    if (!(saved_mods & opposite_shift)) {
        return false;
    }

    del_mods(MOD_MASK_SHIFT);
    send_keyboard_report();

    tap_code(KC_ENT);

    set_mods(saved_mods);
    send_keyboard_report();

    return true;
}

static void arm_thumb_space_repeat(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed || record->tap.count == 0) {
        return;
    }

    switch (keycode) {
        case THUMB_SPACE_LEFT:
            left_thumb_last_tap     = timer_read();
            left_thumb_repeat_armed = true;
            break;

        case THUMB_SPACE_RIGHT:
            right_thumb_last_tap     = timer_read();
            right_thumb_repeat_armed = true;
            break;
    }
}

static void update_status_leds(
    layer_state_t state,
    layer_state_t default_state
) {
    uint8_t layer = get_highest_layer(state | default_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();  // red
    ergodox_right_led_2_off();  // blue
    ergodox_right_led_3_off();  // green

    switch (layer) {
        case NEO2_LAYER_1_AND_2:
            if (get_unicode_input_mode() == UNICODE_MODE_LINUX) {
                ergodox_right_led_3_on();  // green
            } else if (
                get_unicode_input_mode() == UNICODE_MODE_WINCOMPOSE
            ) {
                ergodox_right_led_1_on();  // red
            }
            break;

        case NEO2_LAYER_3:
            ergodox_right_led_1_on();      // red
            break;

        case NEO2_LAYER_4:
            ergodox_right_led_2_on();      // blue
            break;

        case NEO2_LAYER_5:
            ergodox_right_led_3_on();      // green
            break;

        case NEO2_LAYER_6:
            ergodox_right_led_1_on();      // red
            ergodox_right_led_3_on();      // green
            break;

        case DE_NORMAL:
            ergodox_right_led_1_on();      // red
            ergodox_right_led_2_on();      // blue
            break;

        case FKEYS:
            ergodox_right_led_2_on();      // blue
            ergodox_right_led_3_on();      // green
            break;
    }
}
