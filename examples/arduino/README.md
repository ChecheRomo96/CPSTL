# Arduino examples

These sketches are a compact, verifiable tour of the public CPSTL APIs that
match the C++ standard library. They add no Arduino-specific abstraction and
need no external hardware.

| Sketch | Verifies | Expected final serial line |
| --- | --- | --- |
| `BasicUsage` | `vector`, `string`, `sort` and `function` together | `CPSTL hardware smoke: PASS` |
| `Algorithms` | `copy`, `sort`, `find` and `equal` on contiguous storage | `CPSTL Arduino Algorithms: PASS` |
| `Containers` | `vector`, `string`, `stack` and `queue` | `CPSTL Arduino Containers: PASS` |
| `Function` | a capturing callback and a free-function callback | `CPSTL Arduino Function: PASS` |

## Arduino IDE

Install CPSTL as a library, open a sketch from **File > Examples > CPSTL**, and
select the board and serial port. Upload it, then open the Serial Monitor at
9600 baud. A physical run is successful only when the sketch prints its exact
`PASS` line.

`scripts/test-arduino.sh` compiles every sketch in this folder for the Uno,
Mega and ESP32 in CI. Compilation is not a substitute for the serial `PASS`
observation on a real board.
