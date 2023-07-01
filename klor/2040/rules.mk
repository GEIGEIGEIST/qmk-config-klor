# Ignore some warnings during the build, likely to be fixed before RP2040 PR is merged
ALLOW_WARNINGS = yes

# LTO must be disabled for RP2040 builds
LTO_ENABLE = no

# CONVERTER - if you use a listed MCU comment the first line and uncomment the appropiate line
CONVERT_TO = promicro_rp2040
#CONVERT_TO = kb2040
#CONVERT_TO = blok
#CONVERT_TO = elite_pi

# AUDIO 
AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware
