/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define COMBO_TERM 250

#define USB_SUSPEND_WAKEUP_DELAY 0
#define FIRMWARE_VERSION u8"ODEQ9/eDDgx"
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61
#define LAYER_STATE_8BIT
#define COMBO_COUNT 1

#define ERGODOX_LED_30

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
#define UNICODE_KEY_LNX  LCTL(LSFT(KC_U))

