#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/******************************************************************************/
// Keymap 0: Basic Layer
[BASE] = KEYMAP(

  /**********************************************************************/
  // Left Hand:
  KC_MEDIA_PLAY_PAUSE,  KC_1,        KC_2,    KC_3,      KC_4,        KC_5, LGUI(LSFT(KC_7)),
  LALT(LCTL(KC_SPACE)), KC_Q,        KC_W,    KC_E,      KC_R,        KC_T, KC_ESCAPE,
  LALT(KC_SPACE),       GUI_T(KC_A), KC_S,    KC_D,      SFT_T(KC_F), KC_G, /* 2U ^^ */
  KC_INSERT,            KC_Z,        KC_X,    KC_C,      KC_V,        KC_B, KC_TRANSPARENT,
  KC_HOME,              KC_END,      KC_PGUP, KC_PGDOWN, TT(1),

  // Left Thumb:
                     KC_TRANSPARENT, KC_TRANSPARENT,
                                     KC_RALT,
  CTL_T(KC_BSPACE),  LT(1, KC_TAB),  LSFT(KC_RALT),

  /**********************************************************************/
  // Right Hand:
  LGUI(LSFT(KC_8)), KC_6,      KC_7,        KC_8,     KC_9,     KC_0,             KC_MEDIA_NEXT_TRACK,
  KC_CAPSLOCK,      KC_Y,      KC_U,        KC_I,     KC_O,     KC_P,             KC_BSLASH,
  /* 2U ^^ */       KC_H,      SFT_T(KC_J), KC_K,     KC_L,     GUI_T(KC_SCOLON), KC_QUOTE,
  KC_TRANSPARENT,   KC_N,      KC_M,        KC_COMMA, KC_DOT,   KC_SLASH,         LALT(KC_PSCREEN),
                               TT(2),       KC_LEFT,  KC_UP,    KC_DOWN,          KC_RIGHT,

  // Right Thumb:
                  KC_TRANSPARENT,  KC_TRANSPARENT,
                                   KC_RALT,
  LSFT(KC_RALT),  LT(1,KC_ENTER),  ALT_T(KC_SPACE)
),

/******************************************************************************/
// Keymap 1: Symbol Layer
[SYMB] = KEYMAP(

  /**********************************************************************/
  // Left Hand:
  KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,   KC_F11,
  KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,    KC_TRANSPARENT,
  KC_PLUS,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC, /* 2U ^^ */
  KC_TRANSPARENT, KC_TRANSPARENT, KC_LCBR,        KC_RCBR,        KC_TILD,        KC_PIPE, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Left Thumb:
                   KC_TRANSPARENT,  KC_TRANSPARENT,
                                    KC_TRANSPARENT,
  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,

  /**********************************************************************/
  // Right Hand:
  KC_F12,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
  KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_EQUAL,
  /* 2U ^^     */ KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_MINUS,
  KC_TRANSPARENT, KC_UNDS,        KC_COMMA,       KC_LBRACKET,    KC_RBRACKET,    KC_SLASH,       KC_TRANSPARENT,
                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Right Thumb:
                   KC_TRANSPARENT,  KC_TRANSPARENT,
                                    KC_TRANSPARENT,
  KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT
),

/******************************************************************************/
// Keymap 2: Media and Mouse Keys
[MDIA] = KEYMAP(

  /****************************************************************************/
  // Left Hand:
  LALT(KC_F6),    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT,      LALT(LSFT(KC_F11)), LALT(KC_F11),
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_6)), KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT,     KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_8)), KC_MEDIA_NEXT_TRACK, LGUI(LSFT(KC_4)),   /* 2U ^^ */
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_7)), KC_MEDIA_PREV_TRACK, LGUI(LSFT(KC_5)),   KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT,

  // Left Thumb:
                   KC_TRANSPARENT, KC_TRANSPARENT,
                                   KC_TRANSPARENT,
      KC_MS_BTN1,  KC_MS_BTN3,     KC_TRANSPARENT,


  /****************************************************************************/
  // Right Hand:
  LALT(KC_F12),   LALT(LSFT(KC_F12)), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_F10),
  KC_TRANSPARENT, KC_TRANSPARENT,     KC_MS_WH_UP,    KC_MS_UP,       KC_MS_WH_DOWN,  KC_TRANSPARENT, KC_TRANSPARENT,
  /* 2U ^^ */     KC_MS_WH_LEFT,      KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_WH_RIGHT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT,     KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_TRANSPARENT, KC_TRANSPARENT,
                                      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Right Thumb:
                   KC_TRANSPARENT, KC_TRANSPARENT,
                                   KC_TRANSPARENT,
  KC_TRANSPARENT,  KC_MS_BTN4,     KC_MS_BTN2

),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

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
    default:
        break;
    }
};
