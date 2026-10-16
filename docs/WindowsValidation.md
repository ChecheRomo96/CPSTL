# Windows end-to-end validation — 2026-10-15

## Revisions and initial state

- CPSTL: `838d8b27c755361a1df716e8e72c76d3b4bca055`, initially clean.
- Pinned RoModularBuild: `c905ef4fbddc39d5602a097387c175fe11832135`
  (`v0.4.0`), clean throughout; no gitlink update or candidate dependency.
- Sibling RoModularBuild: `17fa6798de7db2abe51d17d469532e3d7501b145`.
  Its existing modified `README.md` and untracked
  `docs/PlatformWorkflowProposal.md` were preserved.
- One agent; no commits, tags, pushes, publications or other platform work.

## Tools and public interface

Windows 10.0.19045; x64 target; Visual Studio Build Tools 2022
17.14.37710.0; MSVC 19.44.35229.0, toolset directory 14.44.35207;
MSBuild 17.14.60; Windows SDK 10.0.26100.0; CMake/CTest 4.4.4;
PowerShell 7.6.7; Git 2.55.0.windows.5; Ninja 1.13.2 installed but unused
by the MSVC generator. The workflow requires CMake >=3.25, PowerShell,
the selected C++ compiler and SDK. Tests download GoogleTest at
`063de7e9578f82b369302001269680b4b1553359` with a fixed SHA256;
`FETCHCONTENT_SOURCE_DIR_GOOGLETEST` supports an existing offline checkout.

Public adapters are `scripts/configure.ps1`, `build.ps1`, `test.ps1`,
`install.ps1` and `clean.ps1`, with Bash counterparts. Initial Windows
presets were `windows_msvc_x64` (VS2026, x64) and `windows_clang_x64`
(Ninja Multi-Config). The added `windows_msvc2022_x64` selects VS2022,
inherits the existing x64 profile, and works with both adapter families.
No shared lifecycle behavior changed, so no Bash/PowerShell engine changes
were needed. Bash execution and Clang were not validated in this run.

## Acceptance criteria established before edits

1. Configure and build Debug and Release through CPSTL's public adapters.
2. Execute real tests in both configurations: positive JUnit test count,
   zero failures, no empty-suite override.
3. Install Release through the public adapter, including exported targets,
   headers and static library.
4. Copy the package and a standalone consumer outside CPSTL. Configure with
   `find_package`, compile and execute while CPSTL's entire original tree
   (source, build and dist) is unavailable. Disable CMake package registries.
5. Validate RoModularBuild's own contract and preserve the pinned revision.

## Baseline before tracked edits

`./scripts/configure.ps1 windows_msvc_x64` failed: the preset's
`Visual Studio 18 2026` generator could not find an installed instance.
VS2022 is installed; VS2026 is not.

`./scripts/configure.ps1 windows_msvc_x64 -Fresh -CMakeArguments
@('-G','Visual Studio 17 2022','-DCPSTL_TESTING=ON')` configured successfully.
However, `./scripts/test.ps1 windows_msvc_x64 -Configuration Debug
-Parallel 4 -JUnit build/validation/baseline-debug.xml` failed because its
configure step reapplied the VS2026 generator to the VS2022 build directory.
The baseline failure did not create that JUnit file.

A temporary `CMakeUserPresets.json` defined `windows_msvc2022_x64_local`,
inheriting `windows_msvc_x64` and overriding only the generator. Using the
public configure/build/test/install adapters with that preset and the
unchanged dependency passed Debug 176/176, Release 176/176 and installation.
This established that the installed toolchain worked before adding the
equivalent public CPSTL preset. The temporary user preset was then removed.

## Final commands and observed results

Executed from CPSTL with the new local CPSTL changes and the **unchanged**
RoModularBuild pin:

```powershell
cmake --list-presets=all
./scripts/configure.ps1 windows_msvc2022_x64
./scripts/build.ps1 windows_msvc2022_x64 -Configuration Debug -Parallel 4
./scripts/test.ps1 windows_msvc2022_x64 -Configuration Debug -Parallel 4 -JUnit build/validation/public-Debug.xml
./scripts/build.ps1 windows_msvc2022_x64 -Configuration Release -Parallel 4
./scripts/test.ps1 windows_msvc2022_x64 -Configuration Release -Parallel 4 -JUnit build/validation/public-Release.xml
./scripts/install.ps1 windows_msvc2022_x64
```

All succeeded. Both JUnit reports contain 176 tests, 0 failures and 0
disabled tests: 175 GoogleTest cases plus `CPSTLHeaderCheck`. Library/header
check use C++11; GoogleTest requires C++17. Configuration was STL OFF,
allocation C, vector/string/stack/queue ON. Release was installed to
`dist/windows_msvc2022_x64`. Other feature/allocation combinations were
outside this validation.

`./scripts/validate.ps1` also succeeded from both the pinned submodule and
the sibling RoModularBuild repository: 6 contract tests passed in each,
plus configure/build/install/clean checks. Its deliberate empty-suite test
failed without `-AllowNoTests` and succeeded with that explicit override.
That expected empty-suite case is not counted as CPSTL test evidence.

## Independent consumer and relocation evidence

The fixture at `tests/package-consumer` uses only
`find_package(CPSTL 1.1.5 EXACT CONFIG REQUIRED)` and `CPSTL::CPSTL`.
It checks vector insertion/sorting, string operations and `to_string`
(which also exercises compiled library symbols), returning nonzero on error.

Execution directory:
`C:/Users/jromo/AppData/Local/Temp/CPSTL-Windows-434c77b5ed6e486c95193020eeb5b882`.
The fixture and installed package were copied there as `consumer` and
`relocated-package`. Installed `.cmake` files contained no original CPSTL
source/build absolute paths. CPSTL was renamed temporarily to
`C:/Dev/RoModular/CPSTL.validation-hidden`; the original location was
confirmed absent before these commands:

```powershell
# $validationRoot is the external execution directory above.
cmake -S "$validationRoot/consumer" -B "$validationRoot/consumer-build" -G "Visual Studio 17 2022" -A x64 "-DCMAKE_PREFIX_PATH=$validationRoot/relocated-package" -DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF -DCMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY=OFF
cmake --build "$validationRoot/consumer-build" --config Release
ctest --test-dir "$validationRoot/consumer-build" -C Release --no-tests=error --output-on-failure --output-junit "$validationRoot/consumer.xml"
& "$validationRoot/consumer-build/Release/cpstl_consumer.exe"
```

All commands returned zero; CTest passed 1/1 and direct execution printed
`CPSTL 1.1.5: installed package PASS`. MSBuild emitted MSB8029 because the
independent build was under TEMP; it did not prevent compilation or execution.
The original tree was restored in a `finally` block.

Raw logs and JUnit reports remain under `build/validation/`, including
`public-*.log`, `public-Debug.xml`, `public-Release.xml`,
`pinned-romodular-validation.log`, `sibling-romodular-validation.log`,
`isolation.log`, `isolate.ps1` and `consumer.xml`. These are local ignored
execution artifacts, not committed evidence archives.

## VS2026 follow-up after installation

The user subsequently authorized installing VS2026. The official WinGet
package installed successfully with exit code 0:

```powershell
winget install --id Microsoft.VisualStudio.BuildTools --exact --source winget --accept-source-agreements --accept-package-agreements --override '--wait --quiet --norestart --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended' --disable-interactivity
```

Installed Build Tools 2026 package 18.10.4, instance 18.10.12306.391 at
`C:/Program Files (x86)/Microsoft Visual Studio/18/BuildTools`, alongside
VS2022. `vswhere` confirmed both instances complete, with no pending reboot.
The original preset detected MSVC 19.51.36260.0, toolset directory
14.51.36231, x64, MSBuild 18.10.1-1.26427.6 and SDK 10.0.26100.0.

The original preset was then executed without generator overrides:

```powershell
./scripts/configure.ps1 windows_msvc_x64 -Fresh
./scripts/build.ps1 windows_msvc_x64 -Configuration Debug -Parallel 4
./scripts/test.ps1 windows_msvc_x64 -Configuration Debug -Parallel 4 -JUnit build/validation/vs2026-Debug.xml
./scripts/build.ps1 windows_msvc_x64 -Configuration Release -Parallel 4
./scripts/test.ps1 windows_msvc_x64 -Configuration Release -Parallel 4 -JUnit build/validation/vs2026-Release.xml
./scripts/install.ps1 windows_msvc_x64
```

All commands succeeded: Debug 176/176 and Release 176/176, zero failures
and zero disabled tests; Release installed to `dist/windows_msvc_x64`.
CPSTL feature options and the pinned RoModularBuild revision were unchanged.
`-Fresh` cleared only the original preset's earlier failed build tree;
the VS2022 builds and reports were retained.

The installed package and consumer fixture were copied to
`C:/Users/jromo/AppData/Local/Temp/CPSTL-VS2026-ee4c4ce96e1c4b86b6405c835ae752d1`.
The isolation procedure above was repeated using the
`Visual Studio 18 2026` generator: original CPSTL tree unavailable,
package registries disabled, relocated package selected through
`CMAKE_PREFIX_PATH`. Configure/build/CTest/direct execution all passed;
the consumer ran 1/1 test and printed `CPSTL 1.1.5: installed package PASS`.
The original tree was restored in `finally`. The same harmless MSB8029
warning about using TEMP appeared.

Additional local evidence in `build/validation/`: `vs2026-configure.log`,
`vs2026-build-*.log`, `vs2026-test-*.log`, `vs2026-install.log`,
`vs2026-Debug.xml`, `vs2026-Release.xml`, `vs2026-isolation.log`,
`vs2026-consumer.xml`, `vs2026-isolate.ps1` and
`vs2026-installed-instances.json`.

## Allocation and STL matrix follow-up — 2026-10-15

Executed with the same CPSTL working tree, unchanged RoModularBuild
`c905ef4fbddc39d5602a097387c175fe11832135`, VS2026/MSVC 19.51.36260.0,
x64 and C++11 (GoogleTest uses C++17). No implementation changes were needed.
The previous builds, reports and uncommitted changes were preserved.

Temporary CMake user presets inherited `windows_msvc_x64` and selected:

| Preset | CPSTL_USING_STL | CPSTL_ALLOCATION | Debug | Release |
| --- | --- | --- | --- | --- |
| `windows_msvc_allocation_c` | OFF | C | 176/176 | 176/176 |
| `windows_msvc_allocation_cpp` | OFF | CPP | 176/176 | 176/176 |
| `windows_msvc_allocation_std` | OFF | STD | 175/175 | 175/175 |
| `windows_msvc_allocation_stl` | ON | STD | 165/165 | 165/165 |

Each preset also set `CPSTL_TESTING=ON`, `CPSTL_EXAMPLES=OFF` and
`CPSTL_CXX_STANDARD=11`. Modules retained their ON defaults. Each mode used
its own `build/<preset>` directory. The generated MSBuild project definitions
were checked for the requested `CPSTL_USING_*_ALLOCATION` macro and for
presence of `CPSTL_USING_STL` only in STL mode.

The exact adapter commands, run from CPSTL, were:

```powershell
$matrixRoot = Join-Path (Get-Location) 'build/validation/allocation-matrix'
foreach ($mode in @('c', 'cpp', 'std', 'stl')) {
    $preset = "windows_msvc_allocation_$mode"
    ./scripts/configure.ps1 $preset
    foreach ($configuration in @('Debug', 'Release')) {
        ./scripts/build.ps1 $preset -Configuration $configuration -Parallel 4
        ./scripts/test.ps1 $preset -Configuration $configuration -Parallel 4 `
            -JUnit "$matrixRoot/$mode-$configuration.xml"
    }
}
```

The actual runner captured each command's output separately and checked for
failure. All eight JUnit reports had positive test counts, zero failures and
zero disabled tests: **1,384 passing test executions** in total.

STD allocation omits `AllocatorTest.ReturnsNullOnOverflowAndZero`, which is
guarded out for `std::allocator`. STL mode excludes 18 CPSTL-specific cases
and adds seven STL-specific cases relative to C allocation, for a net count
of 165. The difference includes CPSTL allocation-failure guarantees, empty
adapter behavior and iterator specializations; it is conditional compilation,
not skipped or disabled tests. These results do not establish behavior under
real system-wide memory exhaustion.

Local evidence is in `build/validation/allocation-matrix/`:
`results.json`, eight JUnit XML reports, configure/build/test logs,
`compile-definitions.json`, `test-differences.json`, `run-matrix.ps1`, and a
snapshot of `CMakeUserPresets.json`. The temporary root user preset file was
removed after verification. To repeat this matrix, first copy that snapshot
to the CPSTL root, provided no user preset file already exists, then run the
saved runner from the CPSTL root. Keep the file while using these local
presets; it is needed for subsequent adapter invocations.

This follow-up tested builds and unit/header checks only. Installation and
isolated package consumption remain validated for the default C backend
above, not for each additional backend.

## Remaining limits and next step

Both VS2022 and the original VS2026 workflow passed end to end on this host.
No intervention, RoModularBuild source fix or dependency revision update
is needed. Review the CPSTL preset/documentation/fixture changes. Clang,
Bash execution, C++14/17/20 library builds, examples, other feature combinations and other platforms remain
outside the recorded validation scope.

## Release 1.1.6 verification — 2026-10-15

After the version update, the public test adapter passed 176/176 tests in
Debug and 176/176 in Release on `windows_msvc2022_x64`. Reports are
`build/validation/release-1.1.6-debug.xml` and
`build/validation/release-1.1.6-release.xml`. The public install adapter
installed version 1.1.6; the package-consumer fixture now requests that exact
version and passed its Release build and installed-package test using the
installed prefix with package registries disabled. The earlier relocation
experiment above remains evidence for version 1.1.5.
