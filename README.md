
# Backlight control.

after installing arch on my macbook I didnt have any way to control the keyboard or display backlight, while i understand it would have been easier to just cat some text into the sys class i also wanted to practice my C skills so thought this would be a fun project.

# Requirements
User will need permssion to edit the sys class for the backlight, for display brightness see /sys/class/backlight or keyboard /sys/class/leds.

Rule can be setup in the /etc/udev/rules.d, example rule for leds, in leds.rules:
```
ACTION=="add", SUBSYSTEM=="leds", RUN+="/bin/chgrp backlightctrl $sys$devpath/brightness", RUN+="/bin/chmod g+w $sys$devpath/brightness"
```
This rule allows users part of the `backlightctrl` group to make changes to the brightness for leds.

# Setup reminder
In case i lose my mind, in order to set this up, add the brightnes path and the max_brightness value to the static.h in src.
Add softlink to `~/bin`
Update `.config/libinput-gestures.conf` for gesture controlled backlight brightness.