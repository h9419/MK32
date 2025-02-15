#ifndef KEYMAP_C
#define KEYMAP_C

#include "key_definitions.h"
#include "keyboard_config.h"
#include "keymap.h"
#include "plugins.h"

// A bit different from QMK, default returns you to the first layer, LOWER and raise increase/lower layer by order.
#define DEFAULT 0x100
#define LOWER 0x101
#define RAISE 0x102

// Keymaps are designed to be relatively interchangeable with QMK
enum custom_keycodes
{
	QWERTY,
	PLUGINS,
};

//Set these for each layer and use when layers are needed in a hold-to use layer
enum layer_holds
{
	QWERTY_H = LAYER_HOLD_BASE_VAL,
	FUNCS_H
};

// array to hold names of layouts for oled
char default_layout_names[LAYERS][MAX_LAYOUT_NAME_LENGTH] = {
	"QWERTY",
	"Plugins",
};

/* select a keycode for your macro
 * important - first macro must be initialized as MACRO_BASE_VAL
 * */

#define MACROS_NUM 4
enum custom_macros
{
	KC_MS_NW = MACRO_BASE_VAL,
	KC_MS_NE,
	KC_MS_SW,
	KC_MS_SE,
};

/*define what the macros do
 * important- make sure you you put the macros in the same order as the their enumeration
 */
uint16_t macros[MACROS_NUM][MACRO_LEN] = {
	{KC_MS_UP, KC_MS_LEFT, KC_NO},
	{KC_MS_UP, KC_MS_RIGHT, KC_NO},
	{KC_MS_LEFT, KC_MS_DOWN, KC_NO},
	{KC_MS_RIGHT, KC_MS_DOWN, KC_NO},
};

/*Encoder keys for each layer by order, and for each pad
 * First variable states what usage the encoder has
 */

uint16_t default_encoder_map[LAYERS][ENCODER_SIZE] = {
	// |VOL + | VOL - | MUTE |
	{MEDIA_ENCODER, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE},
	// |Y+|Y-| LEFT CLICK|
	{MOUSE_ENCODER, KC_MS_UP, KC_MS_DOWN, KC_MS_BTN1}};

uint16_t default_slave_encoder_map[LAYERS][ENCODER_SIZE] = {
	// |VOL + | VOL - | MUTE |
	{MOUSE_ENCODER, KC_MS_WH_UP, KC_MS_WH_DOWN, KC_AUDIO_MUTE},
	// |Y+|Y-| LEFT CLICK|
	{MOUSE_ENCODER, KC_MS_RIGHT, KC_MS_LEFT, KC_MS_BTN2}};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

//NOTE: For this keymap due to wiring constraints the the two last rows on the left are wired unconventionally
// Each keymap is represented by an array, with an array that points to all the keymaps  by order
//  uint16_t _QWERTY[MATRIX_ROWS][KEYMAP_COLS]={

// 		/* Qwerty
// 		 * ,-----------------------------------------.    .-----------------------------------------.
// 		 * |  ~   |   1  |   2  |   3   |   4  |   5  |   |    6  |   7  |   8  |   9  |   0  |   -  |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Esc  |   Q  |   W  |   E   |   R  |   T  |   |    Y  |   U  |   I  |   O  |   P  |  =   |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Tab  |   A  |   S  |   D   |   F  |   G  |   |    H  |   J  |   K  |   L  |   ;  |  '   |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Shift|   Z  |   X  |   C   |   V  |   B  |   |    N  |   M  |   ,  |   .  |   /  |  up  |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Ctrl | GUI  |  Alt | Space |Space |NUM_H |   |  Del  |Bspc  |Enter | Left | Right  |Down  |
// 		 * `------------------------------------------'    ------------------------------------------'
// 		 *                            |default |RAISE|    |lower|NUM |
// 		 *                              --------------    ---------------
// 		 */
// 		  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS },
// 		  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQUAL},
// 		  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
// 		  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP } ,
// 		  {KC_LCTRL,KC_LGUI, KC_LALT, KC_SPC, KC_SPC,  NUM_H,  KC_DEL,  NUM,   LOWER, KC_BSPC, KC_ENT,  KC_LEFT },
// 		  {DEFAULT,RAISE, KC_NONE, KC_NONE, KC_NONE,   KC_NONE,  KC_RIGHT,  KC_DOWN,   KC_NONE, KC_NONE, KC_NONE,   KC_NONE }

// };

//  uint16_t _NUM[MATRIX_ROWS][KEYMAP_COLS]={

// 		/* Nums
// 		 * ,-----------------------------------------.    .-----------------------------------------.
// 		 * | F1   |   F2 |   F3 |   F4  |  F5  |  F6  |   |   F7  |  F8  |  F9  |  F10 | F11  |  F12 |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Esc  |   Q  |   W  |   E   |   R  |   T  |   |    Y  |   U  |   I  |   [ |   ]   |  \   |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Tab  |   A  |   S  |   D   |   F  |   G  |   |    H  |   J  |   K  |   L  |   ;  |  '   |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Shift|   Z  |   X  |   C   |   V  |   B  |   |    N  |   M  |   ,  |   .  |   /  |  up  |
// 		 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 		 * | Ctrl | GUI  |  Alt | Space |Space |NUM_H |   |  Del  |Bspc  |Enter | Left | Right  |Down  |
// 		 * `------------------------------------------'    ------------------------------------------'
// 		 *                            |default |RAISE|    |lower|NUM |
// 		 *                              --------------    ---------------
// 		 */
// 		  { KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9, KC_F10,KC_F11,  KC_F12 },
// 		  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_LBRC,    KC_RBRC, KC_BSLASH },
// 		  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
// 		  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQUAL } ,
// 		  {KC_LCTRL,KC_LGUI, KC_LALT, KC_SPC, KC_SPC,  NUM_H,  KC_DEL,  NUM,   LOWER, KC_BSPC, KC_ENT,  KC_LEFT },
// 		  {DEFAULT,RAISE, KC_NONE, KC_NONE, KC_NONE,   KC_NONE,  KC_RIGHT,  KC_DOWN,   KC_NONE, KC_NONE, KC_NONE,   KC_NONE }
// };

//  uint16_t _PLUGINS[MATRIX_ROWS][KEYMAP_COLS]={

// 			/* Plugins
// 			 * ,-----------------------------------------.    .-----------------------------------------.
// 			 * |  ~   |   1  |   2  |   3   |   4  |   5  |   |    6  |   7  |   8  |   9  |   0  |   -  |
// 			 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 			 * | Esc  |   Q  |   W  |   E   |   R  |   T  |   |    Y  |   U  |   I  |   O  |   P  |  =   |
// 			 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 			 * | Tab  |   A  |   S  |   D   |   F  |   G  |   |    H  |   J  |   K  |   L  |   ;  |  '   |
// 			 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 			 * | Shift|   Z  |   X  |   C   |   V  |   B  |   |    N  |   M  |   ,  |   .  |   /  |  up  |
// 			 * |------+------+------+-------+------+------|   |-------+------+------+------+------+------|
// 			 * | Ctrl | GUI  |  Alt | Space |Space |NUM_H |   |  Del  |Bspc  |Enter | Left | Right  |Down  |
// 			 * `------------------------------------------'    ------------------------------------------'
// 			 *                            |default |RAISE|    |lower|NUM |
// 			 *                              --------------    ---------------
// 			 */
// 			  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
// 			  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
// 			  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
// 			  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT } ,
// 			  {KC_LCTRL,KC_LGUI, KC_LALT, KC_SPC, KC_SPC,  NUM_H,  KC_DEL,  NUM,   LOWER, KC_BSPC, KC_ENT,  KC_LEFT },
// 			  {DEFAULT,RAISE, KC_NONE, KC_NONE, KC_NONE,   KC_NONE,  KC_RIGHT,  KC_DOWN,   KC_NONE, KC_NONE, KC_NONE,   KC_NONE }

// 	};
// uint16_t _default84[MATRIX_ROWS][KEYMAP_COLS] = {
// 	{KC_ESC,   KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,  			 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_F13,  KC_PAUS, KC_DEL},
// 	{KC_GRV,   KC_1,   KC_2,   KC_3,    KC_4,    KC_5,   			 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_NONE, KC_BSPC, KC_HOME},
// 	{KC_TAB,   KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,   			 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_NONE, KC_BSLS, KC_PGUP},
// 	{KC_CAPS,  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,  KC_NONE, KC_NONE, KC_ENT,  KC_PGDN},
// 	{KC_LSFT,  KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_NONE, KC_NONE, KC_RSFT,  KC_UP,  KC_END},
// 	{KC_LCTL,  KC_LALT,KC_LGUI,KC_SPC,  KC_NONE, KC_NONE, KC_RALT,   KC_RGUI,KC_RCTL, KC_NONE, KC_NONE,  KC_NONE, KC_NONE, KC_LEFT, KC_DOWN,  KC_RGHT}
// };

// 	uint16_t _default84[MATRIX_ROWS][KEYMAP_COLS] = {
// 	{KC_PAUS, KC_Q,   KC_W,    KC_E,    KC_R,   KC_U,  KC_I,    KC_O,    KC_P, KC_RSFT, KC_NONE},
// 	{KC_LALT, KC_TAB, KC_CAPS, KC_F3,    KC_T,  KC_Y,  KC_RBRC, KC_F7, KC_LBRC, KC_LSFT, KC_BSPC},
// 	{KC_NONE, KC_A,   KC_S,    KC_D,    KC_F,   KC_J,  KC_K,     KC_L,  KC_SCLN, KC_RGUI, KC_BSLS},
// 	{KC_UP,  KC_ESC, KC_SPC,   KC_F4,   KC_G,  KC_H,   KC_F6, KC_NONE,  KC_QUOT, KC_LGUI, KC_F11},
// 	{KC_RCTL,  KC_Z, KC_X,     KC_C,   KC_V,    KC_M,  KC_COMM, KC_DOT,  KC_NONE, KC_NONE, KC_ENT},
// 	{KC_LEFT,  KC_RGHT,KC_DOWN, KC_NONE, KC_B,    KC_N, KC_NONE, KC_DOT,  KC_SLSH, KC_RALT, KC_F12},
// 	{KC_LCTL,  KC_GRV, KC_F1,  KC_F2,    KC_5,   KC_6, KC_EQL,  KC_F8,  KC_MINUS,   KC_DEL, KC_F9},
// 	{KC_F5,    KC_1,   KC_2,    KC_3,    KC_4,   KC_7, KC_8,    KC_9,     KC_0,  KC_NONE,  KC_F10}
// };

uint16_t _defaultDuckyOne[MATRIX_ROWS][KEYMAP_COLS] = {
	{KC_GRV, KC_2, KC_4, KC_6, KC_8, KC_0, KC_EQUAL, KC_ESC, KC_F4, KC_F7, KC_PGUP, KC_INSERT, KC_NUMLOCK, KC_NONE, KC_KP_ASTERISK},
	{KC_TAB, KC_W, KC_R, KC_Y, KC_I, KC_P, KC_RBRC, KC_F2, KC_F6, KC_F9, KC_PGDOWN, KC_DELETE, KC_KP_7, KC_LGUI, KC_KP_9},
	{KC_CAPS, KC_S, KC_F, KC_H, KC_K, KC_SCLN, KC_ENTER, KC_NONE, KC_AUDIO_MUTE, KC_NONE, KC_F11, RAISE, KC_KP_4, KC_LALT, KC_KP_6},
	{KC_LSHIFT, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH, KC_RCTRL, KC_PSCREEN, KC_CALCULATOR, KC_NONE, KC_RIGHT, KC_DOWN, KC_KP_1, KC_RALT, KC_KP_3},
	{KC_1, KC_3, KC_5, KC_7, KC_9, KC_MINUS, KC_BSPACE, KC_F1, KC_F5, KC_F8, KC_NONE, KC_HOME, KC_KP_SLASH, KC_NONE, KC_KP_MINUS},
	{KC_Q, KC_E, KC_T, KC_U, KC_O, KC_LBRC, KC_BSLASH, KC_F3, KC_PAUSE, KC_NONE, KC_F10, KC_END, KC_KP_8, KC_LCTRL, KC_KP_PLUS},
	{KC_A, KC_D, KC_G, KC_J, KC_L, KC_QUOT, KC_NONE, KC_NONE, KC_AUDIO_VOL_DOWN, KC_NONE, KC_F12, KC_UP, KC_KP_5, KC_SPACE, KC_KP_ENTER},
	{KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_RSHIFT, KC_NONE, KC_SCROLLLOCK, KC_AUDIO_VOL_UP, KC_NONE, KC_KP_0, KC_LEFT, KC_KP_2, KC_RGUI, KC_KP_DOT},
};

uint16_t _DuckyOneMousePad[MATRIX_ROWS][KEYMAP_COLS] = {
	{KC_GRV, KC_2, KC_4, KC_6, KC_8, KC_0, KC_EQUAL, KC_ESC, KC_F4, KC_F7, KC_PGUP, KC_INSERT, KC_NUMLOCK, KC_NONE, KC_MS_ACCEL1},
	{KC_TAB, KC_W, KC_R, KC_Y, KC_I, KC_P, KC_RBRC, KC_F2, KC_F6, KC_F9, KC_PGDOWN, KC_DELETE, KC_NONE, KC_LGUI, KC_NONE},
	{KC_CAPS, KC_S, KC_F, KC_H, KC_K, KC_SCLN, KC_ENTER, KC_NONE, KC_AUDIO_MUTE, KC_NONE, KC_F11, RAISE, KC_MS_LEFT, KC_LALT, KC_MS_RIGHT},
	{KC_LSHIFT, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH, KC_RCTRL, KC_PSCREEN, KC_CALCULATOR, KC_NONE, KC_RIGHT, KC_DOWN, KC_NONE, KC_RALT, KC_NONE},
	{KC_1, KC_3, KC_5, KC_7, KC_9, KC_MINUS, KC_BSPACE, KC_F1, KC_F5, KC_F8, KC_NONE, KC_HOME, KC_MS_ACCEL0, KC_NONE, KC_NONE},
	{KC_Q, KC_E, KC_T, KC_U, KC_O, KC_LBRC, KC_BSLASH, KC_F3, KC_PAUSE, KC_NONE, KC_F10, KC_END, KC_MS_UP, KC_LCTRL, KC_MS_WH_UP},
	{KC_A, KC_D, KC_G, KC_J, KC_L, KC_QUOT, KC_NONE, KC_NONE, KC_AUDIO_VOL_DOWN, KC_NONE, KC_F12, KC_UP, KC_NONE, KC_SPACE, KC_MS_WH_DOWN},
	{KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_RSHIFT, KC_NONE, KC_SCROLLLOCK, KC_AUDIO_VOL_UP, KC_NONE, KC_MS_BTN1, KC_LEFT, KC_MS_DOWN, KC_RGUI, KC_MS_BTN2},
};

//Create an array that points to the various keymaps
uint16_t (*default_layouts[])[MATRIX_ROWS][KEYMAP_COLS] = {&_defaultDuckyOne, &_DuckyOneMousePad};

uint8_t current_layout = 0;

#endif
