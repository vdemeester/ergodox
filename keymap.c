/* vdemeester personal ergodox layout  */
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "led.h"
#include "keymap_bepo.h"

/* Layers */
enum {
  BASE = 0,
  BEPO,
  NMDIA,
  NUMR,
  FNLR,
};

/* Macros */
enum {
  MDBL0 = 0,

  MFNLR,

  // Function / number keys
  KF_1, // 1, F1
  KF_2, // 2, F2
  KF_3, // ...
  KF_4,
  KF_5,
  KF_6,
  KF_7,
  KF_8,
  KF_9,
  KF_10,
  KF_11,
  KF_12,

  // Cut/Copy/Paste
  MCUT,
  MCOPY,
  MPSTE
};

/* Fn keys */
enum {
  F_BSE = 0,
  F_BEPO,
  F_SFT,
  F_ALT,
  F_CTRL
};

/* States & timers */
uint16_t kf_timers[12];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Del  |           | Del  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |Backsp|           |Backsp|   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '/Shift|
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | \/Shift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl |  fn  | App  | LGui | Alt  |                                      | RAlt |   [  | Home |   ]  |End/Ctl|
 *   `-----------------------------------'                                      `-----------------------------------'
 *                                       ,--------------.       ,-------------.
 *                                       | Play  | num  |       | Left |Right |
 *                                ,------+-------+------|       |------+------+------.
 *                                |      |       | PgUp |       |  Up  |      |      |
 *                                |Space |Backsp |------|       |------|RShift|Enter |
 *                                |      |       | PgDn |       | Down |      |      |
 *                                `---------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
                // left hand
                KC_GRV,    M(KF_1),   M(KF_2),   M(KF_3),        M(KF_4),  M(KF_5),  M(KF_11),
                KC_TAB,       KC_Q,      KC_W,      KC_E,           KC_R,     KC_T,   KC_BSPC,
                M(MFNLR),     KC_A,      KC_S,      KC_D,           KC_F,     KC_G,
                KC_LSFT,      KC_Z,      KC_X,      KC_C,           KC_V,     KC_B,    KC_ENT,
                KC_LCTL,  M(MFNLR),  F(F_BEPO),  KC_LGUI,  ALT_T(KC_ESC),

                KC_DELT,  TG(NUMR),
                KC_PGUP,
                KC_SPC,    KC_BSPC,  KC_PGDN,

                // right hand
                M(KF_12),     M(KF_6),   M(KF_7),    M(KF_8),    M(KF_9),    M(KF_10),     KC_MINS,
                KC_BSPC,     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_EQL,
                KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  SFT_T(KC_QUOT),
                KC_ENT,      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SFT_T(KC_BSLS),
                KC_RALT, KC_RBRC, KC_HOME, KC_LBRC,   CTL_T(KC_END),
                
                KC_LEFT, KC_RGHT,
                KC_UP,
                KC_DOWN, KC_RSFT,  KC_ENT
         ),
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   #    |   "  |   «  |   »  |   (  |   )  | INS  |           |   %  |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   B  |   É  |   P  |   O  |   È  |Back  |           |Back  |   !  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|Space |           |Space |------+------+------+------+------+--------|
 * | ~L1/Ê  |   A  |   U  |   I  |   E  |   ;  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
 * | Ç      |   À  |   Y  |   X  |   .  |   K  |      |           |      |   ?  |   Q  |   G  |   H  |   F  |   W    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | MUTE |  V+  |  V-  | GUI  | LAlt |                                       | MENU |      |      |      |    L2  |
 *   `----------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | DEL  | GUI  |       | PgUp | Esc  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | LAlt |       | PgDn |        |      |
 *                                 | Space|LShift|------|       |------| RShift |Space |
 *                                 |      |      |ctr/Es|       | RAlt |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_                      *
[BEPO] = KEYMAP(  // layer                       0 : default
        // left hand
   BP_DOLLAR,                        BP_DOUBLE_QUOTE,     BP_LEFT_GUILLEMET,   BP_RIGHT_GUILLEMET,   BP_LEFT_PAREN, BP_RIGHT_PAREN,   KC_INSERT,
   KC_TAB,                           BP_B,                BP_E_ACUTE,          BP_P,                 BP_O,          BP_E_GRAVE,       KC_BSPC,
   LT(MFNLR, BP_E_CIRCUMFLEX), BP_A,                BP_U,                BP_I,                 BP_E,          BP_COMMA,        
   BP_C_CEDILLA,                     BP_A_GRAVE,          BP_Y,                BP_X,                 BP_DOT,        BP_K,             KC_ENT,
   KC_MUTE,                          KC_VOLU,             F(F_BEPO),             KC_LGUI,              KC_LALT,
                                                                                                           KC_DELETE,        KC_RGUI,
                                                                                                                             KC_LALT,
                                                                                            KC_SPC,        KC_LSHIFT,        CTL_T(KC_ESCAPE),

        // right hand
   BP_PERCENT,              BP_AT,               BP_PLUS,             BP_MINUS,             BP_SLASH,      BP_ASTERISK,         BP_EQUAL,
   KC_BSPC,                 BP_DEAD_CIRCUMFLEX,  BP_V,                BP_D,                 BP_L,          BP_J,                BP_Z,
                            BP_C,                BP_T,                BP_S,                 BP_R,          BP_N,                BP_M,
   KC_ENT,                  BP_APOSTROPHE,       BP_Q,                BP_G,                 BP_H,          BP_F,                BP_W,
                                                 KC_APP,              KC_UNDEFINED,         KC_UNDEFINED,  KC_UNDEFINED,        TG(NMDIA),
   KC_PGUP,                 KC_ESC,
   KC_PGDN,
   KC_RALT,                 KC_RSHIFT,           KC_SPACE
),
/* Navigation and media layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |n.lock|c.lock|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[NMDIA] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                                               KC_TRNS, KC_TRNS,KC_TRNS,
       // right hand
       KC_INS,  KC_F6,   KC_F7,   KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                KC_UP,   KC_END,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
       KC_LEFT, KC_DOWN, KC_RGHT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                         KC_TRNS, KC_P0,   M(MDBL0),KC_PDOT, CTL_T(KC_PENT),

       KC_NLCK, KC_CAPS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Numeric Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |n.lock|c.lock|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[NUMR] = KEYMAP(
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                                               KC_TRNS, KC_TRNS,KC_TRNS,
       // right hand
       KC_INS,  KC_F6,   KC_F7,   KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                KC_UP,   KC_END,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
       KC_LEFT, KC_DOWN, KC_RGHT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                         KC_TRNS, KC_P0,   M(MDBL0),KC_PDOT, CTL_T(KC_PENT),

       KC_NLCK, KC_CAPS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* fn layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |Insert|           |Insert|Eject |Power |Sleep | Wake |PrtScr|ScrollLk|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |VolUp |           |      |      |      | MsUp |      |      | Pause  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | Calc | Mail |Browsr|------|           |------|      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       | Lclk | Mclk | Rclk |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Next |      |      |
 *                                 | Mute |      |------|       |------|      |      |
 *                                 |      |      |      |       | Prev |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[FNLR] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_INS,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,      KC_TRNS, KC_VOLU,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_CALC,     KC_MAIL,      KC_WHOM,
       KC_TRNS, KC_TRNS, M(MCUT),      M(MCOPY),    M(MPSTE),     KC_MUTE, KC_VOLD,
       KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,

                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_MUTE, KC_TRNS, KC_TRNS,
    // right hand
       KC_INS,   KC_EJCT, KC_PWR,  KC_SLEP, KC_WAKE, KC_PSCR, KC_SLCK,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_PAUS,
                 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, KC_TRNS,

       KC_TRNS, KC_TRNS,
       KC_BTN4,
       KC_BTN5, KC_MPRV, KC_MNXT
),
};

const uint16_t PROGMEM fn_actions[] = {
  [F_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS),
  [F_BEPO] = ACTION_LAYER_INVERT(BEPO, ON_PRESS),
  [F_SFT]  = ACTION_MODS_ONESHOT (MOD_LSFT),
  [F_ALT]  = ACTION_MODS_ONESHOT (MOD_LALT),
  [F_CTRL] = ACTION_MODS_ONESHOT (MOD_LCTL)
};

static bool from_appsel;

static void handle_kf (keyrecord_t *record, uint8_t id)
{
  uint8_t code = id - KF_1;
  
  if (record->event.pressed) {
    kf_timers[code] = timer_read ();
  } else {
    uint8_t kc_base;

    if (from_appsel) {
      from_appsel = false;
      return;
    }

    if (kf_timers[code] && timer_elapsed (kf_timers[code]) > TAPPING_TERM) {
      // Long press
      kc_base = KC_F1;
    } else {
      kc_base = KC_1;
    }
    kf_timers[code] = 0;
    code += kc_base;

    register_code (code);
    unregister_code (code);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
    case MDBL0:
      if (record->event.pressed) {
        return MACRO( I(25), T(P0), T(P0), END );
      }
      break;
    case MFNLR:
      layer_state ^= (1 << NUMR) | (1 << FNLR);
      break;
    case MCUT:
      if (record->event.pressed) {
        return MACRO(D(LSFT), T(DELT), U(LSFT), END);
      }
      break;
    case MCOPY:
      if (record->event.pressed) {
        return MACRO(D(LCTL), T(INS), U(LCTL), END);
      }
      break;
    case MPSTE:
      if (record->event.pressed) {
        return MACRO(D(LSFT), T(INS), U(LSFT), END);
      }
      break;
    case KF_1 ... KF_12:
      handle_kf (record, id);
      break;
    }
    return MACRO_NONE;
};

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

    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_1_on();
    }
    switch (layer) {
    case FNLR:
      ergodox_right_led_2_on();
      break;
    case NUMR:
      ergodox_right_led_3_on();
      break;
    default:
      // none
      break;
    }
    /* // led 1: numeric layer */
    /* if (layer_state & (1 << NUMR)) { */
    /*     ergodox_right_led_2_on(); */
    /* } */
    /* // led 2: FNLR */
    /* if (default_layer_state == 1 << FNLR) { */
    /*     ergodox_right_led_1_on(); */
    /* } */
    
};
