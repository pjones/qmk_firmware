/******************************************************************************/
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/******************************************************************************/
static uint8_t g_usb_led    = 0;
static bool    g_layer_lock = false;

/******************************************************************************/
typedef struct {
    uint8_t tap_layer_one;
    uint8_t tap_layer_two;
} dance_layer_t;

/******************************************************************************/
typedef struct {
    uint16_t tap_kc1;
    uint16_t tap_kc2;
    uint16_t tap_kc3;
} dance_multitap_t;

/******************************************************************************/
enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    VRSN,
    RGB_SLD
};

/******************************************************************************/
enum {
    LAYER_BASE = 0,
    LAYER_SYMB,
    LAYER_NUMBERS,
    LAYER_MEDIA
};

/******************************************************************************/
enum {
    TD_TAB_OR_ALTSPC = 0,
    TD_SYMB_OR_NUMBERS,
    TD_NUMBERS_OR_MEDIA,
    TD_PAREN,
    TD_CURLY,
    TD_SQUARE,
    TD_ANGLE,
    TD_ESC_CAPS,
    TD_QUOTE
};

/******************************************************************************/
enum {
    M_EMACS_PLUS = 0,
    M_EMACS_MINU
};

/******************************************************************************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*############################################################################*/
/*
 * Basic Layer
 */
/*############################################################################*/
[LAYER_BASE] = KEYMAP(

  /**********************************************************************/
  // Left Hand:
  KC_MEDIA_PLAY_PAUSE,  KC_NO,       KC_NO,   KC_NO,     KC_NO,                KC_NO, LGUI(LSFT(KC_7)),
  KC_NO,                KC_Q,        KC_W,    KC_E,      KC_R,                 KC_T,  KC_NO,
  KC_NO,                GUI_T(KC_A), KC_S,    KC_D,      SFT_T(KC_F),          KC_G,  /* 2U ^^ */
  KC_NO,                KC_Z,        KC_X,    KC_C,      KC_V,                 KC_B,  KC_NO,
  KC_NO,                KC_NO,       KC_NO,   KC_NO,     TD(TD_TAB_OR_ALTSPC),

  // Left Thumb:
  KC_NO, KC_NO, KC_NO, CTL_T(KC_BSPACE), TD(TD_SYMB_OR_NUMBERS), KC_NO,

  /**********************************************************************/
  // Right Hand:
  LGUI(LSFT(KC_8)), KC_NO,     KC_NO,               KC_NO,    KC_NO,    KC_NO,            KC_MEDIA_NEXT_TRACK,
  KC_NO,            KC_Y,      KC_U,                KC_I,     KC_O,     KC_P,             KC_NO,
  /* 2U ^^ */       KC_H,      SFT_T(KC_J),         KC_K,     KC_L,     GUI_T(KC_SCOLON), KC_NO,
  KC_NO,            KC_N,      KC_M,                KC_COMMA, KC_DOT,   KC_SLASH,         LALT(KC_PSCREEN),
                               KC_ENTER,            KC_NO,    KC_NO,    KC_NO,            KC_NO,

  // Right Thumb:
  KC_NO, KC_NO, KC_NO, KC_NO, TD(TD_NUMBERS_OR_MEDIA), ALT_T(KC_SPACE)
),

/*############################################################################*/
/*
 * Symbol Layer:
 */
/*############################################################################*/
[LAYER_SYMB] = KEYMAP(

  /**********************************************************************/
  // Left Hand:
  KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT,
  KC_TRANSPARENT, KC_BSLASH,       KC_TRANSPARENT, KC_PIPE,        KC_PLUS,        KC_EQUAL,         KC_TRANSPARENT,
  KC_TRANSPARENT, KC_EXLM,         KC_AT,          KC_HASH,        KC_DLR,         KC_PERCENT,       /* 2U ^^ */
  KC_TRANSPARENT, TD(TD_ESC_CAPS), KC_DELETE,      KC_TRANSPARENT, KC_TILD,        LALT(KC_PSCREEN), KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Left Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  /**********************************************************************/
  // Right Hand:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,
  KC_TRANSPARENT, KC_UNDS,        KC_MINUS,        TD(TD_ANGLE),   TD(TD_CURLY),    TD(TD_SQUARE),   KC_TRANSPARENT,
  /* 2U ^^     */ KC_CIRC,        KC_AMPR,         KC_ASTR,        TD(TD_PAREN),    TD(TD_QUOTE),    KC_TRANSPARENT,
  KC_TRANSPARENT, KC_INSERT,      LSFT(KC_INSERT), KC_RALT,        M(M_EMACS_PLUS), M(M_EMACS_MINU), KC_TRANSPARENT,
                                  KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,  KC_TRANSPARENT,

  // Right Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
),

/*############################################################################*/
/*
 * Numbers Layer
 */
/*############################################################################*/
[LAYER_NUMBERS] = KEYMAP(

  /****************************************************************************/
  // Left Hand:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,
  KC_TRANSPARENT, GUI_T(KC_1),    KC_2,           KC_3,           SFT_T(KC_4),    KC_5,           /* 2U ^^ */
  KC_TRANSPARENT, KC_F11,         KC_F12,         KC_HASH,        KC_DOLLAR,      KC_PERCENT,     KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Left Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,


  /****************************************************************************/
  // Right Hand:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
  /* 2U ^^ */     KC_6,           SFT_T(KC_7),    KC_8,           KC_9,           GUI_T(KC_0),    KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_COMMA,       KC_DOT,         KC_COLON,       KC_TRANSPARENT,
                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Right Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
),

/*############################################################################*/
/*
 * 2: Media and Mouse Keys
 */
/*############################################################################*/
[LAYER_MEDIA] = KEYMAP(

  /****************************************************************************/
  // Left Hand:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT,      KC_TRANSPARENT,             KC_TRANSPARENT,      KC_TRANSPARENT,
  KC_TRANSPARENT, KC_HOME,        LGUI(LSFT(KC_5)), LGUI(LSFT(KC_7)),    LGUI(LSFT(KC_8)),           LGUI(LSFT(KC_6)),    KC_TRANSPARENT,
  KC_TRANSPARENT, GUI_T(KC_END),  LGUI(LSFT(KC_4)), KC_MEDIA_PREV_TRACK, SFT_T(KC_MEDIA_NEXT_TRACK), KC_MEDIA_PLAY_PAUSE, /* 2U ^^ */
  KC_TRANSPARENT, KC_MS_ACCEL0,   KC_TRANSPARENT,   KC_MS_BTN3,          KC_MS_BTN1,                 KC_MS_BTN2,          KC_TRANSPARENT,
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT,      KC_TRANSPARENT,

  // Left Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,


  /****************************************************************************/
  // Right Hand:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,    KC_PGUP,        KC_TRANSPARENT,
  /* 2U ^^ */     KC_LEFT,        SFT_T(KC_DOWN), KC_UP,          KC_RIGHT,       KC_PGDOWN,      KC_TRANSPARENT,
  KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_MS_ACCEL2,   KC_TRANSPARENT,
                                  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

  // Right Thumb:
  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
),

};

/******************************************************************************/
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
    case M_EMACS_PLUS:
        return MACRODOWN(D(LCTL), T(X), T(EQUAL), T(G), U(LCTL), END);
    case M_EMACS_MINU:
        return MACRODOWN(D(LCTL), T(X), T(MINUS), T(G), U(LCTL), END);
    };

    return MACRO_NONE;
};

/******************************************************************************/
/*
 * Tap Dance function that allows a single key to switch to multiple
 * layers.  It acts like the tap-toggle (TT) key in QMK except it can
 * work with more than one layer.
 *
 * If a layer is active then tapping the once will turn all layers
 * off.  Otherwise tap or tap and hold as many times as you want to
 * get to the desired layer.
 */
void dance_layer_each(qk_tap_dance_state_t *state, void *user_data) {
    dance_layer_t *layers = (dance_layer_t *)user_data;
    uint8_t layer = biton32(layer_state);
    bool shift_is_on = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

    layer_clear();

    // Test if layer locking is changing:
    if (state->count == 1) {
        g_layer_lock = g_layer_lock || shift_is_on;

        if (layer != 0 && shift_is_on) {
            g_layer_lock = false;
            return;
        }
    }

    switch (state->count) {
    case 1:
        layer_on(layers->tap_layer_one);
        break;

    case 2:
        layer_on(layers->tap_layer_two);
        break;
    }
}

/******************************************************************************/
/*
 * Reset function for `dance_layer_each'.
 */
void dance_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->interrupted || !g_layer_lock) {
        layer_clear();
        g_layer_lock = false;
    }
}

/******************************************************************************/
/*
 * Tap Dance function that acts like `ACTION_TAP_DANCE_DOUBLE' but can
 * handle more than two keys/taps.
 */
void dance_multitap_finish(qk_tap_dance_state_t *state, void *user_data) {
    dance_multitap_t *keys = (dance_multitap_t *)user_data;

    switch (state->count) {
    case 1:
        if (keys->tap_kc1) register_code16(keys->tap_kc1);
        break;
    case 2:
        if (keys->tap_kc2) register_code16(keys->tap_kc2);
        break;
    case 3:
        if (keys->tap_kc3) register_code16(keys->tap_kc3);
        break;
    }
}

/******************************************************************************/
/*
 * Reset function for `dance_multitap_finish'.
 */
void dance_multitap_reset(qk_tap_dance_state_t *state, void *user_data) {
    dance_multitap_t *keys = (dance_multitap_t *)user_data;

    switch (state->count) {
    case 1:
        if (keys->tap_kc1) unregister_code16(keys->tap_kc1);
        break;
    case 2:
        if (keys->tap_kc2) unregister_code16(keys->tap_kc2);
        break;
    case 3:
        if (keys->tap_kc3) unregister_code16(keys->tap_kc3);
        break;
    }
}

/******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case EPRM:
        if (record->event.pressed) {
            eeconfig_init();
        }
        return false;
        break;
    case VRSN:
        if (record->event.pressed) {
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        return false;
        break;
    }

    return true;
}

/******************************************************************************/
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    g_usb_led = 0;
};

/******************************************************************************/
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    // Reset all the LEDs:
    ergodox_led_all_off();

    if (g_usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Caps lock light should be on:
        ergodox_led_all_on();
    } else {
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
        default:
            break;
        }
    }
};

/******************************************************************************/
void led_set_kb(uint8_t usb_led) {
    g_usb_led = usb_led;
}

/******************************************************************************/
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(LAYER_SYMB) // FN1 - Momentary Layer 1 (Symbols)
};

/******************************************************************************/
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB_OR_ALTSPC] = {
        .fn = { NULL, dance_multitap_finish, dance_multitap_reset },
        .user_data = (void *)&((dance_multitap_t) { KC_TAB
                                                  , LALT(KC_SPACE)
                                                  , LCTL(LALT(KC_SPACE))
                                                  })
    },

    [TD_SYMB_OR_NUMBERS] = {
        .fn = { dance_layer_each, NULL, dance_layer_reset},
        .user_data = (void *)&((dance_layer_t) { LAYER_SYMB
                                               , LAYER_NUMBERS
                                               , false
                                               })
    },

    [TD_NUMBERS_OR_MEDIA] = {
        .fn = { dance_layer_each, NULL, dance_layer_reset},
        .user_data = (void *)&((dance_layer_t) { LAYER_NUMBERS
                                               , LAYER_MEDIA
                                               , false
                                               })
    },

    [TD_PAREN]    = ACTION_TAP_DANCE_DOUBLE(KC_LPRN,      KC_RPRN),
    [TD_CURLY]    = ACTION_TAP_DANCE_DOUBLE(KC_LCBR,      KC_RCBR),
    [TD_SQUARE]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET,  KC_RBRACKET),
    [TD_ANGLE]    = ACTION_TAP_DANCE_DOUBLE(KC_LABK,      KC_RABK),
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESCAPE,    KC_CAPSLOCK),

    [TD_QUOTE] = {
        .fn = { NULL, dance_multitap_finish, dance_multitap_reset },
        .user_data = (void *)&((dance_multitap_t) { KC_QUOTE
                                                  , KC_DOUBLE_QUOTE
                                                  , KC_GRAVE
                                                  })
    }
};
