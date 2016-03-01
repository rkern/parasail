# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

This project follows the [Gitflow Workflow model](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow).

## [Unreleased]
The Unreleased section will be empty for tagged releases. Unreleased functionality appears in the develop branch.

## [1.0.1] - 2016-03-01

### Added
- TODO
- TODO

### Changed
- Many improvements and bug fixes to the CMake build.
  - Needed to bump CMAKE_MINIMUM_REQUIRED to VERSION 3.1 to fix static linking.
  - Visual Studio, OSX, and Linux have been verified to work.
- Windows platform natively supported.
- If an instruction set, e.g., AVX2 is not detected, then the functions are stubbed out and return NULL and set errno to ENOSYS.
- restrict keyword is conditionally preprocessed away if it's not supported by the compiler (e.g., C++, C89).  parasail internally still uses restrict if there is a suitable extension (e.g., __restrict) but this change allows greater flexibility for external libraries and applications.

### Deprecated
- TODO
- TODO

### Removed
- TODO
- TODO

### Fixed
- Changed C++ style comments to C style to support MSVC build.
- Corrected mixed declarations and code to support MSVC build.
- Fixed various warnings from gcc -Wall -Wextra, clang, icc. MSVC build still produces many warnings.

### Closed Issues
- incorrect default SSE41_CFLAGS for gcc 4.4.7 [\#17]
- test_isa should also report what the compiler supported [\#15]
- update README et al. for new citation [\#13]
- Adding flag to disable/enable binaries in CMakeLists.txt [\#9]
- Profile thread safety? [\#8]
- Can't get parasail\_aligner to use \> 1 thread [\#7]
- Missing \#include \<string.h\> in tests [\#6]
- Documentation [\#5]
- AVX2: no such instruction [\#1](https://github.com/jeffdaily/parasail/issues/1)

## [1.0.0] - 2015-09-16
First stable, production-ready version of parasail.

[Unreleased]: https://github.com/jeffdaily/parasail/compare/v1.0.1...develop
[1.0.1]: https://github.com/jeffdaily/parasail/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/jeffdaily/parasail/releases/tag/v1.0.0

[\#17]: https://github.com/jeffdaily/parasail/issues/17
[\#16]: https://github.com/jeffdaily/parasail/issues/16
[\#15]: https://github.com/jeffdaily/parasail/issues/15
[\#14]: https://github.com/jeffdaily/parasail/issues/14
[\#13]: https://github.com/jeffdaily/parasail/issues/13
[\#12]: https://github.com/jeffdaily/parasail/issues/12
[\#11]: https://github.com/jeffdaily/parasail/issues/11
[\#10]: https://github.com/jeffdaily/parasail/issues/10
[\#9]: https://github.com/jeffdaily/parasail/issues/9
[\#8]: https://github.com/jeffdaily/parasail/issues/8
[\#7]: https://github.com/jeffdaily/parasail/issues/7
[\#6]: https://github.com/jeffdaily/parasail/issues/6
[\#5]: https://github.com/jeffdaily/parasail/issues/5
[\#4]: https://github.com/jeffdaily/parasail/issues/4
[\#3]: https://github.com/jeffdaily/parasail/issues/3
[\#2]: https://github.com/jeffdaily/parasail/issues/2
[\#1]: https://github.com/jeffdaily/parasail/issues/1