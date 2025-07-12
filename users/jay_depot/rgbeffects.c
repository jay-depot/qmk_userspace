#include QMK_KEYBOARD_H
#include "layers.h"
#include "colors.h"

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_sethsv (HSV_COLOR_DEFAULT);

    return state;
}

#ifdef RGB_MATRIX_ENABLE
// Layer state indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // if (host_keyboard_led_state().caps_lock) {
    //     for (int i = led_min; i <= led_max; i++) {
    //         if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
    //             rgb_matrix_set_color(i, MIN(rgb_matrix_get_val() + 76, 255), 0x00, 0x00);
    //         }
    //     }
    // }

    uint8_t layer = get_highest_layer(layer_state);

    hsv_t hsv = (hsv_t){HSV_BLACK};
    switch (get_highest_layer(layer_state)) {
        case LAYER_GAMING:
            return true;
            // hsv = (hsv_t){HSV_COLOR_GAME};
            // break;
        case LAYER_NAVIGATION:
            hsv = (hsv_t){HSV_COLOR_NAVIGATION};
            break;
        case LAYER_NUMERAL:
            hsv = (hsv_t){HSV_COLOR_NUMERAL};
            break;
        case LAYER_SYMBOLS:
            hsv = (hsv_t){HSV_COLOR_SYMBOLS};
            break;
        case LAYER_POINTER:
            hsv = (hsv_t){HSV_COLOR_POINTER};
            break;
        case LAYER_FUNCTION:
            hsv = (hsv_t){HSV_COLOR_FUNCTION};
            break;
        case LAYER_OSL:
            hsv = (hsv_t){HSV_COLOR_OSL};
            break;
        default:
            hsv = (hsv_t){HSV_COLOR_DEFAULT};
            break;
    };

    // if (hsv.v > rgb_matrix_get_val()) {
    //     hsv.v = MIN(rgb_matrix_get_val() + 22, 255);
    // }

    rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    rgb_t defaultColor = hsv_to_rgb((hsv_t){HSV_COLOR_DEFAULT});
    rgb_t offColor = hsv_to_rgb((hsv_t){HSV_COLOR_DISABLED});

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});

            if (index >= led_min && index < led_max && index != NO_LED) {
                if (keycode > KC_TRNS) {
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                } else if (keycode == KC_TRNS) {
                    rgb_matrix_set_color(index, defaultColor.r, defaultColor.g, defaultColor.b);
                } else {
                    rgb_matrix_set_color(index, offColor.r, offColor.g, offColor.b);
                }
            }
        }
    }

    return false;
};
#endif // RGB_MATRIX_ENABLE
