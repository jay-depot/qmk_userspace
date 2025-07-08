#include QMK_KEYBOARD_H
#include "layers.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case LAYER_NAVIGATION:
            rgblight_sethsv (0,  0, 10);
            break;
        case LAYER_NUMERAL:
            rgblight_sethsv (240, 255, 64);
            break;
        case LAYER_SYMBOLS  :
            rgblight_sethsv (240, 255, 127);
            break;
            // LAYER_POINTER,
            // LAYER_FUNCTION,
            // LAYER_GAME,
            // LAYER_OSL

        default: //  LAYER_BASE
            rgblight_sethsv (0,  0, 10);
            break;
    }

    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_sethsv (0,  0, 10);

    return state;
}

#ifdef RGB_MATRIX_ENABLE
// Layer state indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (int i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, MIN(rgb_matrix_get_val() + 76, 255), 0x00, 0x00);
            }
        }
    }

    uint8_t layer = get_highest_layer(layer_state);
    if (layer > 0) {
        hsv_t hsv = rgb_matrix_get_hsv();
        switch (get_highest_layer(layer_state)) {
            case 1:
                hsv = (hsv_t){HSV_BLUE};
                break;
            case 2:
                hsv = (hsv_t){HSV_AZURE};
                break;
            case 3:
                hsv = (hsv_t){HSV_ORANGE};
                break;
            case 4:
                hsv = (hsv_t){HSV_GREEN};
                break;
            case 5:
                hsv = (hsv_t){HSV_TEAL};
                break;
            case 6:
                hsv = (hsv_t){HSV_PURPLE};
                break;
            case 7:
            default:
                hsv = (hsv_t){HSV_RED};
                break;
        };

        if (hsv.v > rgb_matrix_get_val()) {
            hsv.v = MIN(rgb_matrix_get_val() + 22, 255);
        }
        rgb_t rgb = hsv_to_rgb(hsv);

        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }

    return false;
};
#endif // RGB_MATRIX_ENABLE
