# Cradio Keyboard with KB2040

This is the [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040) revision, a drop-in Pro Micro replacement for Cradio.
## Keyboard Info

* Keyboard Maintainer: [@filterpaper](https://github.com/filterpaper)
* Hardware Supported: [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040) controllers with:
    * [Cradio](https://github.com/davidphilipbarr/36keys/tree/master/34Keys)
    * [Sweep](https://github.com/davidphilipbarr/Sweep)
    * [Hypergolic](https://github.com/davidphilipbarr/hypergolic)
    * Variants of the same 34-key direct pin PCB

Make example for this controller (after setting up your build environment):

    make cradio/kb2040:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOTLOADER` if it is configured.
* **Physical reset button**: Quick double-tap on the reset button soldered on the PCB.
* **Controller boot button**: Hold the `BOOT` button on the controller and plug in the USB.
* **Bootmagic reset**: Hold down the top left key on the left half and plug in the controller.
