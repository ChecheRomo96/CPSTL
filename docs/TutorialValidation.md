# Tutorial validation — 2026-10-15

CPSTL 1.1.7 aligns all 20 Arduino/desktop tutorial pairs around observable
inputs, operations and results. The legacy AUnit runner is separate and now
explains that it contains no registered CPSTL test cases.

Validation performed on Windows with MSVC 2022 and Arduino CLI:

- Built and executed all 20 desktop tutorials with the public
  `windows_msvc2022_x64` adapters in Release, using C, CPP and STD allocation,
  and separately with `CPSTL_USING_STL=ON`.
- Compared the 19 scenario transcripts across all four configurations. They
  match; the configuration report intentionally reflects its selected mode.
- Checked the observable results: retained capture order after sorting a copy,
  exact lookup position, 20 reversed samples, independent vector copies,
  insertion/erasure contents, queue arrival order, undo restoration, callback
  totals, ownership transfer, rejected commands, and 3753 mV ADC conversion.
- Compiled all 20 tutorials for both `arduino:avr:uno` and
  `arduino:avr:mega` with stock C++11 core flags: 40 successful builds.
- Ran the native Release suite: 176/176 tests passed. Installed the 1.1.7
  package, built the standalone consumer requesting exactly that version,
  and passed its execution test.

Each tutorial README includes a captured desktop transcript. Byte samples,
capacity, numeric limits and build settings have explicit portability notes.
The Arduino builds verify compilation, not physical serial output; no boards
were flashed or executed during this revision. Other hosts and cores were
not exercised in this run.

Local logs and captured outputs are under `build/tutorial-validation/`.
