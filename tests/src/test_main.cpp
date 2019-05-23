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

int main()
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

    std::wstring word(L"løbende");
    StemDanish(word);

    word = L"aanhoudend";
    StemDutch(word);

    word = L"transportation";
    StemEnglish(word);

    word = L"jatkuvasti";
    StemFinnish(word);

    word = L"continuellement";
    StemFrench(word);

    word = L"ständig";
    StemGerman(word);

    word = L"continuamente";
    StemItalian(word);

    word = L"kontinuerlig";
    StemNorwegian(word);

    word = L"continuamente";
    StemPortuguese(word);

    word = L"беспрестанно";
    StemRussian(word);

    word = L"continuamente";
    StemSpanish(word);

    word = L"kontinuerligt";
    StemSwedish(word);

    return 0;
}
