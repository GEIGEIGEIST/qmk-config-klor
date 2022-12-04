/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        ┌─┐┌─╴╷┌──┬─
                                        │ ┐├─╴│└─┐│
                                        └─┘└─╴╵╶─┘╵
*/
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klor.h"
#ifdef HAPTIC_ENABLE
#include "drivers/haptic/DRV2605L.h"
#endif //HAPTIC ENABLE
#ifdef OLED_ENABLE
#include "lib/klorimation.c"
#endif //OLED ENABLE


#if __has_include("secrets.h") 
# include "secrets.h"
#else
char mymail[] = NULL;
char pbase[] = NULL;
#endif


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                  │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                       │
// └─────────────────────────────────────────────────┘ 

enum klor_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _COLEMAK,
    _QWERTY,
    _MOUSE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                   │
// └─────────────────────────────────────────────────┘

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    LOWER,
    RAISE,
    ADJUST,
    OS_SWAP,
    WMAIL,
    PBASE,
    GIPHY,
    MAKE_H,
    SNAP1,
    SNAP2,
    SCROLL
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s               │
// └─────────────────────────────────────────────────┘

// LEFT HAND HOME ROW MODS ├───────────────────────────────────┐

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_R MT(MOD_LALT, KC_R)
#define CTL_S MT(MOD_LCTL, KC_S)
#define SHT_T MT(MOD_LSFT, KC_T)

// RIGHT HAND HOME ROW MODS ├───────────────────────────────────┐

#define SHT_N MT(MOD_RSFT, KC_N)
#define CTL_E MT(MOD_LCTL, KC_E)
#define ALT_I MT(MOD_LALT, KC_I)
#define GUI_O MT(MOD_LGUI, KC_O)

#define LOWER LT(_LOWER, KC_TAB)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   c o m b o s                       │
// └─────────────────────────────────────────────────┘

const uint16_t PROGMEM esc_combo[] = {KC_TAB, KC_Q, COMBO_END};
//const uint16_t PROGMEM save_combo[] = {KC_D, KC_S, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(esc_combo, KC_ESC)
    //COMBO(save_combo, C(KC_S))
};


// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y   o v e r r i d e s         │
// └─────────────────────────────────────────────────┘

const key_override_t sve_key_override = ko_make_basic(MOD_MASK_GUI, KC_S, C(KC_S));

// This globally defines all key overrides to be used ├───────────┐
const key_override_t **key_overrides = (const key_override_t *[]){
  &sve_key_override,
  NULL // Null terminate the array of overrides!
};


// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   s o u n d s                       │
// └─────────────────────────────────────────────────┘

#ifdef AUDIO_ENABLE
  #define WINXP_SOUND W__NOTE(_DS6), Q__NOTE(_DS5), H__NOTE(_AS5), H__NOTE(_GS5), H__NOTE(_DS5), H__NOTE(_DS6), H__NOTE(_AS5)
  #define MAC_SOUND S__NOTE(_CS5), B__NOTE(_C5)
 
  float winxp_song[][2] = SONG(WINXP_SOUND);
  float mac_song[][2] = SONG(MAC_SOUND);
#endif // AUDIO_ENABLE

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
   ┌─────────────────────────────────────────────────┐
   │ c o l e m a k                                   │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │    Q    │    W    │    F    │    P    │    G    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    J    │    L    │    U    │    Y    │    ;    │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │    A    │    R    │    S    │    T    │    D    ├─╯                ╰─┤    H    │    N    │    E    │    I    │    O    │    
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │    Z    │    X    │    C    │    V    │    B    ││ SHIFT  ││PLY/PSE ││    K    │    M    │    ,    │    .    │    /    │ 
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │  CTRL   │  LOWER  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  RAISE  │  BSPCE  │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */ 

   [_COLEMAK] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,                          KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  
    GUI_A,    ALT_R,    CTL_S,    SHT_T,    KC_D,                          KC_H,     SHT_N,    CTL_E,    ALT_I,    GUI_O,    
    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LSFT,   KC_MPLY,  KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
                        KC_DEL,   LOWER,    KC_SPC,   KC_ESC,    KC_LGUI,  KC_ENT,   RAISE,    KC_BSPC
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ q w e r t y                                     │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │    Q    │    W    │    E    │    R    │    T    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    Y    │    U    │    I    │    O    │    P    │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │    A    │    S    │    D    │    F    │    G    ├─╯                ╰─┤    H    │    J    │    K    │    L    │    ;    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │    Z    │    X    │    C    │    V    │    B    ││ SHIFT  ││PLY/PSE ││    N    │    M    │    ,    │    .    │    /    │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │  CTRL   │  LOWER  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  RAISE  │ BSPACE  │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */ 

   [_QWERTY] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                          KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  
    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                          KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  
    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LSFT,   KC_MPLY,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  
                        KC_LCTL,  LOWER,    KC_SPC,   KC_LALT,   KC_LGUI,  KC_ENT,   RAISE,    KC_BSPC
 ),


 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ m o u s e                                       │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │ RCLICK  │ MCLICK  │ LCLICK  │         ├─╯                ╰─┤         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │ SCROLL  │         │         ││        ││        ││         │         │         │         │         │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │         │         │         │         ││         │         │         │         │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_MOUSE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  SCROLL,   _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ l o w e r                                       │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │ CAPSLCK │ NUMLCK  │    ↑    │    =    │    {    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    }    │    7    │    8    │    9    │    +    │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │  SHIFT  │    ←    │    ↓    │    →    │    [    ├─╯                ╰─┤    ]    │    4    │    5    │    6    │    -    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │ SCRNSHT │   PG↑   │  SAVE   │   PG↓   │    (    ││  MUTE  ││PLY/PSE ││    )    │    1    │    2    │    3    │    *    │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │    ▼    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │ ADJUST  │    0    │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */ 

   [_LOWER] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_CAPS,  KC_NUM,   KC_UP,    KC_EQL,   KC_LCBR,                       KC_RCBR,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
    KC_LSFT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_LBRC,                       KC_RBRC,  KC_P4,    KC_P5,    KC_P6,    KC_MINS,  
    SNAP2,    KC_PGUP,  C(KC_S),  KC_PGDN,  KC_LPRN,  KC_MUTE,   KC_MPLY,  KC_RPRN,  KC_P1,    KC_P2,    KC_P3,    KC_PAST,  
                        _______,  _______,  _______,  RGB_MOD,   RGB_MOD,  _______,  ADJUST,   KC_P0
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ r a i s e                                       │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │    !    │    @    │    #    │    $    │    %    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    ^    │    &    │    Ü    │    °    │    /    │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │    Ä    │    è    │    SZ   │    é    │    "    ├─╯                ╰─┤    '    │    ¥    │    €    │    £    │    Ö    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │   WEB   │    `    │   CUE   │    ~    │         ││  MUTE  ││PLY/PSE ││  PBASE  │         │ DM REC1 │ DM STOP │ DM PLY1 │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │  GIPHY  │ ADJUST  │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */ 

   [_RAISE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                       KC_CIRC,  KC_AMPR,  RALT(KC_U),RALT(KC_3),KC_BSLS,
    RALT(KC_A),RALT(KC_F),RALT(KC_S),RALT(KC_G),KC_DQT,                   KC_QUOT,LSFT(RALT(KC_4)),RALT(KC_5), RALT(KC_4),  RALT(KC_O), 
    WMAIL,    LSFT(KC_GRV),RALT(KC_C),KC_GRV,XXXXXXX,  KC_MUTE,   KC_MPLY,  PBASE,  XXXXXXX,DM_REC1,  DM_RSTP,  DM_PLY1, 
                        GIPHY,    ADJUST,   _______,  RGB_MOD,   RGB_MOD,  _______,  _______,  _______
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ a d j u s t                                     │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │  RESET  │ AUDIO   │ HAPTIC  │   HUI   │   MOD   │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │   F7    │   F8    │   F9    │   F12   │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │ DEBUG   │         │ QWERTY  │   SAT   │         ├─╯                ╰─┤         │   F4    │   F5    │   F6    │   F11   │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │  MAKE   │ OS SWAP │ COLEMAK │   VAL   │         ││  MUTE  ││PLY/PSE ││         │   F1    │   F2    │   F3    │   F10   │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │    ▼    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */ 

   [_ADJUST] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    QK_BOOT,  AU_TOG,   HPT_TOG,  RGB_HUI,  RGB_MOD,                       XXXXXXX,  KC_F7,    KC_F8,    KC_F9,    KC_F12,   
    DB_TOGG,  XXXXXXX,  QWERTY,   RGB_SAI,  XXXXXXX,                       XXXXXXX,  KC_F4,    KC_F5,    KC_F6,    KC_F11,
    MAKE_H,   OS_SWAP,  COLEMAK,  RGB_VAI,  XXXXXXX,  KC_MUTE,   KC_MPLY,  XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F10,
                        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 )

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ t e m p l a t e                                 │
   └─────────────────────────────────────────────────┘
   ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
   │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │   
   ├─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         ││        ││        ││         │         │         │         │         │
   └─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┘
                       │         │         │         │         ││         │         │         │         │  
                       └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ 

   [_TEMPLATE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  
                        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 )*/ 
};




// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ H A P T I C   F E E D B A C K                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

void keyboard_post_init_user(void) {
  // Call the post init code.
  #if HAPTIC_ENABLE
    haptic_disable(); // disables per key haptic feedback by default
  #endif //HAPTIC ENABLE
  
  #if RGB_MATRIX_ENABLE
    rgblight_enable_noeeprom();
    //rgblight_sethsv_noeeprom(35, 255, 255); // set default RGB color to yellow
  #endif //RGB_MATRIX_ENABLE

 #ifdef OLED_ENABLE
    //wait_ms(1000);
    //oled_init(OLED_ROTATION_90);
  #endif //OLED_ENABLE
}




// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ O L E D                                                                                                                │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef OLED_ENABLE

void keyboard_post_init_kb(void) {
    oled_clear();
    oled_render();
    keyboard_post_init_user();
}

// Rotate OLED
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

// Draw to OLED
bool oled_task_user() {
    render_animation();
    return false;
}
#endif // OLED_ENABLE

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHT_T:
            return TAPPING_TERM - 150; 
        case SHT_N:
            return TAPPING_TERM - 150;  
        default:
            return TAPPING_TERM;
    }
}


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘


#ifdef POINTING_DEVICE_ENABLE
    static bool scrolling_mode = false;
#endif// POINTING_DEVICE_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case OS_SWAP: 
            if (record->event.pressed) {
                if (!keymap_config.swap_lctl_lgui) {
                  keymap_config.swap_lctl_lgui = true;  // ─── MAC
                  #ifdef AUDIO_ENABLE
                    PLAY_SONG(mac_song);
                  #endif // AUDIO_ENABLE
                }
                else {
                  keymap_config.swap_lctl_lgui = false; // ─── WIN
                  #ifdef AUDIO_ENABLE
                    PLAY_SONG(winxp_song);
                  #endif // AUDIO_ENABLE        
                }
              #ifdef HAPTIC_ENABLE
                DRV_pulse(pulsing_strong);
              #endif // HAPTIC_ENABLE
            eeconfig_update_keymap(keymap_config.raw);
            clear_keyboard();  // ──── clear to prevent stuck keys    
            return false;
          }


// ┌─────────────────────────────────────────────────┐
// │ l a y e r                                       │
// └─────────────────────────────────────────────────┘

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
                #ifdef HAPTIC_ENABLE
                  DRV_pulse(transition_hum);
                #endif // HAPTIC_ENABLE
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
                #ifdef HAPTIC_ENABLE
                  DRV_pulse(transition_hum);
                #endif // HAPTIC_ENABLE
            }
            return false;
        /*case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;

        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        */
// ┌─────────────────────────────────────────────────┐
// │ m o u s e                                       │
// └─────────────────────────────────────────────────┘
/*
     case SCROLL:
             if (record->event.pressed) {
                 scrolling_mode = true;
                pointing_device_set_cpi(50);
             } else {
                scrolling_mode = false;
                pointing_device_set_cpi(500);
            }
            return false;
*/
// ┌─────────────────────────────────────────────────┐
// │ q m k                                           │
// └─────────────────────────────────────────────────┘

        case MAKE_H:
          if (record->event.pressed) {
            #ifdef KEYBOARD_klor_rp2040
              SEND_STRING ("qmk compile -kb klor/rp2040 -km geistyubi");
            #else 
              SEND_STRING ("qmk compile -kb klor -km geistyubi");
            #endif
            tap_code(KC_ENTER); 
          } 
          break;

// ┌─────────────────────────────────────────────────┐
// │ p r o d u c t i v i t y                         │
// └─────────────────────────────────────────────────┘

      case WMAIL:
          if (record->event.pressed) {
            SEND_STRING (mymail);
          } 
          break;

      case PBASE:
          if (record->event.pressed) {
            SEND_STRING (pbase);
          } 
          break;

      case GIPHY:
          if (record->event.pressed) {
            SEND_STRING ("@gif ");
          } 
          break;

     case SNAP1:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LSFT(SS_LCMD("4")));           //MAC
            } else {
              SEND_STRING(SS_LWIN(SS_TAP(X_PSCR)));         //WIN
            }
          }
          break;

      case SNAP2:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LSFT(SS_LCMD(SS_LCTL("4"))));  //MAC           
            } else {
              SEND_STRING(SS_LSFT(SS_LWIN("S")));           //WIN
            }
          }
          break;

      case KC_MPLY:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  DRV_pulse(sharp_click);
          #endif // HAPTIC_ENABL
        }
        break;
    }
    return true;
}


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ E N C O D E R                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef ENCODER_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ e n c o d e r  L                                │
// └─────────────────────────────────────────────────┘ 

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }

// ┌─────────────────────────────────────────────────┐
// │ e n c o d e r  R                                │
// └─────────────────────────────────────────────────┘

    } else if (index == 1) {
      if(IS_LAYER_ON(_LOWER)){
          if (clockwise) {
              tap_code(KC_MNXT);
          } else {
              tap_code(KC_MPRV);
          }
      }else {
            if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
      }
    }
    return true;
}

#endif // ENCODER_ENABLE


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ T R A C K B A L L                                                                                                      │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef POINTING_DEVICE_ENABLE

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);  // always required before the auto mouse feature will work
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_mode) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

#endif //POINTING_DEVICE_ENABLE





/*

                                                       ▐█    ▟▛ ▐█     ▄▆▀▀▀▀▀▀▆▄  ▐█▀▀▀▀▀█▌
                                                       ▐█   ▟▛  ▐█    ▟▛        ▜▙ ▐█     █▌
                                                       ▐█  ▟▛   ▐█   ▐█          █▋▐█     █▌
                                                       ▐█ ▟█▙   ▐█   ▐█          █▋▐█▀▀▜█▀▀▘
                                                       ▐█▟▛ ▜▙  ▐█    ▜▙        ▟▛ ▐█   ▜▙
                                                       ▐█▛   ▜▙ ▐█▄▄▄▄ ▀▜▆▄▄▄▄▆▛▀  ▐█    ▜▙

                                                                 ▄██████████████▄
                                                                 ████████████████
                                                            ▄██████▀  ▀████▀  ▀██████▄
                                                            ███████▄  ▄████▄  ▄███████
                                                            ███████████▀▀▀▀███████████
                                                            ▀█████████▀ ▄▄ ▀█████████▀
                                                                 ████▀ ▄██▄ ▀████
                                                                 ████▄▄████▄▄████

*/



