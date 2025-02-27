// Corne Cherry V3

/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2024 @mintommm

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
｀
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  LSFT_SPC,
  RSFT_ENT,
  LGUI_LALT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_L,    KC_U, KC_COMM,  KC_DOT,                         KC_F,    KC_W,    KC_R,    KC_Y,    KC_P,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_E,    KC_I,    KC_A,    KC_O, KC_MINS,                         KC_K,    KC_T,    KC_N,    KC_S,    KC_H, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V, KC_SCLN,                         KC_G,    KC_D,    KC_M,    KC_J,    KC_B, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        LGUI_LALT,   LOWER,LSFT_SPC,   RSFT_ENT,   RAISE, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

    [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   LCTL(KC_W),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_LBRC, KC_RBRC,  KC_EQL, KC_PIPE, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_LPRN, KC_RPRN, KC_PPLS, KC_PMNS, KC_ASTR, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ENT,                        KC_LT,   KC_GT, KC_CIRC, KC_AMPR, KC_UNDS, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LGUI,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PSCR,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_QUES, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SPC,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   KC_P0,   KC_P7,   KC_P8,   KC_P9, KC_PDOT,                      XXXXXXX, XXXXXXX, KC_EQL,  XXXXXXX, XXXXXXX, LGUI(KC_L),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_P0,   KC_P4,   KC_P5,   KC_P6, KC_COMM,                      XXXXXXX, XXXXXXX, KC_PPLS, KC_PMNS, KC_PAST, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_P0,   KC_P1,   KC_P2,   KC_P3, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool space_pressed = false;
static uint16_t space_pressed_time = 0;
static bool enter_pressed = false;
static uint16_t enter_pressed_time = 0;
static bool lguilalt_pressed = false;
static uint16_t lguilalt_pressed_time = 0;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed &&
            TIMER_DIFF_16(record->event.time,
                          lower_pressed_time) < TAPPING_TERM) {
          tap_code(KC_INTERNATIONAL_5);
          tap_code(KC_LANGUAGE_2);
        }
        lower_pressed = false;
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed &&
            TIMER_DIFF_16(record->event.time,
                          raise_pressed_time) < TAPPING_TERM) {
          tap_code(KC_INTERNATIONAL_4);
          tap_code(KC_LANGUAGE_1);

          // chromeOS用、LCTLだと物理キーで使ってるLCTLと競合してここでUnregisterされる可能性があるのでRCTLを使う
          // 副作用としてWindowsで全角スペースが入力される。Macはわからない
          register_code(KC_RSFT);
          register_code(KC_RCTL);
          tap_code(KC_SPC);
          unregister_code(KC_RCTL);
          unregister_code(KC_RSFT);
        }
        raise_pressed = false;
      }
      return false;
      break;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;

    case LSFT_SPC:
      if (record->event.pressed) {
        space_pressed = true;
        space_pressed_time = record->event.time;
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        if (space_pressed &&
            TIMER_DIFF_16(record->event.time,
                          space_pressed_time) < TAPPING_TERM) {
          tap_code(KC_SPC);
        }
        space_pressed = false;
      }
      return false;
      break;

    case RSFT_ENT:
      if (record->event.pressed) {
        enter_pressed = true;
        enter_pressed_time = record->event.time;
        register_code(KC_RSFT);
      } else {
        unregister_code(KC_RSFT);
        if (enter_pressed &&
            TIMER_DIFF_16(record->event.time,
                          enter_pressed_time) < TAPPING_TERM) {
          tap_code(KC_ENT);
        }
        enter_pressed = false;
      }
      return false;
      break;

    case LGUI_LALT:
      if (record->event.pressed) {
        if (lguilalt_pressed &&
            TIMER_DIFF_16(record->event.time, lguilalt_pressed_time) <
                TAPPING_TERM * 2) {
          // 1回目タップ後に押したとき
          // 1回目のタップのフラグがオン &
          // 最初のキー押下から2回目のキー押下までの時間が TAPPING_TERM
          // の2倍未満ならダブルタップ目と判断する
          lguilalt_pressed_time = record->event.time;
          register_code(KC_LGUI);
        } else {
          lguilalt_pressed_time = record->event.time;
          register_code(KC_LALT);
        }
        lguilalt_pressed = false;
      } else {
        if (!lguilalt_pressed &&
            TIMER_DIFF_16(record->event.time, lguilalt_pressed_time) <
                TAPPING_TERM) {
          // 1回目をタップで離したとき
          // 1回目のタップのフラグがオフ &
          // 最初のキー押下からキーを離した時までの時間が TAPPING_TERM
          // 未満ならタップと判断する
          lguilalt_pressed = true;
        }
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
      }
      return false;
      break;

    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
        space_pressed = false;
        enter_pressed = false;
      }
      break;
  }
  return true;
}
