/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2023
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
    it under the terms of the BSD License.
* @{*/

#ifndef __GERMAN_STEM_H__
#define __GERMAN_STEM_H__

#include "stemming.h"

namespace stemming
    {
    /**
    @brief German stemmer.

    @par Definitions:

    German includes the following accented forms,
    -ä ö ü and a special letter, ß, equivalent to double s.

    The following letters are vowels:
    -a e i o u y ä ö ü

    @par Algorithm:

    <b>Step 0:</b>

    - Replace ß with ss, ae with ä, oe with ö, ue with ü (unless preceded by q).

        The rules here for ae, oe and ue were
        added in Snowball 2.3.0, but were previously present as a variant of the
        algorithm termed "german2." The condition on the replacement of ue prevents
        the unwanted changing of quelle. Also note that feuer is not modified
        because the first part of the rule changes it to feUer, so ue is not found.

    <b>Step 1:</b>

    Search for the longest among the following suffixes:
        a.) em (not preceded by 'syst')
        b.) ern er
        c.) en es e
        d.) s (preceded by a valid s-ending)
    and delete if in R1. (Of course the letter of the valid s-ending is not necessarily in R1).
    If an ending of group (c) is deleted, and the ending is preceded by 'niss', delete the final s.

    (For example, äckern -> äck, ackers -> acker, armes -> arm, bedürfnissen -> bedürfnis).

    <b>Step 2:</b>

    Search for the longest among the following suffixes:
        - en er est
        - st (preceded by a valid st-ending, itself preceded by at least 3 letters)
    and delete if in R1.

    (For example, derbsten -> derbst by step 1, and derbst -> derb by step 2,
    because b is a valid st-ending, and is preceded by just 3 letters).

    <b>Step 3:</b>

    Search for the longest among the following suffixes, and perform the action indicated.
        - end ung
            - Delete if in R2
            - If preceded by ig, delete if in R2 and not preceded by e

        - ig ik isch
            - Delete if in R2 and not preceded by e

        - lich heit
            - Delete if in R2
            - If preceded by er or en, delete if in R1

        - keit
            - Delete if in R2
            - If preceded by lich or ig, delete if in R2
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
            bool stepBSucessfull{ false };
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
                /*ern*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
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
                /*es*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                stepBSucessfull = true;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*en*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                stepBSucessfull = true;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                stepBSucessfull = true;
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

            if (stepBSucessfull && text.length() > 4 &&
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
                        /*st*/common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                if (stem<string_typeT>::is_one_of(text[text.length()-3], L"bdfghklmntBDFGHKLMNT") )
                    {
                    text.erase(text.length()-2);
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
        bool m_transliterate_umlauts{ true };
        };
    }

/** @}*/

#endif // __GERMAN_STEM_H__
