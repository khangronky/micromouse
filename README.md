# Neo Micromouse Project

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Libraries](#libraries)
- [Contributing](#contributing)
- [License](#license)

## Overview

The **Neo Micromouse Project** is an embedded systems project developed using the Arduino framework and PlatformIO. This project aims to create a sophisticated micromouse capable of navigating mazes efficiently. Leveraging modular code architecture with dedicated libraries and comprehensive unit testing ensures reliability and scalability.

## Features

- **Modular Architecture:** Organized codebase with separate directories for source files, headers, libraries, and tests.
- **PlatformIO Integration:** Efficient build and dependency management using PlatformIO.
- **Unit Testing:** Comprehensive tests to ensure code quality and functionality.
- **Custom Libraries:** Reusable libraries tailored for the micromouse functionalities.
- **Arduino UNO Compatible:** Designed to run on the Arduino UNO board with ease.

## Project Structure

- **include/**: Contains project header files for declarations and macro definitions.
- **lib/**: Private libraries for the project.
- **src/**: Source files for the main application.
- **test/**: Unit tests for the project using PlatformIO Test Runner.
- **.gitignore**: Specifies files and directories to be ignored by Git.
- **platformio.ini**: PlatformIO project configuration file.
- **README.md**: Project documentation.

## Installation

### Prerequisites

- **Arduino IDE**: Ensure you have Arduino IDE installed.
- **VS Code**: Ensure you have VS Code installed.
- **PlatformIO**: Ensure you have PlatformIO installed. You can install it as a [VS Code extension](https://platformio.org/install/ide?install=vscode) or as a standalone CLI.

### Setup

1. **Clone the Repository**

   ```bash
   git clone https://github.com/khangronky/micromouse.git
   cd micromouse
   ```

2. **Install Dependencies**

   PlatformIO will automatically handle dependencies specified in the `platformio.ini` and library directories.

## Usage

### Building the Project

To build the project, navigate to the project directory and run:

```bash
platformio run
```

### Uploading to Arduino UNO

Ensure your Arduino UNO is connected, then upload the firmware:

```bash
platformio run --target upload
```

### Monitoring Serial Output

To monitor the serial output from the Arduino UNO:

```bash
platformio device monitor
```

## Testing

The project includes unit tests to verify the functionality of individual modules.

### Running Tests

Execute the following command to run all unit tests:

```bash
platformio test
```

### Test Configuration

Tests are located in the `test/` directory and utilize PlatformIO's built-in testing framework.

## Libraries

No library is used in this project.

## Contributing

Contributions are welcome! Please follow these steps:

1. **Clone the Repository**

   ```bash
   git clone https://github.com/khangronky/micromouse.git
   cd micromouse
   ```

2. **Create a Feature Branch**

   ```bash
   git checkout -b feature/YourFeature
   ```

3. **Commit Your Changes**

   ```bash
   git commit -m "Add some feature"
   ```

4. **Push to the Branch**

   ```bash
   git push origin feature/YourFeature
   ```

5. **Open a Pull Request**

## Acknowledgements

- [PlatformIO](https://platformio.org/)
- [Arduino](https://www.arduino.cc/)
- [GCC Documentation on Header Files](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html)

---

For any questions or support, please open an issue in the [GitHub repository](https://github.com/khangronky/micromouse/issues).
