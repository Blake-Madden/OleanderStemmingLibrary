## Change Log

### 2023.1 Release
- Updated the Swedish and German stemmers to the latest Snowball 2.3 standard.

### 2023 Release
- Updated Spanish, Russian, Italian, and French stemmers to the latest Snowball standard.
- Made stemming less aggressive with punctuation at the end of a word. Now, only trailing `'` and `'s'
  are removed.
- Added Catch2 unit tests which compare results against the latest Snowball datasets.\n
  (Unit tests can be built with CMake.)

### 2022 Release
- Modernized code to C++17.
- Added support for full-width characters (e.g., "Ｄｏｃｕｍｅｎｔｉｎｇ" will become "Document").
- Streamlined the library, removing most of the peripheral helper files.
- Changed license to BSD.

### 2016 Release
- Updated Portuguese stemmer to new standard.

### 2015 Release
- Overhaul of Doxygen documentation.
- Updates to compile with GCC.
- Files are now UTF-8 (without BOM) encoded, which is compatible with Visual Studio 2008 and GCC. Note that this is no longer compatible with earlier versions of Visual Studio.

### 2010 Release
- Added Russian stemmer.
- Documentation expanded.

### 2009.1 Release
- Added support for smart apostrophes.

### 2009 Release
- Removed "common_lang_constants.cpp" so that the library now consists only of header files.

### 2.0 Release
- All extended ASCII characters are written in numeric value, so that you can compile on GCC without needing to encode the source code files to UTF-8.
- Fixed a few access violations.
- Fixed a bug in step 1 of the French stemmer.
- Updated the English and Spanish stemmers to the newer 2006 algorithms.
- General optimizations.

**NOTE:** This release is now only compatible with `std::wstring` (Unicode strings). If you need to stem an ANSI string, then convert it to a wstring using `mbstowcs()` and then stem the `std::wstring`.

### 1.2 Release
- Fixed a couple of bugs when compiling with GCC.

### 1.1 Release
- Fixed an error when compiling with Visual Studio 2005.

### 1.0 Release
- Added updates to English, Italian, Spanish, Norwegian, and Portuguese stemmers to include latest changes made to the Porter algorithms.
- Fixed case-sensitive comparison bug in Portuguese stemmer.
- Fixed bug in Portuguese stemmer where an "i" was sometimes incorrectly removed from the suffix.
- Fixed a bug in the English stemmer were some words ending in "e" would be incorrectly stemmed.
- Unicode now supported. If the symbol `UNICODE` is globally defined, stemmers now work with `std::wstring`s; otherwise, `std::string`s are expected.
- Removed template arguments for stemmers. Now you can just declare `english_stem EnglishStemmer;` instead of `english_stem<char> EnglishStemmer;` and it will know whether to expect either `std::wstring` or `std::string` types based on whether UNICODE is enabled.
- Now licensed under the BSD license.
- Added more helper functions in "utilities.h" and "string_util.h".

### 0.3 Release
- Fixed index bug in Dutch stemmer (wasn't checking the size of string when it should have been).
- Fixed a compiler bug where a few inclusions were missing.
- Added `round()` function to utility library for doing accurate integer rounding.
- Removed unused variable in English stemmer.
- Fixed compiler cast warning in `find_r2()` function.
- Fixed access violation in `hash_german_yu()`, `hash_french_yui()`, and `hash_italian_ui()` caused by one letter words.
- Fixed compiler error in `stricmp()` function.
- Added `strstr()` and `strcspn()` `char/wchar_t` wrappers to "string_util.h".
- Added `size_of_array()` macro to "utilities.h".
- Removed debugging hack code in `is_either()` function in "utilities.h".

### 0.2 Release

- Fixed a couple of syntax errors in Finnish and French stemmers that GCC picked up.
- Added support for German variant algorithm, where umlauted words are expanded to the English equivalent.
