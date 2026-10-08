# Hardware verification

CPSTL's embedded support is verified at three levels:

| Target | Build verification | Physical verification | CPSTL mode |
| --- | --- | --- | --- |
| AVR ATmega328P (Arduino Uno) | AVR-GCC smoke firmware, simavr and every Arduino tutorial | Upload an Arduino tutorial and observe its documented output at 9600 baud | CPSTL implementation with C allocation |
| ESP32 | Arduino compilation for `esp32:esp32:esp32` | Upload an Arduino tutorial and observe its documented output at 9600 baud | STL mode |
| STM32G0B1CBT6 | Foundation's Cortex-M0+ consumer build | Flash the Foundation consumer through ST-LINK and observe its configured pass signal | CPSTL implementation with C allocation and no C++ runtime |

The automated builds catch compiler, headers and link configuration errors.
Only a physical run can mark a board as hardware verified, because it also
covers the programmer/debugger connection, board power and the actual target.

## Verification record

| Date | Target | Connection | Result |
| --- | --- | --- | --- |
| 2026-10-07 | ESP32 | CP2102 USB-to-UART | `CPSTL hardware smoke: PASS` |
| 2026-10-07 | Arduino Mega (AVR) | COM8 | `CPSTL hardware smoke: PASS` |
| 2026-10-07 | ESP32 | CP2102 USB-to-UART | `Algorithms: PASS`; `Function: PASS` |
| 2026-10-07 | Arduino Mega (AVR) | COM8 | `Algorithms: PASS`; `Function: PASS` |
| 2026-10-07 | STM32G0B1CBT6 | ST-LINK / SWD, 100 kHz | Foundation consumer: 12/12 checks passed (`PASS`) |

## AVR and ESP32 procedure

1. Open a tutorial sketch under `examples/<Tutorial>/` in Arduino IDE, with
   this repository installed as the CPSTL library. `FixedCapacityLog` is a
   compact first tutorial; the catalog is in `examples/README.md`.
2. Select either an Arduino Uno or the connected ESP32 board and its serial
   port.
3. Upload the sketch, then open the serial monitor at 9600 baud.
4. Record the board model, core version and the tutorial output in the
   verification record.

An ESP32 has a hosted C++ standard library, so it intentionally uses
`CPSTL_USING_STL`. The AVR run intentionally uses CPSTL's own implementation
and `malloc`/`free`.

## STM32G0B1CBT6 procedure

Use the Foundation hardware-consumer firmware once its Cortex-M0+ build has
been generated. Connect the ST-LINK through SWD (PA13/SWDIO, PA14/SWCLK, NRST,
GND and 3.3 V reference); do not use a PICkit. Record the exact Foundation and
CPSTL commits, programmer version and the observable pass signal.

The STM32G0B1 is the freestanding case: the firmware must link with C
allocation and without `operator new` or `operator delete` from a C++ runtime.
