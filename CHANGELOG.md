# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial project structure
- Basic database operations (read/write)
- Memory safety checks
- Platform abstraction layer
- Unity test framework integration
- CMake build system
- String type support
  - Dynamic string handling based on size information
  - String storage and retrieval
  - String validation in tests
- Custom struct support
  - Variadic arguments for struct initialization in DATA macro
  - Full read/write capability for struct data types
  - Complete struct field validation in tests
- Comprehensive test suite
  - Low-level memory tests
  - High-level database operation tests
  - String handling tests
  - Struct handling tests
  - Error condition tests
- Project documentation
  - README.md with usage examples
  - CONTRIBUTING.md guidelines
  - CODE_OF_CONDUCT.md
  - CHANGELOG.md
  - MIT License

### Changed
- Improved memory management
  - Proper alignment handling for different data types
  - Correct magic number size calculation
  - Better memory bounds checking
- Enhanced error handling and status reporting
- Updated status codes for better error identification
- Improved test output with detailed status messages
- Refactored DATA macro to use variadic arguments for struct initialization
- Changed from fixed-length string classes to dynamic size-based string handling

### Deprecated
- None

### Removed
- Fixed-size string types (string_10, string_20, string_50, string_100)
- Replaced with dynamic size-based string handling

### Fixed
- Memory alignment issues for different data types
- Magic number size calculation (reduced from 4 bytes to 1 byte)
- Memory boundary checks in validation functions
- Database initialization and fetch behavior
- Memory cleanup between tests

### Security
- Added memory boundary checks
- Added magic number validation for data integrity
- Improved memory cleanup between operations 