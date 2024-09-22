/* Copyright 2024 Abdullah (@motjuste) <abdullah.motjuste@gmail.com>
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

enum layers {
    _NORMAN = 0,
    _QWERTY,
    _NUMBER,
    _SYMBOL,
    _FUNNAV,
};

// Aliases for readability
#define TNUMNAV TT(_NUMBER)
#define TSYMNAV TT(_SYMBOL)
#define LFUNSPC LT(_FUNNAV, KC_SPC)
#define LFUNBSP LT(_FUNNAV, KC_BSPC)

#define CMD_LBR MT(MOD_RGUI, KC_LBRC)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define ALT_EQL MT(MOD_RALT, KC_EQL)
#define CTL_QUO MT(MOD_RCTL, KC_QUOTE)

#define NORMAN DF(_NORMAN)
#define QWERTY DF(_QWERTY)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_NORMAN] = LAYOUT(
        KC_TAB , KC_Q   , KC_W   , KC_D   , KC_F   , KC_K   ,                                         KC_J   , KC_U   , KC_R   , KC_L   , KC_SCLN, KC_MINS,
        CTL_ESC, KC_A   , KC_S   , KC_E   , KC_T   , KC_G   ,                                         KC_Y   , KC_N   , KC_I   , KC_O   , KC_H   , CTL_QUO,
        SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ENT , KC_RBRC,     KC_BSLS, KC_ESC , KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_SENT,
                                   LFUNBSP, KC_LALT, KC_SPC , KC_LCMD, TNUMNAV,     TSYMNAV, CMD_LBR, KC_BSPC, ALT_EQL, LFUNSPC
    ),

    [_QWERTY] = LAYOUT(
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                         KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                         KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, CTL_QUO,
        SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ENT , KC_RBRC,     KC_BSLS, KC_ESC , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_SENT,
                                   LFUNBSP, KC_LALT, KC_SPC , KC_LCMD, TNUMNAV,     TSYMNAV, CMD_LBR, KC_BSPC, ALT_EQL, LFUNSPC
    ),

    [_NUMBER] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                         KC_VOLU, KC_MPRV, KC_UP  , KC_MNXT, _______, _______,
        _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,                                         KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
        _______, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL , KC_BSLS, _______, _______,     _______, _______, KC_MPLY, KC_MUTE, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                         KC_VOLU, KC_MPRV, KC_UP  , KC_MNXT, KC_COLN, KC_LCBR,
        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                                         KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_DQUO,
        _______, KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, KC_PIPE, _______, KC_RCBR,     KC_PIPE, _______, KC_MPLY, KC_MUTE, KC_LABK, KC_RABK, KC_QUES, _______,
                                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),

    [_FUNNAV] = LAYOUT(
        KC_TILD, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, KC_BRID, KC_BRIU, KC_F11 , KC_F12 , KC_CAPS, NORMAN , QWERTY ,     _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
        //
        // IDEA: make right side mouse keys
        //  but I want it to enable me to jump around on the screen (properly),
        //  not make me, how John Siracusa put it, "drag myself by the teeth"
        //
    ),

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }


bool oled_task_user(void) {

#ifdef MASTER_RIGHT
    const bool is_on_the_right_side = is_keyboard_master();
#else
    const bool is_on_the_right_side = !is_keyboard_master();
#endif

    const uint8_t current_layer = get_highest_layer(layer_state|default_layer_state);

    oled_set_cursor(14, 0);
    oled_write_P(current_layer == _QWERTY  ? PSTR("QWERTY ") : PSTR("       "), false);

    const uint8_t start = is_on_the_right_side ? 0 : 11;
    bool invert = (current_layer == _FUNNAV)
               || (current_layer == _SYMBOL &&  is_on_the_right_side)
               || (current_layer == _NUMBER && !is_on_the_right_side);

    oled_set_cursor(start, 2);
    oled_write_P(PSTR("         "), invert);

    oled_set_cursor(start, 3);
    switch (current_layer) {
        case _SYMBOL:
            oled_write_P(PSTR("   SYM   "), invert);
            break;
        case _NUMBER:
            oled_write_P(PSTR("   NUM   "), invert);
            break;
        case _FUNNAV:
            oled_write_P(PSTR("   FUN   "), invert);
            break;
        case _NORMAN:
        case _QWERTY:
            oled_write_P(is_on_the_right_side ? PSTR("   SYM   ") : PSTR("   NUM   "), invert);
            break;
        default:
            oled_write_P(PSTR("   ERR   "), !invert);
            break;
    }

    oled_set_cursor(start, 4);
    oled_write_P(PSTR("         "), invert);

    oled_set_cursor(0, 7);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);

    return false;
}
#endif
