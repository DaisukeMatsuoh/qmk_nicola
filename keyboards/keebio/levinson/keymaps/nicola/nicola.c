/* Copyright 2018-2019 eswai <@eswai>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "nicola.h"

static uint8_t ncl_chrcount = 0; // 文字キー入力のカウンタ (シフトキーを除く)
static uint8_t ncl_keycount = 0; // シフトキーも含めた入力のカウンタ
static uint8_t ncl_modcount = 0; // modifierキー入力のカウンタ
static bool ncl_rshift = false; // 右シフトキーの状態
static bool ncl_lshift = false; // 左シフトキーの状態
static bool ncl_modifier_active = false;  // modifierがアクティブだったかを記録

// 文字入力バッファ
static uint16_t ninputs[5];

// NICOLA配列のテーブル
typedef struct {
  char t[4]; // 単独
  char l[4]; // 左シフト
  char r[4]; // 右シフト
} ncl_keymap;

// NICOLA on QWERTY
const ncl_keymap nmap[] = {
  [KC_Q]    = {.t = ".",  .l = "la",  .r = ""},
  [KC_W]    = {.t = "ka", .l = "e",   .r = "ga"},
  [KC_E]    = {.t = "ta", .l = "ri",  .r = "da"},
  [KC_R]    = {.t = "ko", .l = "lya", .r = "go"},
  [KC_T]    = {.t = "sa", .l = "re",  .r = "za"},

  [KC_Y]    = {.t = "ra", .l = "pa",  .r = "yo"},
  [KC_U]    = {.t = "ti", .l = "di",  .r = "ni"},
  [KC_I]    = {.t = "ku", .l = "gu",  .r = "ru"},
  [KC_O]    = {.t = "tu", .l = "du",  .r = "ma"},
  [KC_P]    = {.t = ",",  .l = "pi",  .r = "le"},

  [KC_A]    = {.t = "u",  .l = "wo",  .r = "vu"},
  [KC_S]    = {.t = "si", .l = "a",   .r = "zi"},
  [KC_D]    = {.t = "te", .l = "na",  .r = "de"},
  [KC_F]    = {.t = "ke", .l = "lyu", .r = "ge"},
  [KC_G]    = {.t = "se", .l = "mo",  .r = "ze"},

  [KC_H]    = {.t = "ha", .l = "ba",  .r = "mi"},
  [KC_J]    = {.t = "to", .l = "do",  .r = "o"},
  [KC_K]    = {.t = "ki", .l = "gi",  .r = "no"},
  [KC_L]    = {.t = "i",  .l = "po",  .r = "lyo"},
  [KC_SCLN] = {.t = "nn", .l = "",    .r = "ltu"},

  [KC_Z]    = {.t = ".",  .l = "lu",  .r = ""},
  [KC_X]    = {.t = "hi", .l = "-",   .r = "bi"},
  [KC_C]    = {.t = "su", .l = "ro",  .r = "zu"},
  [KC_V]    = {.t = "hu", .l = "ya",  .r = "bu"},
  [KC_B]    = {.t = "he", .l = "li",  .r = "be"},

  [KC_N]    = {.t = "me", .l = "pu",  .r = "nu"},
  [KC_M]    = {.t = "so", .l = "zo",  .r = "yu"},
  [KC_COMM] = {.t = "ne", .l = "pe",  .r = "mu"},
  [KC_DOT]  = {.t = "ho", .l = "bo",  .r = "wa"},
  [KC_SLSH] = {.t = "/",  .l = "?",    .r = "lo"},
};

// シフトキーの状態に応じて文字をPCへ送る
void ncl_type(void) {
  for (int i = 0; i < ncl_chrcount; i++) {
    if (ninputs[i] == 0) break;
    if (ncl_lshift) {
      send_string(nmap[ninputs[i]].l);
    } else if (ncl_rshift) {
      send_string(nmap[ninputs[i]].r);
    } else {
      send_string(nmap[ninputs[i]].t);
    }
  }
  ncl_clear();
}

// バッファをクリアする
void ncl_clear(void) {
  for (int i = 0; i < 5; i++) {
    ninputs[i] = 0;
  }
  ncl_chrcount = 0;
  ncl_keycount = 0;
  ncl_lshift = false;
  ncl_rshift = false;
}


bool process_nicola(uint16_t keycode, keyrecord_t *record, uint8_t ncl_layer, uint16_t lshiftkey, uint16_t rshiftkey, uint16_t modkeys[2]) {

  //static int modkeys_size = sizeof(modkeys) / sizeof(modkeys[0]);

  bool is_modifier = false; // SHIFTキーなどのキーが押されているかどうかを確認する

  switch (keycode) {
    case KC_LCTL:
    case KC_LSFT:
    case KC_LALT:
    case KC_LGUI:
    case KC_RCTL:
    case KC_RSFT:
    case KC_RALT:
    case KC_RGUI:
      is_modifier = true;
      break;
  }

  // modifier処理
  if (is_modifier) {
    if (record->event.pressed) {
      ncl_modcount++;
      ncl_modifier_active = true;
    } else {
      if (ncl_modcount > 0) {
        ncl_modcount--;
      }
    }
    return true;
  }

  // modifierが押されている場合は通常のキー処理
  if (ncl_modcount > 0) {
    if (record->event.pressed) {
      ncl_clear();
    }
    return true;  // Ctrl+C, Alt+Tab等を正常に処理
  }

  // modifierが離された直後はNICOLA処理をスキップ
  if (ncl_modifier_active && ncl_modcount == 0) {
    ncl_modifier_active = false;
    ncl_clear();
    return true;
  }

  if (layer_state_is(ncl_layer) & !is_modifier) {

    if (record->event.pressed) {
      if (keycode == lshiftkey) {
        ncl_lshift = true;
        ncl_keycount++;
        if (ncl_keycount > 1) ncl_type();
        return false;
      } else if (keycode == rshiftkey) {
        ncl_rshift = true;
        ncl_keycount++;
        if (ncl_keycount > 1) ncl_type();
        return false;
      }
      switch (keycode) {
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          ninputs[ncl_chrcount] = keycode;
          ncl_chrcount++;
          ncl_keycount++;
          if (ncl_keycount > 1) ncl_type();
          return false;
          break;
        default: // 親指シフトに関係ないキー
          ncl_clear();
          return true;
          break;
      }

    } else { // key release

      if (keycode == lshiftkey) {
        ncl_lshift = false;
        if (ncl_keycount > 0) {
            if (ncl_keycount == 1 && ncl_chrcount == 0) {
            // シフトキーのみが押されていた場合
            tap_code16(lshiftkey);
            ncl_clear();
            } else {
            // 文字キーと一緒に押されていた場合
            ncl_type();
            }
        }
        return false;
      }

      if (keycode == rshiftkey) {
        ncl_rshift = false;
        if (ncl_keycount > 0) {
            if (ncl_keycount == 1 && ncl_chrcount == 0) {
            // シフトキーのみが押されていた場合
            tap_code16(rshiftkey);
            ncl_clear();
            } else {
            // 文字キーと一緒に押されていた場合
            ncl_type();
            }
        }
        return false;
      }

      switch (keycode) {
        case KC_A ... KC_Z: // 親指シフト処理するキー
        case KC_SLSH:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
          if (ncl_keycount > 0) {
            ncl_type();
          }
          return false;  // 常にfalseを返す
          break;
      }
    }
  }

  return true;
}
