/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
     it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_GERMAN_STEM_H
#define OLEAN_GERMAN_STEM_H

#include "stemming.h"

namespace stemming
    {
    /**
    @brief German stemmer.
    */
    //------------------------------------------------------
    template <typename string_typeT = std::wstring>
    class german_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Set to @c true (the default) to use the algorithm that expands "ä" to "ae", etc...
            @details This should only be @c false if preferring to use the German algorithm prior
                to the Snowball 2.3.0 standard.
            @param transliterate_umlauts Whether to transliterate umlauted vowels.*/
        void should_transliterate_umlauts(const bool transliterate_umlauts)
            { m_transliterate_umlauts = transliterate_umlauts; }
        /// @returns Whether umlauted vowels are being transliterated.
        bool is_transliterating_umlauts() const noexcept
            { return m_transliterate_umlauts; }
        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::german; }
        /** @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            if (text.length() < 2)
                {
                stem<string_typeT>::remove_german_umlauts(text);
                return;
                }

            // reset internal data
            stem<string_typeT>::reset_r_values();

            std::transform(text.begin(), text.end(), text.begin(), full_width_to_narrow);
            stem<string_typeT>::remove_possessive_suffix(text);

            stem<string_typeT>::hash_german_yu(text, GERMAN_VOWELS);
            // change 'ß' to "ss"
            stem<string_typeT>::replace_all(text, string_typeT(1, common_lang_constants::ESZETT), L"ss");
            // German variant addition
            if (is_transliterating_umlauts())
                {
                stem<string_typeT>::replace_all(text, L"ae",
                    string_typeT(1, common_lang_constants::LOWER_A_UMLAUTS));
                stem<string_typeT>::replace_all(text, L"oe",
                    string_typeT(1, common_lang_constants::LOWER_O_UMLAUTS));
                // ue to ü, if not in front of 'q'
                size_t start = 1;
                while (start != string_typeT::npos)
                    {
                    start = text.find(L"ue", start);
                    if (start == string_typeT::npos ||
                        stem<string_typeT>::is_either(text[start-1],
                            common_lang_constants::LOWER_Q, common_lang_constants::UPPER_Q) )
                        {
                        break;
                        }
                    text.replace(start, 2, string_typeT(1, common_lang_constants::LOWER_U_UMLAUTS));
                    }
                }

            stem<string_typeT>::find_r1(text, GERMAN_VOWELS);
            if (stem<string_typeT>::get_r1() == text.length() )
                {
                stem<string_typeT>::remove_german_umlauts(text);
                stem<string_typeT>::unhash_german_yu(text);
                return;
                }
            stem<string_typeT>::find_r2(text, GERMAN_VOWELS);
            // R1 must have at least 3 characters in front of it
            if (stem<string_typeT>::get_r1() < 3)
                {
                stem<string_typeT>::set_r1(3);
                }

            step_1(text);
            step_2(text);
            step_3(text);

            // unhash special 'u' and 'y' back, and remove the umlaut accent from a, o and u. 
            stem<string_typeT>::remove_german_umlauts(text);
            stem<string_typeT>::unhash_german_yu(text);
            }
    private:
        //---------------------------------------------
        void step_1(string_typeT& text)
            {
            bool groupCDeleted{ false };
            // 'em', but not if 'system'
            if ((stem<string_typeT>::is_suffix(text,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M)) &&
                !(stem<string_typeT>::is_suffix(text,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_Y, common_lang_constants::UPPER_Y,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M)) &&
                stem<string_typeT>::delete_if_is_in_r1(text,
                /*em*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*erinnen*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*erin*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ern*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*lns*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                text.erase(text.length() - 2);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*ln*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                text.erase(text.length() - 1);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*er*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*es*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                groupCDeleted = true;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*en*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                groupCDeleted = true;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                groupCDeleted = true;
                }
            // Define a valid s-ending as one of b, d, f, g, h, k, l, m, n, r or t.
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                if (stem<string_typeT>::is_one_of(text[text.length()-2], L"bdfghklmnrtBDFGHKLMNRT") )
                    {
                    text.erase(text.length()-1);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }

            if (groupCDeleted && text.length() > 4 &&
                stem<string_typeT>::is_suffix(text,
                          common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                          common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                          common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                          common_lang_constants::LOWER_S, common_lang_constants::UPPER_S))
                { text.pop_back(); }
            }
        //---------------------------------------------
        void step_2(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*est*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*er*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*en*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                return;
                }
            // Define a valid st-ending as the same list, excluding letter r.
            else if (text.length() >= 6 &&
                    stem<string_typeT>::is_suffix_in_r1(text,
                        /*st*/
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                if (stem<string_typeT>::is_one_of(text[text.length()-3], L"bdfghklmntBDFGHKLMNT"))
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (text.length() >= 4 &&
                    stem<string_typeT>::is_suffix_in_r1(text,
                        /*et*/
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                constexpr wchar_t VALID_ET_SUFFIX_CHARACTERS[]{
                    L'd', L'f', L'g', L'k', L'l', L'm', L'n', L'r',
                    L's', L't', L'z', L'ä', L'D', L'F', L'G', L'K',
                    L'L', L'M', L'N', L'R', L'S', L'T', L'Z', L'Ä',
                    UPPER_U_HASH, LOWER_U_HASH };
                if (stem<string_typeT>::is_one_of(text[text.length() - 3], VALID_ET_SUFFIX_CHARACTERS) &&
                    has_et_suffix(std::basic_string_view<typename string_typeT::value_type>
                                  { text.c_str(), text.length() - 2 }))
                    {
                    text.erase(text.length() - 2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            }
        //---------------------------------------------
        void step_3(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*heit*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*lich*/common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) )
                {
                if (stem<string_typeT>::delete_if_is_in_r1(text,
                    /*er*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) ||
                    stem<string_typeT>::delete_if_is_in_r1(text,
                        /*en*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                    {
                    return;
                    }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                /*keit*/common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                if (stem<string_typeT>::delete_if_is_in_r2(text,
                        /*lich*/common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                        common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ig*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_G, common_lang_constants::UPPER_G) )
                    {
                    return;
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*isch*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) )
                {
                if (text.length() >= 5 &&
                    stem<string_typeT>::get_r2() <= (text.length()-4) &&
                    stem<string_typeT>::is_neither(text[text.length()-5],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text.erase(text.length()-4);
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                /*end*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*ig*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_G, common_lang_constants::UPPER_G)  &&
                    stem<string_typeT>::is_neither(text[text.length()-3],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                /*ung*/common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*ig*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_G, common_lang_constants::UPPER_G)  &&
                    stem<string_typeT>::is_neither(text[text.length()-3],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*ig*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::get_r2() <= text.length()-2 &&
                    stem<string_typeT>::is_neither(text[text.length()-3],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*ik*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::get_r2() <= text.length()-2 &&
                    stem<string_typeT>::is_neither(text[text.length()-3],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            }

        [[nodiscard]]
        bool has_et_suffix(const auto& suffix)
            {
            if (suffix.length() >= 2)
                {
                // geordn
                if (suffix.length() >= 6 &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 6],
                        common_lang_constants::LOWER_G, common_lang_constants::LOWER_G) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 5],
                        common_lang_constants::LOWER_E, common_lang_constants::LOWER_E) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 4],
                        common_lang_constants::LOWER_O, common_lang_constants::LOWER_O) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 3],
                        common_lang_constants::LOWER_R, common_lang_constants::LOWER_R) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 2],
                        common_lang_constants::LOWER_D, common_lang_constants::LOWER_D) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 1],
                        common_lang_constants::LOWER_N, common_lang_constants::LOWER_N))
                    {
                    return false;
                    }
                // intern
                if (suffix.length() >= 6 &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 6],
                        common_lang_constants::LOWER_I, common_lang_constants::LOWER_I) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 5],
                        common_lang_constants::LOWER_N, common_lang_constants::LOWER_N) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 4],
                        common_lang_constants::LOWER_T, common_lang_constants::LOWER_T) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 3],
                        common_lang_constants::LOWER_E, common_lang_constants::LOWER_E) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 2],
                        common_lang_constants::LOWER_R, common_lang_constants::LOWER_R) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 1],
                        common_lang_constants::LOWER_N, common_lang_constants::LOWER_N))
                    {
                    return false;
                    }
                // tick
                if (suffix.length() >= 4 &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 4],
                        common_lang_constants::LOWER_T, common_lang_constants::LOWER_T) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 3],
                        common_lang_constants::LOWER_I, common_lang_constants::LOWER_I) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 2],
                        common_lang_constants::LOWER_C, common_lang_constants::LOWER_C) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 1],
                        common_lang_constants::LOWER_K, common_lang_constants::LOWER_K))
                    {
                    return false;
                    }
                // plan
                if (suffix.length() >= 4 &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 4],
                        common_lang_constants::LOWER_P, common_lang_constants::LOWER_P) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 3],
                        common_lang_constants::LOWER_L, common_lang_constants::LOWER_L) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 2],
                        common_lang_constants::LOWER_A, common_lang_constants::LOWER_A) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 1],
                        common_lang_constants::LOWER_N, common_lang_constants::LOWER_N))
                    {
                    return false;
                    }
                // tr
                if (suffix.length() >= 2 &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 2],
                        common_lang_constants::LOWER_T, common_lang_constants::LOWER_T) &&
                    stem<string_typeT>::is_either(suffix[suffix.length() - 1],
                        common_lang_constants::LOWER_R, common_lang_constants::LOWER_R))
                    {
                    return false;
                    }
                }
            return true;
            }

        bool m_transliterate_umlauts{ true };
        };
    }

/** @}*/

#endif // OLEAN_GERMAN_STEM_H
