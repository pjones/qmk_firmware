#include "minidox.h"
#include "action_layer.h"

/******************************************************************************/
static uint8_t g_usb_led    = 0;
static uint8_t g_layer_keys = 0;

/******************************************************************************/
typedef struct {
  uint8_t  tap_layer_one;       // Tapping once goes to this layer.
  uint8_t  tap_layer_two;       // Second tap turns this layer on.
  uint16_t tap_layer_key;       // If a layer wasn't used, send this key.
} dance_layer_t;

/******************************************************************************/
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
};

/******************************************************************************/
enum {
  LAYER_BASE = 0,
  LAYER_SYMB,
  LAYER_NUMBERS,
  LAYER_MOVEMENT,
  LAYER_WINMGR,
  LAYER_MOUSE,
  LAYER_DRAW
};

/******************************************************************************/
enum {
  TD_SYMB_OR_MOUSE = 0,
  TD_NUMBERS_OR_WINMGR,
  TD_PAREN,
  TD_CURLY,
  TD_SQUARE,
  TD_ANGLE,
  TD_QUOTE
};

/******************************************************************************/
enum {
  M_EMACS_PLUS = 0,
  M_EMACS_MINU
};

/******************************************************************************/
#define ________       KC_TRANSPARENT
#define XXXXXXXX       KC_NO
#define JUST_1_SPC     LCTL(LALT(KC_SPACE))
#define LAYER_LEFT     TD(TD_SYMB_OR_MOUSE)
#define LAYER_RIGHT    TD(TD_NUMBERS_OR_WINMGR)
#define DRAW_KEY       LT(LAYER_DRAW, KC_TAB)
#define LAYER_TAP_TERM 120

/******************************************************************************/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER_BASE
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |DRAW | LAYER | BSpc |    | Space| LAYER | Enter |
 *                  `-------------|      |    |      |-------+-------.
 *                                | Ctrl |    | Alt  |
 *                                `------'    `------'
 */
[LAYER_BASE] = KEYMAP(
  KC_Q,        KC_W,   KC_E,  KC_R,        KC_T, /*|*/ KC_Y,  KC_U,         KC_I,    KC_O,    KC_P,
  GUI_T(KC_A), KC_S,   KC_D,  SFT_T(KC_F), KC_G, /*|*/ KC_H,  SFT_T(KC_J),  KC_K,    KC_L,    GUI_T(KC_SCLN),
  KC_Z,        KC_X,   KC_C,  KC_V,        KC_B, /*|*/ KC_N,  KC_M,         KC_COMM, KC_DOT,  KC_SLSH,
                                                 /*|*/
         DRAW_KEY, LAYER_LEFT, CTL_T(KC_BSPACE), /*|*/ ALT_T(KC_SPACE), LAYER_RIGHT, KC_ENTER
),

/* LAYER_SYMB
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  \   |  `   |  |   |  +   |  =   |           |   _  |   -  | <  > | {  } | [  ] |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  !   |  @   |  #   |  $   |  %   |           |   ^  |   &  |  *   | (  ) | '  " |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | J1S  |      |      |  ~   |AltGR |           |Font +|Font -|      | <  > |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[LAYER_SYMB] = KEYMAP(
  KC_BSLASH,  KC_GRAVE, KC_PIPE,  KC_PLUS, KC_EQUAL,   /*|*/ KC_UNDS,         KC_MINUS,        TD(TD_ANGLE), TD(TD_CURLY),    TD(TD_SQUARE),
  KC_EXLM,    KC_AT,    KC_HASH,  KC_DLR,  KC_PERCENT, /*|*/ KC_CIRC,         KC_AMPR,         KC_ASTR,      TD(TD_PAREN),    TD(TD_QUOTE),
  JUST_1_SPC, XXXXXXXX, XXXXXXXX, KC_TILD, KC_RALT,    /*|*/ M(M_EMACS_PLUS), M(M_EMACS_MINU), XXXXXXXX,     TD(TD_ANGLE),    XXXXXXXX,
                                                       /*|*/
                       ________, ________, ________,   /*|*/ ________, ________, ________
),

/* LAYER_NUMBERS
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  | F11  | F12  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | F13  | F14  |   #  |   $  |   %  |           |   :  |   -  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
  */
[LAYER_NUMBERS] = KEYMAP(
  KC_F1,  KC_F2,  KC_F3,   KC_F4,     KC_F5,      /*|*/ KC_F6,    KC_F7,    KC_F8,    KC_F11, KC_F12,
  KC_1,   KC_2,   KC_3,    KC_4,      KC_5,       /*|*/ KC_6,     KC_7,     KC_8,     KC_9,   KC_0,
  KC_F13, KC_F14, KC_HASH, KC_DOLLAR, KC_PERCENT, /*|*/ KC_COLON, KC_MINUS, KC_COMMA, KC_DOT, KC_SLASH,
                                                  /*|*/
                   ________, ________,  ________, /*|*/ ________, ________, ________
),

/* LAYER_MOVEMENT
 *
 * ,----------------------------------.           ,----------------------------------.
 * |S-Tab |      |      |S-Ins | Ins  |           | Home | PgDn | PgUp | End  |M-Ent |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Tab  |      | DEL  | Esc  | Caps |           | Left | Down |  Up  | Rght | Ent  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |C-Tab |      |      |      |      |           | Ms-L | Ms-D | Ms-U | Ms-R |C-Ent |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
  */
[LAYER_MOVEMENT] = KEYMAP(
  LSFT(KC_TAB), XXXXXXXX,  XXXXXXXX, LSFT(KC_INS), KC_INS,   /*|*/ KC_HOME,    KC_PGDN,    KC_PGUP,  KC_END,      LALT(KC_ENT),
  KC_TAB,       XXXXXXXX,  KC_DEL,   KC_ESC,       KC_CAPS,  /*|*/ KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_ENT,
  LCTL(KC_TAB), XXXXXXXX,  XXXXXXXX, XXXXXXXX,     XXXXXXXX, /*|*/ KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, LCTL(KC_ENT),
                                                             /*|*/
                                ________, ________, ________,/*|*/ ________, ________, ________
),

/* LAYER_WINMGR
 *
 * ,----------------------------------.           ,----------------------------------.
 * |RESET |P-Clr | V-Dn | V-Up | Mute |           | M-1  | M-2  | M-3  | M-4  | M-5  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |Lock  |Radio | Prev | Next | Play |           | M-6  | M-7  | M-8  | M-9  | M-0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           | M-Lt | M-Dn | M-Up | M-Rt |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[LAYER_WINMGR] = KEYMAP(
  RESET,              LGUI(LSFT(KC_5)), LGUI(LSFT(KC_7)),    LGUI(LSFT(KC_8)),    LGUI(LSFT(KC_6)),    /*|*/ LGUI(KC_1),    LGUI(KC_2),    LGUI(KC_3),  LGUI(KC_4),     LGUI(KC_5),
  LGUI(LALT(KC_L)),   LGUI(LSFT(KC_4)), KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE, /*|*/ LGUI(KC_6),    LGUI(KC_7),    LGUI(KC_8),  LGUI(KC_9),     LGUI(KC_0),
  XXXXXXXX,           XXXXXXXX,         XXXXXXXX,            XXXXXXXX,            XXXXXXXX,            /*|*/ LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RIGHT), XXXXXXXX,
                                                                                                       /*|*/
                                                                        ________, ________,  ________, /*|*/ ________, ________,  ________
),

/* LAYER_MOUSE
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      |      |           | ACL0 | ACL1 | ACL2 |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |L-Clk |M-Clk |           | Left | Down |  Up  | Rght |R-Clk |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[LAYER_MOUSE] = KEYMAP(
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, /*|*/ KC_ACL0,  KC_ACL1,  KC_ACL2,  XXXXXXXX, XXXXXXXX,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, KC_BTN1,  KC_BTN2,  /*|*/ KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN3,
  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, /*|*/ XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
                                                    /*|*/
                      ________, ________, ________, /*|*/ ________, ________, ________
),

/* LAYER_DRAW
 *
 * ,----------------------------------.           ,----------------------------------.
 * |On/Off|Clear |Toggle|      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Undo |Erase |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Pen1 | Pen2 | Pen3 | Pen4 | Pen5 |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[LAYER_DRAW] = KEYMAP(
  KC_F9,     LSFT(KC_F9),    LCTL(KC_F9),  XXXXXXXX,       XXXXXXXX,         XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  KC_F10,    LALT(KC_LCTRL), XXXXXXXX,     XXXXXXXX,       XXXXXXXX,         XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
  KC_LSHIFT, KC_LCTRL,       KC_LALT,      LSFT(KC_LCTRL), LSFT(KC_LALT),    XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,

                                            ________, ________, ________,    ________, ________, ________
),

/* LAYER_BLANK
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,---------------.
 *                  |     |       |      |    |      |       |       |
 *                  `-------------|      |    |      |-------+-------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
/*
[LAYER_BLANK] = KEYMAP(
  ________, ________, ________, ________, ________,         ________, ________, ________, ________, ________,
  ________, ________, ________, ________, ________,         ________, ________, ________, ________, ________,
  ________, ________, ________, ________, ________,         ________, ________, ________, ________, ________,

                      ________, ________, ________,         ________, ________, ________
),
 */
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
 * layers and at the same time potentially send a normal key.  It's
 * like the LT layer switch, but allows multiple taps to select the
 * desired layer.
 */
void dance_layer_each(qk_tap_dance_state_t *state, void *user_data) {
  dance_layer_t *layers = (dance_layer_t *)user_data;

  switch (state->count) {
  case 1:
    g_layer_keys++;
    layer_on(layers->tap_layer_one);
    break;

  case 2:
    layer_off(layers->tap_layer_one);
    layer_on(layers->tap_layer_two);
    break;
  }

  update_tri_layer(LAYER_SYMB, LAYER_NUMBERS, LAYER_MOVEMENT);
}

/******************************************************************************/
/*
 * Reset function for `dance_layer_each'.
 */
void dance_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
  dance_layer_t *layers = (dance_layer_t *)user_data;

  // Deactivate the key's layer:
  if (!state->pressed) g_layer_keys--;
  if (g_layer_keys == 0) layer_clear();
  update_tri_layer(LAYER_SYMB, LAYER_NUMBERS, LAYER_MOVEMENT);

  // If the key wasn't used to trigger a layer, use it as a normal key:
  if (g_layer_keys == 0 && !state->interrupted &&
      timer_elapsed(state->timer) <= (LAYER_TAP_TERM + 50))
  {
    for (uint8_t i=0; i < state->count; i++) {
      register_code(layers->tap_layer_key);
      unregister_code(layers->tap_layer_key);
    }
  }
}

/******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
  [TD_SYMB_OR_MOUSE] = {
    .fn = { dance_layer_each, NULL, dance_layer_reset},
    .custom_tapping_term = LAYER_TAP_TERM,
    .user_data = (void *)&((dance_layer_t) { LAYER_SYMB
                                           , LAYER_MOUSE
                                           , KC_TAB
                                           })
  },

  [TD_NUMBERS_OR_WINMGR] = {
    .fn = { dance_layer_each, NULL, dance_layer_reset},
    .custom_tapping_term = LAYER_TAP_TERM,
    .user_data = (void *)&((dance_layer_t) { LAYER_NUMBERS
                                           , LAYER_WINMGR
                                           , KC_ENTER
                                           })
  },

  [TD_PAREN]    = ACTION_TAP_DANCE_DOUBLE(KC_LPRN,     KC_RPRN),
  [TD_CURLY]    = ACTION_TAP_DANCE_DOUBLE(KC_LCBR,     KC_RCBR),
  [TD_SQUARE]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, KC_RBRACKET),
  [TD_ANGLE]    = ACTION_TAP_DANCE_DOUBLE(KC_LABK,     KC_RABK),
  [TD_QUOTE]    = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE,    KC_DOUBLE_QUOTE),
};
