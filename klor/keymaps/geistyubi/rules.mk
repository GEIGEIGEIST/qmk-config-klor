# ┌─────────────────────────────────────────────────┐
# │ s o f t w a r e   f e a t u r e s               │
# └─────────────────────────────────────────────────┘ 

COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes		# multi media keys
DYNAMIC_MACRO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
SWAP_HANDS_ENABLE = yes

# ┌─────────────────────────────────────────────────┐
# │ h a r d w a r e   f e a t u r e s               │
# └─────────────────────────────────────────────────┘ 

#ENCODERS
ENCODER_ENABLE = yes

#OLED 
OLED_ENABLE = yes

#PER KEY RGB
RGB_MATRIX_ENABLE = yes     # do not use together with RGBLIGHT_ENABLE

#AUDIO
AUDIO_ENABLE = yes
MUSIC_ENABLE = yes

#HAPTIC FEEBACK
HAPTIC_ENABLE = yes

#TRACKBALL
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = paw3204
MOUSEKEY_ENABLE = yes