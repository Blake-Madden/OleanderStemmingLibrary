# Oleander Stemming Library

![logo](stemming.png)

Library for stemming words down to their roots (case insensitively).

This is a header-only library that can be included in your project as such:

```cpp
#include "english_stem.h"
```

## Example

```cpp
#include "english_stem.h"
#include "french_stem.h"
#include "german_stem.h"
#include "finnish_stem.h"
#include "swedish_stem.h"
#include "spanish_stem.h"
#include "dutch_stem.h"
#include "danish_stem.h"
#include "italian_stem.h"
#include "norwegian_stem.h"
#include "portuguese_stem.h"
#include "russian_stem.h"

#include <iostream>
#include <string>

int main()
    {
    // the word to be stemmed
    std::wstring word(L"documentation");

    /* Create an instance of a "english_stem" class. The template argument for the
       stemmers are the type of std::basic_string that you are trying to stem,
       by default std::wstring (Unicode strings).
       As long as the char type of your basic_string is wchar_t, then you can use
       any type of basic_string.
       This is to say, if your basic_string has a custom char_traits or allocator,
       then just specify it in your template argument to the stemmer. For example:

       using myString = std::basic_string<wchar_t, myTraits, myAllocator>;
       myString word(L"documentation");

       stemming::english_stem<myString> StemEnglish;
       StemEnglish(word);
    */

    stemming::english_stem<> StemEnglish;
    std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;

    // the "english_stem" has its operator() overloaded, so you can
    // treat your class instance like it's a function.  In this case,
    // pass in the std::wstring to be stemmed.  Note that this alters
    // the original std::wstring, so when the call is done the string will
    // be stemmed.
    StemEnglish(word);
    // now the variable "word" should equal "document"
    std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    // try a similar word that should have the same stem
    word = L"documenting";
    std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;
    StemEnglish(word);
    // now the variable "word" should equal "document"
    std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    // Now try a French word
    stemming::french_stem<> StemFrench;
    word = L"continuellement";
    std::wcout << L"\n(French) Original text:\t" << word.c_str() << std::endl;
    StemFrench(word);
    // now the variable "word" should equal "continuel"
    std::wcout << L"(French) Stemmed text:\t" << word.c_str() << std::endl;

    // Many other stemmers are also available
    stemming::german_stem<> StemGerman;
    stemming::finnish_stem<> StemFinnish;
    stemming::swedish_stem<> StemSwedish;
    stemming::dutch_stem<> StemDutch;
    stemming::spanish_stem<> StemSpanish;
    stemming::italian_stem<> StemItalian;
    stemming::norwegian_stem<> StemNorwgian;
    stemming::danish_stem<> StemDanish;
    stemming::portuguese_stem<> StemPortuguese;

    return 0;
    }
```
