# Native AVR validation

The `atmega328p_avrgcc_avr5` and `atmega2560_avrgcc_avr6` presets build
`CPSTLAvrSmoke` with AVR-GCC and avr-libc, without an Arduino core. CPSTL owns
the test firmware and its USART0 verdict; the pinned RoModularBuild release
owns toolchain profiles, ELF/HEX/map generation, optional C++ allocation glue,
simavr execution and avrdude transport. avr-libc provides startup and linking.

CI builds Debug and Release for both MCUs, then runs the Release HEX in simavr
at 16 MHz. `CPSTL AVR smoke: PASS` means the smoke assertions passed; a failing
check prints `CPSTL AVR smoke: FAIL <number>`. This firmware is a separate
smoke suite from the full Arduino hardware suite and the native STM32 suite.
Simulation does not establish physical Mega/Uno verification.

## Build a Mega image on Windows

Initialize the pinned submodule with `git submodule update --init --recursive`.
With AVR-GCC installed, run from the CPSTL checkout:

```powershell
$avrRoot = Join-Path $env:LOCALAPPDATA 'Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7'
.\scripts\configure.ps1 atmega2560_avrgcc_avr6 -Fresh -CMakeArguments @("-DROMODULAR_AVR_TOOLCHAIN_ROOT=$avrRoot")
.\scripts\build.ps1 atmega2560_avrgcc_avr6 -Configuration Release -Parallel 4
```

The compiler can come from an Arduino tools installation; the generated image
does not link the Arduino core. Substitute your standalone AVR toolchain root
when appropriate. The resulting ELF, HEX and map are under
`build/atmega2560_avrgcc_avr6/bin/Release/`.

## Explicit physical Mega test

The following command replaces the application on the Mega on COM3. Close
other serial monitors first. The `wiring` protocol, 115200 baud and `-NoErase`
are for a Mega2560 with its normal serial bootloader, not an ISP programmer.
avrdude still checks the device signature and verifies the programmed image.

```powershell
$tools = Join-Path $env:LOCALAPPDATA 'Arduino15/packages/arduino/tools/avrdude'
$avrdude = (Get-ChildItem $tools -Recurse -Filter avrdude.exe | Select-Object -First 1).FullName
$config = (Get-ChildItem $tools -Recurse -Filter avrdude.conf | Select-Object -First 1).FullName
.\tools\RoModularBuild\scripts\avrdude.ps1 -Tool $avrdude -Config $config -Device atmega2560 -Programmer wiring -Port COM3 -Baud 115200 -NoErase -File .\build\atmega2560_avrgcc_avr6\bin\Release\CPSTLAvrSmoke.hex -Log .\build\mega-flash.log
```

Open a serial terminal at **9600 baud**, then reset the Mega to replay the
verdict. Expect `CPSTL AVR smoke: PASS`. Save its output separately from the
programming log: successful programming alone does not prove the tests ran.
The firmware sleeps after reporting. No physical result is claimed by CI.

On Linux, use `sh tools/RoModularBuild/scripts/simavr.sh --mcu atmega2560
--file build/atmega2560_avrgcc_avr6/bin/Release/CPSTLAvrSmoke.hex --log
build/mega-simavr.log` on one command line. Interpret the CPSTL verdict only
after the helper exits successfully.
