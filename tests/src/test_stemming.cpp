#include <olestem/stemming/danish_stem.h>
#include <olestem/stemming/dutch_stem.h>
#include <olestem/stemming/english_stem.h>
#include <olestem/stemming/finnish_stem.h>
#include <olestem/stemming/french_stem.h>
#include <olestem/stemming/german_stem.h>
#include <olestem/stemming/italian_stem.h>
#include <olestem/stemming/norwegian_stem.h>
#include <olestem/stemming/portuguese_stem.h>
#include <olestem/stemming/russian_stem.h>
#include <olestem/stemming/spanish_stem.h>
#include <olestem/stemming/swedish_stem.h>

#include <string>
#include <unordered_map>

void stemWord(std::wstring & word)
{
    stemming::danish_stem<> StemDanish;
    stemming::dutch_stem<> StemDutch;
    stemming::english_stem<> StemEnglish;
    stemming::finnish_stem<> StemFinnish;
    stemming::french_stem<> StemFrench;
    stemming::german_stem<> StemGerman;
    stemming::italian_stem<> StemItalian;
    stemming::norwegian_stem<> StemNorwegian;
    stemming::portuguese_stem<> StemPortuguese;
    stemming::russian_stem<> StemRussian;
    stemming::spanish_stem<> StemSpanish;
    stemming::swedish_stem<> StemSwedish;

    StemDanish(word);
    StemDutch(word);
    StemEnglish(word);
    StemFinnish(word);
    StemFrench(word);
    StemGerman(word);
    StemItalian(word);
    StemNorwegian(word);
    StemPortuguese(word);
    StemRussian(word);
    StemSpanish(word);
    StemSwedish(word);
}

int main()
{
    std::vector<std::wstring> wordVect;
    wordVect = {L"løbende",
                L"aanhoudend",
                L"transportation",
                L"jatkuvasti",
                L"continuellement",
                L"ständig",
                L"continuamente",
                L"kontinuerlig",
                L"беспрестанно",
                L"kontinuerligt",
                L"",
                L" ",
                L"   ",
                L"    "};

    for (auto & word : wordVect) stemWord(word);

    return 0;
}