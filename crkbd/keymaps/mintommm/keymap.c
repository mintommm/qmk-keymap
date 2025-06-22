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
  LGUI_LALT,
  LPRN_LABK,
  RPRN_RABK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_L,    KC_U, KC_COMM, KC_QUOT,                         KC_F,    KC_W,    KC_R,    KC_Y,    KC_P,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_E,    KC_I,    KC_A,    KC_O, KC_MINS,                         KC_K,    KC_T,    KC_N,    KC_S,    KC_H, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V, KC_SCLN,                         KC_G,    KC_D,    KC_M,    KC_J,    KC_B,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        LGUI_LALT,   LOWER,LSFT_SPC,   RSFT_ENT,   RAISE, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

    [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   LCTL(KC_W),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ENT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                   LPRN_LABK,RPRN_RABK, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_SPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_ENT,                       KC_SPC, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
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
          tap_code(KC_INTERNATIONAL_5); // 「無変換」キー
          tap_code(KC_LANGUAGE_2); // 「かな」キー
        }
        lower_pressed = false;
      }
      return false;

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
          tap_code(KC_INTERNATIONAL_4); // 「変換」キー
          tap_code(KC_LANGUAGE_1); // 「英数」キー

          // chromeOS用、LCTLだと物理キーで使ってるLCTLと競合してここでUnregisterされる可能性があるのでRCTLを使う
          // 副作用としてWindowsで半角スペースが入力される。Macはわからない
          register_code(KC_RSFT);
          register_code(KC_RCTL);
          tap_code(KC_SPC);
          unregister_code(KC_RCTL);
          unregister_code(KC_RSFT);
        }
        raise_pressed = false;
      }
      return false;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;

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

    case LPRN_LABK:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          tap_code16(KC_LABK);
        } else {
          tap_code16(KC_LPRN);
        }
      }
      return false;

    case RPRN_RABK:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          tap_code16(KC_RABK);
        } else {
          tap_code16(KC_RPRN);
        }
      }
      return false;

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
};

const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_DOT);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&comma_key_override
};
