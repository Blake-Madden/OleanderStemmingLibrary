#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include "../src/danish_stem.h"
#include "../src/dutch_stem.h"
#include "../src/english_stem.h"
#include "../src/finnish_stem.h"
#include "../src/french_stem.h"
#include "../src/german_stem.h"
#include "../src/italian_stem.h"
#include "../src/norwegian_stem.h"
#include "../src/portuguese_stem.h"
#include "../src/russian_stem.h"
#include "../src/spanish_stem.h"
#include "../src/swedish_stem.h"
#include "utfcpp/source/utf8.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename Tstemmer>
void TestLanguage(const std::string_view dictionaryPath,
                  const std::string_view expectedPath,
                  Tstemmer& stemmer)
    {
    // Open the test file (must be UTF-8 encoded)
    std::ifstream dictFile(dictionaryPath.data());
    if (!dictFile.is_open())
        { FAIL("Dictionary file failed to load."); }
    std::ifstream expectedFile(expectedPath.data());
    if (!expectedFile.is_open())
        { FAIL("Expected results file failed to load."); }

    std::string line, line2;
    size_t lineNumber{ 0 };

    while (std::getline(dictFile, line))
        {
        if (utf8::find_invalid(line.begin(), line.end()) != line.end())
            { FAIL("Corrected UTF-8 in dictionary file."); }

        const auto utf16line = utf8::utf8to16(line);
        std::wstring dictLineText;
        if (utf16line.length())
            {
            std::for_each(utf16line.cbegin(), utf16line.cend(),
                [&dictLineText](const auto ch)
                { dictLineText.append(1, static_cast<wchar_t>(ch)); });
            }
        // chop off ' in front of string
        if (dictLineText.length() > 1 && dictLineText.front() == L'\'')
            { dictLineText.erase(0, 1); }

        std::getline(expectedFile, line2);
        if (utf8::find_invalid(line2.begin(), line2.end()) != line2.end())
            { FAIL("Corrected UTF-8 in expected results file."); }
        const auto utf16line2 = utf8::utf8to16(line2);
        std::wstring expectedLineText;
        if (utf16line2.length())
            {
            std::for_each(utf16line2.cbegin(), utf16line2.cend(),
                [&expectedLineText](const auto ch)
                { expectedLineText.append(1, static_cast<wchar_t>(ch)); });
            }

        // chop off ' in front of string, and any 's after them
        if (expectedLineText.length() > 1 && expectedLineText.front() == L'\'')
            { expectedLineText.erase(0, 1); }
        if (expectedLineText.length() > 2 &&
            expectedLineText.back() == L's' &&
            expectedLineText[expectedLineText.length() - 2] == L'\'')
            {
            expectedLineText.pop_back();
            expectedLineText.pop_back();
            }
        if (expectedLineText.length() > 1 &&
            expectedLineText.back() == L'\'')
            {
            expectedLineText.pop_back();
            }
        // avoid non-sensical tests like 's' and '''
        // (there is little merit in these tests and making the algorithm
        // less optimal to handle them isn't right).
        if (expectedLineText == L"'")
            {
            ++lineNumber;
            continue;
            }

        // skip if we read in BOMs
        if (dictLineText == L"0x0e00" && expectedLineText == L"0x0e00")
            {
            ++lineNumber;
            continue;
            }

        stemmer(dictLineText);
        if (dictLineText != expectedLineText)
            {
            UNSCOPED_INFO("Comparison failed on line #" << lineNumber);
            }
        CHECK(dictLineText == expectedLineText);

        // uppercase the string, stem it, then lowercase it and compare that with the expected result
        std::wstring upperDictLineText{ dictLineText };
        std::transform(upperDictLineText.cbegin(), upperDictLineText.cend(), upperDictLineText.begin(),
            [](const auto& ch)
            { return std::towupper(ch); });
        stemmer(upperDictLineText);
        std::transform(upperDictLineText.cbegin(), upperDictLineText.cend(), upperDictLineText.begin(),
            [](const auto& ch)
            { return std::towlower(ch); });
        if (dictLineText != expectedLineText)
            {
            UNSCOPED_INFO("UCase comparison failed on line #" << lineNumber);
            }
        CHECK(dictLineText == expectedLineText);

        ++lineNumber;
        }
    }

TEST_CASE("danish", "[stemming][dutch]")
    {
    stemming::danish_stem stemmer;
    TestLanguage("danish/voc.txt", "danish/output.txt", stemmer);
    }

TEST_CASE("dutch", "[stemming][dutch]")
    {
    stemming::dutch_stem stemmer;
    TestLanguage("dutch/voc.txt", "dutch/output.txt", stemmer);
    }

TEST_CASE("english", "[stemming][english]")
    {
    stemming::english_stem stemmer;
    TestLanguage("english/voc.txt", "english/output.txt", stemmer);
    }

TEST_CASE("finnish", "[stemming][finnish]")
    {
    stemming::finnish_stem stemmer;
    TestLanguage("finnish/voc.txt", "finnish/output.txt", stemmer);
    }

TEST_CASE("french", "[stemming][french]")
    {
    stemming::french_stem stemmer;
    TestLanguage("french/voc.txt", "french/output.txt", stemmer);
    }

TEST_CASE("german", "[stemming][german]")
    {
    stemming::german_stem stemmer;
    TestLanguage("german/voc.txt", "german/output.txt", stemmer);
    }

TEST_CASE("italian", "[stemming][italian]")
    {
    stemming::italian_stem stemmer;
    TestLanguage("italian/voc.txt", "italian/output.txt", stemmer);
    }

TEST_CASE("norwegian", "[stemming][norwegian]")
    {
    stemming::norwegian_stem stemmer;
    TestLanguage("norwegian/voc.txt", "norwegian/output.txt", stemmer);
    }

TEST_CASE("portuguese", "[stemming][portuguese]")
    {
    stemming::portuguese_stem stemmer;
    TestLanguage("portuguese/voc.txt", "portuguese/output.txt", stemmer);
    }

TEST_CASE("russian", "[stemming][russian]")
    {
    stemming::russian_stem stemmer;
    TestLanguage("russian/voc.txt", "russian/output.txt", stemmer);
    }

TEST_CASE("spanish", "[stemming][spanish]")
    {
    stemming::spanish_stem stemmer;
    TestLanguage("spanish/voc.txt", "spanish/output.txt", stemmer);
    }

TEST_CASE("swedish", "[stemming][swedish]")
    {
    stemming::swedish_stem stemmer;
    TestLanguage("swedish/voc.txt", "swedish/output.txt", stemmer);
    }
