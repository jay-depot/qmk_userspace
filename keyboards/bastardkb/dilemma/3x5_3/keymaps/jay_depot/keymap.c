/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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
#include "layers.h"

// Mod Key defns:
#define OS_LALT OSM(MOD_LALT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RSFT OSM(MOD_RSFT)

#define SPC_NUM LT(LAYER_NUMERAL , KC_SPC)
#define ENT_OSL LT(LAYER_OSL, KC_ENT)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)
#define SHFT_NAV LT(LAYER_NUMERAL, KC_NO)

#define TO_BASE  TO(LAYER_BASE)
#define OS_OSL   OSL(LAYER_OSL)
#define TO_NAV   TO(LAYER_NAVIGATION)
#define TO_NUM   TO(LAYER_NUMERAL)
#define TO_SYM   TO(LAYER_SYMBOLS)
#define TO_POINT TO(LAYER_POINTER)
#define TO_FN    TO(LAYER_FUNCTION)
#define TO_GAME  TO(LAYER_GAME)
// #define TO_MED   TO(LAYER_MEDIA)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_BSPC,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                      OS_LGUI, OS_LCTL, OS_LSFT,        SPC_NUM, TAB_SYM, ENT_OSL
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 */
  /**
   * \brief Navigation layer.
   *
   * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
   * keys are vim, line and page movement below arranged similarly.
   */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSPC,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
                      OS_LGUI, OS_LCTL, OS_LSFT,        SPC_NUM, TAB_SYM, ENT_OSL
  ),

  /**
   * \brief Numeral layout.
   *
   * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
   * are in the standard numpad locations with symbols in the remaining positions.
   * `KC_DOT` is duplicated from the base layer.
   */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
    XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX,         KC_BSLS, KC_ASTR, KC_SLSH, KC_LPRN, KC_LBRC,
    XXXXXXX,    KC_4,    KC_5,    KC_6,    KC_0,         XXXXXXX, KC_PLUS, KC_MINS,  KC_EQL, KC_SCLN,
    XXXXXXX,    KC_1,    KC_2,    KC_3,  KC_DOT,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR,
                      OS_LGUI, OS_LCTL, OS_LSFT,        SPC_NUM, TAB_SYM, ENT_OSL
  ),

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,          KC_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,           KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,          KC_LPRN, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                      OS_LGUI, OS_LCTL, OS_LSFT,         SPC_NUM, TAB_SYM, ENT_OSL
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD,         S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
    XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1,         KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX,
    XXXXXXX, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______,
                      OS_LGUI, OS_LCTL, OS_LSFT,         TO_BASE, TAB_SYM, ENT_OSL
  ),

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
                      OS_LGUI, OS_LCTL, OS_LSFT,        SPC_NUM, TAB_SYM, ENT_OSL
  ),

/**
 * \brief Game layer.
 *
 * QWERTY layout shifted one column to the right for comfortable WASD positioning.
 * default one-shot mods and space on thumbs.
 */

  [LAYER_GAME] = LAYOUT_split_3x5_3(
        KC_ESC, KC_Q,    KC_W,    KC_E,    KC_R,            KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,
        KC_TAB, KC_A,    KC_S,    KC_D,    KC_F,            KC_G,    KC_H,    KC_J,    KC_K,    KC_L,
       XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,            KC_B,    KC_N,    KC_M, KC_COMM,    KC_DOT,
                      OS_LGUI, OS_LCTL, OS_LSFT,        SPC_NUM, TAB_SYM, ENT_OSL
  ),

/**
 * \brief One-Shot layer.
 *
 * The layer to get to other layers, mostly.
 */
  [LAYER_OSL] = LAYOUT_split_3x5_3(
     KC_ESC, XXXXXXX,  XXXXXXX, TO_POINT, XXXXXXX,        KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS,
      TO_FN,  TO_SYM,   TO_NUM,  TO_BASE, TO_GAME,        KC_SCRL, OS_RSFT, OS_RALT, OS_RCTL,  KC_DEL,
    KC_QUOT, XXXXXXX,  XXXXXXX,   TO_NAV, OS_LALT,        KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT,
                       OS_LALT, OS_LCTL,  OS_LSFT,       SPC_NUM, TAB_SYM, ENT_OSL
  ),
};
