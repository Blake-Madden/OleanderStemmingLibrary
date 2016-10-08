# Oleander Stemming Library

![logo](stemming.png)

Library for stemming words down to their root words.

## Compile Instructions

Run this to compile the sample:

> g++ example.cpp -o TestStemmer

To run the sample:

> ./TestStemmer

To generate the API documentation, open _doxygen.config_ in Doxygen and build it.

## License

Copyright (c) 2016, Oleander Software, Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of Oleander Software nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Change Log

### 2016 Release
- Updated *Portuguese* stemmer to new standard.

### 2015 Release
- Overhaul of Doxygen documentation.
- Updates to compile with GCC.
- Files are now UTF-8 (without BOM) encoded, which is compatible with Visual Studio 2008 and GCC. Note that this is no longer compatible with earlier versions of Visual Studio.

### 2010 Release
- Added *Russian* stemmer.
- Documentation expanded.

### 2009.1 Release
- Added support for smart apostrophes.


### 2009 Release
- Removed "common_lang_constants.cpp" so that the library now consists only of header files.

### 2.0 Release
- All extended ASCII characters are written in numeric value, so that you can compile on GCC without needing to encode the source code files to UTF-8.
- Fixed a few access violations.
- Fixed a bug in step1 of the French stemmer.
- Updated the English and Spanish stemmers to the newer 2006 algorithms.
- General optimizations.

**NOTE:** *This release is now only compatible with std::wstring (Unicode strings). If you need to stem an ANSI string, then convert it to a wstring using mbstowcs and then stem the wstring.*

### 1.2 Release
- Fixed a couple of bugs when compiling with GCC.

### 1.1 Release
- Fixed an error when compiling with Visual Studio 2005.

### 1.0 Release
- Added updates to English, Italian, Spanish, Norwegian, and Portuguese stemmers to include latest changes made to the Porter algorithms.
- Fixed case-sensitive comparison bug in Portuguese stemmer.
- Fixed bug in Portuguese stemmer where an "i" was sometimes incorrectly removed from the suffix.
- Fixed a bug in the English stemmer were some words ending in "e" would be incorrectly stemmed.
- Unicode now supported. If the symbol UNICODE is globally defined, stemmers now work with std::wstrings; otherwise, std::strings are expected.
- Removed template arguments for stemmers. Now you can just declare "english_stem EnglishStemmer;" instead of "english_stem<char> EnglishStemmer;"and it will know whether to expect either std::wstring or std::string types based on whether UNICODE is enabled.
- Now licensed under the BSD license.
- Added more helper functions in utilities.h and string_util.h

### 0.3 Release
- Fixed index bug in Dutch stemmer (wasn't checking size of string when it should have been).
- Fixed a compiler bug where a few inclusions were missing.
- Added "round" function to utility library for doing accurate integer rounding.
- Removed unused variable in English stemmer.
- Fixed compiler cast warning in "find_r2" function.
- Fixed access violation in "hash_german_yu", "hash_french_yui", and "hash_italian_ui" caused by one letter words.
- Fixed compiler error in stricmp function.
- Added "strstr" and "strcspn" char/wchar_t wrappers to string_util.h.
- Added "size_of_array" macro to utilities.h.
- Removed debugging hack code in "is_either" function in utilities.h.

### 0.2 Release

- Fixed a couple of syntax errors in Finnish and French stemmers that GCC picked up.
- Added support for German variant algorithm, where umlauted words are expanded to the English equivalent.