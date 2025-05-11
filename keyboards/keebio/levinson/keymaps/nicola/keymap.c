#include QMK_KEYBOARD_H

#include "nicola.h"     // Nicola
#define COMBO_TERM 32
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _QWERTY,
    _NICOLA,                // Nicola
    _LOWER,
    _RAISE
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,                     // Nicola
  NICOLA,                   // Nicola
  NLSHFT, NRSHFT,           // Nicola
  LOWER,
  RAISE
};

static uint16_t mkeys[2] = {RAISE, LOWER};      // Nicola
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  ]   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | GUI  |  Alt |      | Raise| Space|  -   | Bksp | Lower|  '   |  \   |   =  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RBRC,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_GRV , KC_LGUI, KC_LALT, RAISE,  KC_ENT,   KC_SPC,  KC_MINS, KC_BSPC,  LOWER,  KC_QUOT, KC_BSLS, KC_EQL
),

/* Nicola
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  ]   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  | GUI  |  Alt | RAISE| Enter| Space|      |  BS  |      |  '   |  \   |   =  |
 * `-----------------------------------------------------------------------------------'
 */
[_NICOLA] = LAYOUT_ortho_4x12(
  _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,   KC_P,   _______,
  _______,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,     KC_L,  KC_SCLN, _______,
  _______,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,  KC_DOT, KC_SLSH, _______,
   KC_GRV,_______,_______, _______,  KC_ENT,  KC_SPC,  _______, KC_BSPC, _______, _______, _______, _______
),

/* Lower
  ----------------------------------------------------------------------------------------------------------.
 |  ESC  |    !   |    @   |   Up   |    $   |    %   |    ^   |    &   |    *   |    (   |    )   |  Bksp  |
 |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 |  Ctrl |  Home  |   <-   |  Down  |   ->   |  PgUp  |        |        |        |        |        |        |
 |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 | Shift |  End   |        |  Down  |        |  PgDn  |        |        |        |        |        |  Shift |
 |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 |   ~   |  GUI   |  Alt   |        |  Enter |  Space |   #    | Delete |        |  Mute  |  Vol-  |  Vol+  |
  ----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_EXLM,  KC_AT ,  KC_UP ,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_LCTL, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______, _______, _______, _______, _______, _______,
  KC_LSFT, KC_END , _______, KC_DOWN, _______, KC_PGDN, _______, _______, _______, _______, _______, KC_RSFT,
   KC_GRV, KC_LGUI, KC_LALT, _______, KC_ENT ,  KC_SPC, KC_HASH , KC_DEL, _______, KC_MUTE, KC_VOLD, KC_VOLU
),

/* Raise
 .---------------------------------------------------------------------------------------------------------.
 |  ESC  | BKLGT+ |   F7   |   F8   |   F9   |   F12  |       |    7   |    8   |    9   |    *   |    (   |
 |-------+--------+--------+--------+--------+----------------+--------+--------+--------+--------+--------|
 |  Ctrl | BKLGT- |   F4   |   F5   |   F6   |   F11  |       |    5   |    6   |    7   |    :   |    )   |
 |-------+--------+--------+--------+--------+--------|-------+--------+--------+--------+--------+--------|
 | Shift |        |   F1   |   F2   |   F3   |   F10  |       |    1   |    2   |    3   |    /   | Shift  |
 |-------+--------+--------+--------+--------+--------+-------+--------+--------+--------+--------+--------|
 |   ~   |  GUI   |  Alt   |        |  Enter |  Space |   -   | BackSP |    0   |    .   |    \   |   +    |
 '---------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_ESC,   BL_UP,   KC_F7,  KC_F8,   KC_F9,   KC_F12, _______,   KC_7 ,   KC_8 ,   KC_9 , KC_ASTR, KC_LPRN,
  KC_LCTL, BL_DOWN,  KC_F4,  KC_F5,   KC_F6,   KC_F11, _______,   KC_4 ,   KC_5 ,   KC_6 , KC_COLN, KC_RPRN,
  KC_LSFT, _______,  KC_F1,  KC_F2,   KC_F3,   KC_F10, _______,   KC_1 ,   KC_2 ,   KC_3 , KC_SLSH, KC_RSFT,
  KC_GRV , KC_LGUI, KC_LALT, _______, KC_ENT,  KC_SPC, KC_MINS,   KC_BSPC,  KC_0 ,  KC_DOT, KC_BSLS, KC_PLUS
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

#endif

// COMBO Feature
enum combo_events {
  COMBO_EMAIL_OFFICE,
  COMBO_EMAIL_PRIVATE,
  COMBO_TO_ASCII,
  COMBO_TO_NICOLA,
  COMBO_AUTU_GUEST_WIFI_ID,
  COMBO_AUTU_GUEST_WIFI_PASS,
  COMBO_MAC,
  COMBO_WINDOWS,
  COMBO_LINUX,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!


/// OS input method mode for Japanese
enum os_input_method_mode {
    INPUT_METHOD_MODE_MAC,
    INPUT_METHOD_MODE_WINDOWS,
    INPUT_METHOD_MODE_LINUX
};
uint16_t current_os_mode = INPUT_METHOD_MODE_MAC;


const uint16_t PROGMEM email_combo_office[] = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM email_combo_private[] = {KC_W, KC_X, COMBO_END};
const uint16_t PROGMEM to_ascii_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM to_nicola_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM auth_id_combo[] = {KC_O, KC_DOT, COMBO_END};
const uint16_t PROGMEM auth_pass_combo[] = {KC_P, KC_SLSH, COMBO_END};
const uint16_t PROGMEM mode_to_mac[] = {KC_C, KC_M, COMBO_END};
const uint16_t PROGMEM mode_to_windows[] = {KC_C, KC_W, COMBO_END};
const uint16_t PROGMEM mode_to_linux[] = {KC_C, KC_L, COMBO_END};


combo_t key_combos[] = {
  [COMBO_EMAIL_OFFICE] = COMBO_ACTION(email_combo_office),
  [COMBO_EMAIL_PRIVATE] = COMBO_ACTION(email_combo_private),
  [COMBO_TO_ASCII] = COMBO_ACTION(to_ascii_combo),
  [COMBO_TO_NICOLA] = COMBO_ACTION(to_nicola_combo),
  [COMBO_AUTU_GUEST_WIFI_ID] = COMBO_ACTION(auth_id_combo),
  [COMBO_AUTU_GUEST_WIFI_PASS] = COMBO_ACTION(auth_pass_combo),
  [COMBO_MAC] = COMBO_ACTION(mode_to_mac),
  [COMBO_WINDOWS] = COMBO_ACTION(mode_to_windows),
  [COMBO_LINUX] = COMBO_ACTION(mode_to_linux)
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */


void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO_EMAIL_OFFICE:
      if (pressed) {
        SEND_STRING("user1@example.com");
      }
      break;
    case COMBO_EMAIL_PRIVATE:
      if (pressed) {
        SEND_STRING("user2@example.com");
      }
      break;
    case COMBO_AUTU_GUEST_WIFI_ID:
      if (pressed) {
        SEND_STRING("Secret_ID");
      }
      break;
    case COMBO_AUTU_GUEST_WIFI_PASS:
      if (pressed) {
        SEND_STRING("Secret_Password");
      }
      break;
    case COMBO_TO_ASCII:
      if (pressed) {
        layer_off(_NICOLA); // 親指シフト > ASCII
        if (current_os_mode == INPUT_METHOD_MODE_MAC) {
            register_code(KC_LNG2); // Mac
            unregister_code(KC_LNG2); // Mac
        }else if (current_os_mode == INPUT_METHOD_MODE_WINDOWS) {
            register_code(KC_INT5); // Win
            unregister_code(KC_INT5); // Win
        }else{
            tap_code16(LCTL(KC_GRV)); // Linux L-Ctrl+`
        }


      }
      break;
    case COMBO_TO_NICOLA:
      if (pressed) {
        layer_on(_NICOLA);  // ASCII > 親指シフト
        if (current_os_mode == INPUT_METHOD_MODE_MAC) {
          register_code(KC_LNG1); // Mac
          unregister_code(KC_LNG1); // Mac
        }else if (current_os_mode == INPUT_METHOD_MODE_WINDOWS) {
          register_code(KC_INT4); // Win
          unregister_code(KC_INT4); // Win
        }else{
          tap_code16(LCTL(KC_QUOT)); // Linux L-Ctrl+'
        }
      }
      break;
    case COMBO_MAC:
      if (pressed) {
        current_os_mode = INPUT_METHOD_MODE_MAC;
      }
      break;
    case COMBO_WINDOWS:
      if (pressed) {
        current_os_mode = INPUT_METHOD_MODE_WINDOWS;
      }
      break;
    case COMBO_LINUX:
      if (pressed) {
        current_os_mode = INPUT_METHOD_MODE_LINUX;
      }
      break;
  }
}


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  //return true;
  //return process_nicola(keycode, record, _NICOLA, NLSHFT, NRSHFT, mkeys);       // Nicola
  return process_nicola(keycode, record, _NICOLA, KC_SPC, KC_MINS, mkeys);       // Nicola
}
