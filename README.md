# CPSTL: Cross-Platform STL Wrapper

CPSTL is a library that serves as a wrapper for the C++ Standard Template Library (STL), enabling cross-platform development whether the STL is available or not. This library provides a consistent interface for STL functionality, allowing developers to write code that can run on multiple platforms without being dependent on the STL's presence.

## Repository Structure

This repository is the central hub for the CPSTL project. CPSTL has been structured into separate repositories to accommodate various platforms and to ensure compatibility with different environments. Additional repositories include:

- [CPSTL-Arduino](https://github.com/YourUsername/CPSTL-Arduino): Optimized and tested for use in Arduino projects.
- [CPSTL-CMake](https://github.com/YourUsername/CPSTL-CMake): Provides directory structures and CMake files for easy integration into larger projects.

## Key Features

- **Cross-Platform Compatibility:** CPSTL is designed to work on different platforms, ensuring that your code functions consistently regardless of the availability of the C++ STL.

- **Ease of Use:** The library provides a familiar and user-friendly interface, making it easy for developers familiar with the C++ STL to work with CPSTL.

- **Integration with CMake:** The repository includes directory structures and CMake files, simplifying the compilation and integration of CPSTL into larger projects.

- **Arduino Support:** CPSTL has been optimized and tested for use in Arduino projects, making it a reliable choice for Arduino development.

- **Dynamic Documentation:** The documentation is adaptable to the package compilation configuration, ensuring that it remains accurate and relevant for specific builds.

- **Clear Documentation:** The library's documentation is generated using Doxygen, making it easy to understand the provided functions, methods, and classes in CPSTL.

## Tested Platforms

CPSTL has been rigorously tested on various platforms to ensure its reliability and cross-compatibility:

- Arduino IDE:
  - AVR (e.g., Arduino Uno, Arduino Mega, etc.) (using C)
  - ESP32 (using C, C++, and CPSTL)

- Windows:
  - Compiled using Visual C++ (cl) (using CPSTL)

- Ubuntu:
  - Compiled using g++ (using CPSTL)
  - Compiled using clang++ (using CPSTL)

- Raspbian:
  - Compiled using g++ (using CPSTL)
  - Compiled using clang++ (using CPSTL)

- macOS:
  - Compiled using g++ (using CPSTL)
  - Compiled using clang++ (using CPSTL)

## Online Documentation

CPSTL offers comprehensive online documentation generated with Doxygen. This documentation provides detailed insights into the functions, methods, classes, and usage examples provided by the library.

To access the online documentation, please visit the [CPSTL Documentation](https://yourusername.github.io/CPSTL/index.html) website.

The online documentation serves as a valuable resource for understanding and effectively utilizing CPSTL in your projects.

## Quick Start

This main repository contains all the essential files compatible with various platforms and file systems, including implementations for different environments like Arduino, Windows, Ubuntu, and macOS.

- If your primary focus is integrating CPSTL seamlessly with CMake, you'll find dedicated resources in the CPSTL-CMake repository. Here, you'll discover a structured directory layout and CMake files tailored to simplify CPSTL integration into larger projects.

- For projects centered around Arduino development, we recommend exploring the CPSTL-Arduino repository. This repository is specifically designed with a file structure optimized for Arduino development.

Please choose the repository that aligns with your project's specific needs to streamline the integration of CPSTL into your development environment and make the most of its cross-platform capabilities.

## Unit Testing

Unit testing is a critical aspect of maintaining the quality and reliability of CPSTL across its various sub-repositories. It's important to note that unit testing methods may vary between each sub-project due to the unique requirements and platforms they cater to. Thorough unit testing is conducted on each sub-repository to ensure functionality and compatibility.

[Unit Testing Page](https://yourusername.github.io/CPSTL/d4/df6/test.html)

## Contributions

Your contributions are highly welcome! If you encounter issues, wish to add new features, or enhance existing ones, please submit a pull request to the CPSTL repository.

## Contact

For questions, suggestions, or comments, feel free to open an [issue](https://github.com/YourUsername/CPSTL/issues) on the repository.

We hope CPSTL proves to be a valuable asset in your cross-platform development projects!

## To Do:

- Enhance the documentation structure.
- Create a tutorials page for the documentation.
- Implement unit testing for CPSTL-Arduino.
- Set up unit testing actions for CPSTL-CMake and CPSTL-Arduino.
