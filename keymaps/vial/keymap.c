#include QMK_KEYBOARD_H
#include "quantum.h"
#include "gpio.h"


static inline uint8_t scale(uint8_t c) {
	return (uint16_t)c * rgb_matrix_config.hsv.v / 255;

}


RGB current_rgb = {36, 0, 255};
RGB current_rgb2 = {36, 0, 255};

#define SW1_PIN GP26
#define SW2_PIN GP27
#define SWAP_FN_PIN GP28
#define SWAP_FN2_PIN GP29

#define EECONFIG_COLOR_LO (uint32_t *)0x20
#define EECONFIG_COLOR_RA (uint32_t *)0x28

#define ROTARY_ROW 4
#define ROTARY_COL 4


static inline void eeconfig_update_kb_at(uint32_t *addr, uint32_t val) {
    eeprom_update_dword(addr,val);
}
static inline uint32_t eeconfig_read_kb_at(uint32_t *addr) {
 return eeprom_read_dword(addr);
}


void keyboard_pre_init_user(void) {
	/* setPinInputHigh(SW1_PIN); */
	/* setPinInputHigh(SW2_PIN); */
	/* setPinInputHigh(SW3_PIN); */
	setPinInputLow(SW1_PIN);
	setPinInputLow(SW2_PIN);
	setPinInputLow(SWAP_FN_PIN);
	setPinInputLow(SWAP_FN2_PIN);


}


enum layer_number {
    _default = 0,
    _lo,
    _ra,
    _up,
    _df,
    _lom,
    _ram,
    _upm
    /* _lower_d, */
    /* _raise_d, */
    /* _upper_d, */
    /* _df_d, */
    /* _lower_r, */
    /* _raise_r, */
    /* _upper_r, */
    /* _df_r */
};


enum custom_keycodes {

	LED_PINK_lo = QK_KB_0,
	LED_GREEN_lo,
	LED_BLUE_lo,
	LED_WHITE_lo,
	LED_PURPLE_lo,
	LED_RED_lo,
	LED_YELLOW_lo,
	LED_ORANGE_lo,
	LED_CYAN_lo,
	LED_MAGENTA_lo,
	LED_GRAY_lo,
	LED_PINK_ra,
	LED_GREEN_ra,
	LED_BLUE_ra,
	LED_WHITE_ra,
	LED_PURPLE_ra,
	LED_RED_ra,
	LED_YELLOW_ra,
	LED_ORANGE_ra,
	LED_CYAN_ra,
	LED_MAGENTA_ra,
	LED_GRAY_ra

};

#define KC_PINK LED_PINK_lo
#define KC_GREE LED_GREEN_lo
#define KC_BLUE LED_BLUE_lo
#define KC_WHIT LED_WHITE_lo
#define KC_PURP LED_PURPLE_lo
#define KC_RED  LED_RED_lo
#define KC_YELL LED_YELLOW_lo
#define KC_ORAN LED_ORANGE_lo
#define KC_CYAN LED_CYAN_lo
#define KC_MAGE LED_MAGENTA_lo
#define KC_GRAY LED_GRAY_lo
#define KC_PINK2 LED_PINK_ra
#define KC_GREE2 LED_GREEN_ra
#define KC_BLUE2 LED_BLUE_ra
#define KC_WHIT2 LED_WHITE_ra
#define KC_PURP2 LED_PURPLE_ra
#define KC_RED2  LED_RED_ra
#define KC_YELL2 LED_YELLOW_ra
#define KC_ORAN2 LED_ORANGE_ra
#define KC_CYAN2 LED_CYAN_ra
#define KC_MAGE2 LED_MAGENTA_ra
#define KC_GRAY2 LED_GRAY_ra


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
      * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
      * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
      * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
      * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
      */
 [_default] = LAYOUT(

         KC_SPC,
         KC_Y,          KC_U,      KC_I,          KC_O,     KC_P,       KC_BSPC,
         KC_H,          KC_J,      KC_K,          KC_L,     KC_SCLN,    KC_QUOT,
         KC_N,          KC_M,      KC_COMM,       KC_DOT,   KC_SLSH,    KC_RSFT,
         LT(2,KC_SPC),  LGUI_T(KC_TAB),   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),

     [_lo] = LAYOUT(

         KC_SPC,
         KC_6,          KC_7,      KC_8,         KC_9,           KC_0,            KC_BSPC,
         KC_LEFT,       KC_RGHT,   KC_DOWN,      KC_UP,          KC_SCLN,         KC_DEL,
         KC_NUBS,       KC_GRV,    KC_QUOT,      LSFT(KC_LBRC),  LSFT(KC_RBRC),   KC_MINS,
         LT(2,KC_SPC),  LGUI_T(KC_TAB),   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),
     [_ra] = LAYOUT(

         KC_SPC,
         KC_F6,         KC_F7,     KC_F8,         KC_F9,    KC_F10,     KC_F11,
         KC_EQL,        KC_MINS,   KC_PAST,       KC_SLSH,  KC_BSPC,    KC_F12,
         KC_N,          KC_M,      KC_COMM,       KC_LBRC,  KC_RBRC,    KC_MINS,
         LT(2,KC_SPC),  LGUI_T(KC_TAB),   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),
     [_up] = LAYOUT(

         KC_SPC,
         KC_Y,          KC_U,      KC_I,          KC_O,     KC_P,       KC_BSPC,
         KC_H,          KC_J,      KC_K,          KC_L,     KC_SCLN,    KC_QUOT,
         KC_N,          KC_M,      KC_COMM,       KC_DOT,   KC_SLSH,    KC_RSFT,
         LT(2,KC_SPC),  KC_LGUI,   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),

     [_df] = LAYOUT(

         KC_SPC,
         KC_Y,          KC_U,      KC_I,          KC_O,     KC_P,       KC_BSPC,
         KC_H,          KC_J,      KC_K,          KC_L,     KC_SCLN,    KC_QUOT,
         KC_N,          KC_M,      KC_COMM,       KC_DOT,   KC_SLSH,    KC_RSFT,
         LT(2,KC_SPC),  KC_LGUI,   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),

     [_lom] = LAYOUT(

         KC_SPC,
         KC_Y,          KC_U,      KC_I,          KC_O,     KC_P,       KC_BSPC,
         KC_H,          KC_J,      KC_K,          KC_L,     KC_SCLN,    KC_QUOT,
         KC_N,          KC_M,      KC_COMM,       KC_DOT,   KC_SLSH,    KC_RSFT,
         LT(2,KC_SPC),  KC_LGUI,   LT(1,KC_ENT),  KC_NO,    KC_NO

   ),

     [_ram] = LAYOUT(

         KC_SPC,
         KC_Y,          KC_U,      KC_I,          KC_O,     KC_P,       KC_BSPC,
         KC_H,          KC_J,      KC_K,          KC_L,     KC_SCLN,    KC_QUOT,
         KC_N,          KC_M,      KC_COMM,       KC_DOT,   KC_SLSH,    KC_RSFT,
         LT(2,KC_SPC),  KC_LGUI,   LT(1,KC_ENT),  KC_NO,    KC_NO

        ),

     [_upm] = LAYOUT(
         KC_SPC,
         KC_PINK,     KC_GREE,      KC_BLUE,     KC_WHIT,     KC_PURP,     KC_RED,
         KC_YELL,     KC_ORAN,      KC_CYAN,     KC_MAGE,     KC_GRAY,     KC_NO,
         KC_PINK2,    KC_GREE2,     KC_BLUE2,    KC_WHIT2,    KC_PURP2,    KC_RED2,
         KC_YELL2,    KC_ORAN2,     KC_CYAN2,    KC_MAGE2,    KC_GRAY2

    )


};


#if defined(ENCODER_MAP_ENABLE)

 const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
     [0] = {ENCODER_CCW_CW(KC_BSPC, KC_DEL),             ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
     [1] = {ENCODER_CCW_CW(LSFT(KC_TAB), KC_TAB),       ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
     [2] = {ENCODER_CCW_CW(KC_MS_L, KC_MS_R),           ENCODER_CCW_CW(KC_MS_UP, KC_MS_DOWN)},
     [3] = {ENCODER_CCW_CW(KC_KP_MINUS, KC_KP_PLUS),    ENCODER_CCW_CW(KC_KP_SLASH, KC_KP_ASTERISK)},
     [4] = {ENCODER_CCW_CW(KC_WH_L, KC_WH_R),           ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
     [5] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
     [6] = {ENCODER_CCW_CW(C(KC_LEFT), C(KC_RIGHT)),    ENCODER_CCW_CW(RCS(KC_TAB), C(KC_TAB))},
     [7] = {ENCODER_CCW_CW(KC_WH_L, KC_WH_R),           ENCODER_CCW_CW(KC_WH_U, KC_WH_D)}

 };

#endif



/* 8layers */
uint8_t get_layer_state(void) {
    uint8_t sw1 = gpio_read_pin(SW1_PIN) ? 0 : 1;
    uint8_t sw2 = gpio_read_pin(SW2_PIN) ? 0 : 1;
    uint8_t sw3= gpio_read_pin(SWAP_FN_PIN) ? 0 : 1;
    uint8_t sw4 = gpio_read_pin(SWAP_FN2_PIN) ? 0 : 1;

    bool rotary_pressed = matrix_is_on(ROTARY_ROW,ROTARY_COL);

if(sw1 && sw2 && sw3 && sw4 && rotary_pressed) return 7;
        else if(!sw1 && !sw2) return 0;
        else if (sw1 && !sw2) return 3;
        else if (sw1 && sw2) return 4;
        else if (!sw1 && sw2) return 3;
        else return 0;











}




void matrix_scan_user(void) {
static uint8_t current_layer = 255;// 初回は不正な値
    uint8_t new_layer = get_layer_state();

    // レイヤーが変わった場合のみ処理を実行
    if (new_layer != current_layer) {
        current_layer = new_layer;
        layer_move(new_layer); // レイヤーを切り替える
    }


}










bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (record->event.pressed) {
         switch (keycode) {
             case LED_PINK_lo:
                 current_rgb = (RGB){255, 128, 192};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);


                 return false;

            case LED_GREEN_lo:
                 current_rgb = (RGB){0, 255, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_BLUE_lo:
                 current_rgb = (RGB){0, 0, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_WHITE_lo:
                 current_rgb = (RGB){255, 255, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_PURPLE_lo:
                 current_rgb = (RGB){128, 0, 128};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_RED_lo:
                 current_rgb = (RGB){255, 0, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_YELLOW_lo:
                 current_rgb = (RGB){255, 255, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_ORANGE_lo:
                 current_rgb = (RGB){255, 128, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_CYAN_lo:
                 current_rgb = (RGB){0, 255, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_MAGENTA_lo:
                 current_rgb = (RGB){255, 0, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_GRAY_lo:
                 current_rgb = (RGB){128, 128, 128};

                 eeconfig_update_kb_at(EECONFIG_COLOR_LO,(current_rgb.r << 16) | (current_rgb.g << 8) | current_rgb.b);

                 return false;

             case LED_PINK_ra:
                 current_rgb2 = (RGB){255, 128, 192};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);


                 return false;

            case LED_GREEN_ra:
                 current_rgb2 = (RGB){0, 255, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_BLUE_ra:
                 current_rgb2 = (RGB){0, 0, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_WHITE_ra:
                 current_rgb2 = (RGB){255, 255, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_PURPLE_ra:
                 current_rgb2 = (RGB){128, 0, 128};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_RED_ra:
                 current_rgb2 = (RGB){255, 0, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_YELLOW_ra:
                 current_rgb2 = (RGB){255, 255, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_ORANGE_ra:
                 current_rgb2 = (RGB){255, 128, 0};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_CYAN_ra:
                 current_rgb2 = (RGB){0, 255, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_MAGENTA_ra:
                 current_rgb2 = (RGB){255, 0, 255};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;

             case LED_GRAY_ra:
                 current_rgb2 = (RGB){128, 128, 128};

                 eeconfig_update_kb_at(EECONFIG_COLOR_RA,(current_rgb2.r << 16) | (current_rgb2.g << 8) | current_rgb2.b);

                 return false;


         }


	bool swap_fn_on = !readPin(SWAP_FN_PIN);
	bool swap_fn2_on = !readPin(SWAP_FN2_PIN);


uint16_t get_tapping_keycode_comp(uint16_t keycode) {
    if (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX) {
        return keycode & 0xFF;
    }
    return keycode;
}








if (!swap_fn2_on && swap_fn_on) {
    if(record->event.pressed) {
        uint16_t basecode = get_tapping_keycode_comp(keycode);
        switch (basecode) {
            case KC_ENTER:
            tap_code(KC_SPC);
            return false;

            case KC_SPC:
            tap_code(KC_ENTER);
            return false;
        }

    }
    return true;
}



else if (!swap_fn_on && swap_fn2_on) {
    switch (keycode) {
        case KC_Y: tap_code(KC_6); return false;
        case KC_U: tap_code(KC_7); return false;
        case KC_I: tap_code(KC_8); return false;
        case KC_O: tap_code(KC_9); return false;
        case KC_P: tap_code(KC_0); return false;


    }
}


else if (swap_fn_on && swap_fn2_on) {
switch (keycode) {
        case KC_Y: tap_code(KC_6); return false;
        case KC_U: tap_code(KC_7); return false;
        case KC_I: tap_code(KC_8); return false;
        case KC_O: tap_code(KC_9); return false;
        case KC_P: tap_code(KC_0); return false;
        case KC_BSPC: tap_code(KC_DEL); return false;



    }
}


     }
     return true;
 }


 bool rgb_matrix_indicators_user(void) {
    bool swap_fn_on  = !readPin(SWAP_FN_PIN);
    bool swap_fn2_on = !readPin(SWAP_FN2_PIN);

    const float BRIGHT = 0.1f;
    const float BRIGHT1 = 0.05f;



    // 両方ON
    if (swap_fn_on && swap_fn2_on) {
        rgb_matrix_set_color(2, 0, 255 * BRIGHT1, 0 );     // LED2 緑
        rgb_matrix_set_color(3, 0, 0, 255 * BRIGHT);     // LED3 青

         for (int i = 4; i <= 6; i++) {
            rgb_matrix_set_color(i, 0, 255 * BRIGHT1, 0);
         }

         for (int i = 7; i <= 9; i++) {
            rgb_matrix_set_color(i, 0, 0, 255 * BRIGHT);
         }


        for (int i = 17; i <= 19; i++) {
            rgb_matrix_set_color(13, 0, 255 * BRIGHT1, 0);
            rgb_matrix_set_color(i, 0, 255 * BRIGHT1, 0);
            rgb_matrix_set_color(29, 0, 255 * BRIGHT1, 0);
            rgb_matrix_set_color(30, 0, 255 * BRIGHT, 0);
       }


    }
    // swap_fn のみ ON
    else if (swap_fn2_on) {
        rgb_matrix_set_color(2, 0, 255 * BRIGHT, 0);     // LED2 緑
        rgb_matrix_set_color(3, 0, 0, 0);       // LED3 OFF

         for (int i = 4; i <= 9; i++) {
            rgb_matrix_set_color(i, 0, 255 * BRIGHT1, 0);
         }
    }
    // swap_fn2 のみ ON
    else if (swap_fn_on) {
        rgb_matrix_set_color(2, 0, 0, 0);       // LED2 OFF
        rgb_matrix_set_color(3, 0, 0, 255 * BRIGHT);     // LED3 青

         for (int i = 4; i <= 9; i++) {
            rgb_matrix_set_color(i, 0, 0, 255 * BRIGHT);
         }
    }
    // 両方OFF
    else {
        rgb_matrix_set_color(2, 0, 0, 0);       // 両方OFF
        rgb_matrix_set_color(3, 0, 0, 0);
    }


	/* return true; */

     switch (get_highest_layer(layer_state)) {


        case _lo:
             for (int i = 0; i <= 1; i++) {

                     rgb_matrix_set_color(0, 255 * BRIGHT1, 128 * BRIGHT1, 192 * BRIGHT1 );     // LED2 緑
                     rgb_matrix_set_color(1, 255 * BRIGHT1, 128 * BRIGHT1, 192 * BRIGHT1 );     // LED2 緑
                     /* rgb_matrix_set_color(10,RGB_BLACK); */
                     /* rgb_matrix_set_color(1,RGB_BLACK); */

                     /* rgb_matrix_set_color(0,RGB_GREEN); */
                     /* rgb_matrix_set_color(1,RGB_GREEN); */


             }

             /* rgb_matrix_set_color_all(RGB_GREEN); */
             break;

        case _ra:
             for (int i = 0; i <= 1; i++) {

                     rgb_matrix_set_color(1, 0, 0, 255 * BRIGHT);     // LED3 青
                     rgb_matrix_set_color(1, 0, 0, 255 * BRIGHT);     // LED3 青
                     /* rgb_matrix_set_color(i,RGB_BLUE); */
	             /* rgb_matrix_set_color(10,RGB_BLACK); */

                     /* rgb_matrix_set_color(0,RGB_PURPLE); */
                     /* rgb_matrix_set_color(1,RGB_PURPLE); */


             }

             /* rgb_matrix_set_color_all(RGB_BLUE); */
             break;

        case _up:
             /* for (int i = 0; i <= 1; i++) { */

                     rgb_matrix_set_color(0,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));
                     rgb_matrix_set_color(1,scale(current_rgb.g), scale(current_rgb.r), scale(current_rgb.b));


                    /* rgb_matrix_set_color(i,RGB_BLUE); */
                     /* rgb_matrix_set_color(10,scale(current_rgb.r), scale(current_rgb.g), scale(current_rgb.b)); */
                     /* rgb_matrix_set_color(11,scale(current_rgb.r), scale(current_rgb.g), scale(current_rgb.b)); */
                     /* rgb_matrix_set_color(i,scale(current_rgb.r), scale(current_rgb.g), scale(current_rgb.b)); */


             /* } */

             /* rgb_matrix_set_color_all(RGB_YELLOW); */

            break;

        case _df:
             /* for (int i = 0; i <= 1; i++) { */
		     /* rgb_matrix_set_color(10,RGB_PURPLE); */

                     rgb_matrix_set_color(0,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));
                     rgb_matrix_set_color(1,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b));


                     /* rgb_matrix_set_color(i,RGB_PURPLE); */
             /* } */

             /* rgb_matrix_set_color_all(RGB_PURPLE); */
             break;


        case _lom:

             /* for (int i = 10; i <= 12; i++) { */
             /*         rgb_matrix_set_color(i,RGB_ORANGE); */
             /* } */
                     rgb_matrix_set_color(0,RGB_YELLOW);
                     rgb_matrix_set_color(1,RGB_YELLOW);


                     /* rgb_matrix_set_color(10,RGB_BLACK); */
                     /* rgb_matrix_set_color(11,RGB_BLACK); */
                     /* rgb_matrix_set_color(12,RGB_AZURE); */


             /* rgb_matrix_set_color_all(RGB_ORANGE); */

	     /* rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON); */
             break;


        case _ram:
             /* for (int i = 10; i <= 12; i++) { */
             /*         rgb_matrix_set_color(i,RGB_SPRINGGREEN); */
             /* } */
                     rgb_matrix_set_color(0,RGB_RED);
                     rgb_matrix_set_color(1,RGB_RED);


                     /* rgb_matrix_set_color(10,RGB_BLACK); */
                     /* rgb_matrix_set_color(11,RGB_AZURE); */
                     /* rgb_matrix_set_color(12,RGB_AZURE); */


             /* rgb_matrix_set_color_all(RGB_SPRINGAZURE); */
             break;

        case _upm:
              /* for (int i = 0; i <= 1; i++) { */
                     rgb_matrix_set_color(0,RGB_WHITE);
                     rgb_matrix_set_color(1,RGB_WHITE);

                    /* rgb_matrix_set_color(0,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b)); */
                     /* rgb_matrix_set_color(1,scale(current_rgb2.g), scale(current_rgb2.r), scale(current_rgb2.b)); */

             /* } */

            /* for (int i = 10; i <= 12; i++) { */
             /*         rgb_matrix_set_color(i,RGB_CORAL); */
             /* } */
/* rgb_matrix_set_color(10,RGB_AZURE); */
                     /* rgb_matrix_set_color(11,RGB_AZURE); */
                     /* rgb_matrix_set_color(12,RGB_AZURE); */


             /* rgb_matrix_set_color_all(RGB_CORAL); */
             break;


     }
	     /* rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING); */
     return false;



     /* rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON); */


 }


void keyboard_post_init_user(void) {
	/* if(!eeconfig_is_enabled()) { */
	/* 	eeconfig_init(); */
	/* } */
	uint32_t packed_lo = eeconfig_read_kb_at(EECONFIG_COLOR_LO);
	current_rgb.r = (packed_lo >> 16) & 0xFF;
	current_rgb.g = (packed_lo >> 8) & 0xFF;
	current_rgb.b = packed_lo & 0xFF;

    uint32_t packed_ra = eeconfig_read_kb_at(EECONFIG_COLOR_RA);
	current_rgb2.r = (packed_ra >> 16) & 0xFF;
	current_rgb2.g = (packed_ra >> 8) & 0xFF;
	current_rgb2.b = packed_ra & 0xFF;

    eeconfig_update_kb_at(EECONFIG_COLOR_LO, packed_lo);
    eeconfig_update_kb_at(EECONFIG_COLOR_RA, packed_ra);




	setPinInput(SWAP_FN_PIN);
	setPinInput(SWAP_FN2_PIN);

}










