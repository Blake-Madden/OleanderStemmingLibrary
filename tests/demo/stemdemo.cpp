// This is mostly used as a CMake project used for code analysis.

#include "src/danish_stem.h"
#include "src/dutch_stem.h"
#include "src/english_stem.h"
#include "src/finnish_stem.h"
#include "src/french_stem.h"
#include "src/german_stem.h"
#include "src/italian_stem.h"
#include "src/norwegian_stem.h"
#include "src/portuguese_stem.h"
#include "src/russian_stem.h"
#include "src/spanish_stem.h"
#include "src/swedish_stem.h"

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

    // The "english_stem" has its operator() overloaded, so you can
    // treat your class instance like it's a function.  In this case,
    // pass in the std::wstring to be stemmed. Note that this alters
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

    // now try a French word
    stemming::french_stem<> StemFrench;
    word = L"continuellement";
    std::wcout << L"\n(French) Original text:\t" << word.c_str() << std::endl;
    StemFrench(word);
    // now the variable "word" should equal "continuel"
    std::wcout << L"(French) Stemmed text:\t" << word.c_str() << std::endl;

    // many other stemmers are also available
    stemming::danish_stem<> StemDanish;
    stemming::dutch_stem<> StemDutch;
    stemming::finnish_stem<> StemFinnish;
    stemming::italian_stem<> StemItalian;
    stemming::german_stem<> StemGerman;
    stemming::norwegian_stem<> StemNorwegian;
    stemming::portuguese_stem<> StemPortuguese;
    stemming::russian_stem<> StemRussian;
    stemming::spanish_stem<> StemSpanish;
    stemming::swedish_stem<> StemSwedish;

    return 0;
    }
