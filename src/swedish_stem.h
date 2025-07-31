/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
     it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_SWEDISH_STEM_H
#define OLEAN_SWEDISH_STEM_H

#include "stemming.h"

namespace stemming
    {
    /**
    @brief Swedish stemmer.
    */
    //------------------------------------------------------
    template <typename string_typeT = std::wstring>
    class swedish_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Stems a Swedish word.
            @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            // reset internal data
            stem<string_typeT>::reset_r_values();

            std::transform(text.begin(), text.end(), text.begin(), full_width_to_narrow);
            stem<string_typeT>::remove_possessive_suffix(text);

            if (text.length() < 3)
                { return; }

            // see where the R1 section begins
            // R1 is the first consonant after the first vowel
            stem<string_typeT>::find_r1(text, SWEDISH_VOWELS);
            if (stem<string_typeT>::get_r1() == text.length())
                { return; }

            // R1 must have at least 3 characters in front of it
            if (stem<string_typeT>::get_r1() < 3)
                { stem<string_typeT>::set_r1(3); }
            // Swedish does not use R2

            step_1(text);
            step_2(text);
            step_3(text);
            }

        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::swedish; }
    private:
        //---------------------------------------------
        void step_1(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*heterna*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*hetens*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*arna*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*erna*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*orna*/common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ande*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*arne*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*aste*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*anden*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*heten*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*heter*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*arnas*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ernas*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ornas*/common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*arens*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*andet*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*andes*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*aren*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*erns*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ades*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*are*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ade*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*het*/common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ast*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ens*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ern*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                { return; }
            else if (delete_if_valid_et_ending(text))
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*at*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*es*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*or*/common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ad*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*as*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ar*/common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*er*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*en*/common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                { return; }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                if (text.length() >= 2 &&
                    stem<string_typeT>::is_one_of(text[text.length()-2],
                    L"bcdfghjklmnoprtvyBCDFGHJKLMNOPRTVY") )
                    {
                    text.erase(text.length()-1);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            }
        //---------------------------------------------
        void step_2(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,
                /*dd*/common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*gd*/common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*nn*/common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*dt*/common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*gt*/common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*kt*/common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*tt*/common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        //---------------------------------------------
        void step_3(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,
                /* fullt */
                common_lang_constants::LOWER_F, common_lang_constants::UPPER_F,
                common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (text.length() >= 4 &&
                (stem<string_typeT>::is_either(text[text.length() - 4],
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_U, common_lang_constants::UPPER_U) ||
                 stem<string_typeT>::is_either(text[text.length() - 4],
                     common_lang_constants::LOWER_V, common_lang_constants::UPPER_V)) &&
                stem<string_typeT>::is_suffix_in_r1(text,
                /* öst (with valid character in front of it) */
                common_lang_constants::LOWER_O_UMLAUTS, common_lang_constants::UPPER_O_UMLAUTS,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /* lig */
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /* els */
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                { return; }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /* ig */
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                { return; }
            }

        //---------------------------------------------
        [[nodiscard]]
        bool delete_if_valid_et_ending(string_typeT& text)
            {
            /* Define a valid et-ending as at least one letter followed by a vowel followed by a non-vowel,
               which is not among any of the following:

               h, iet, uit, fab, cit, dit, alit, ilit, mit, nit, pit, rit, sit, tit,
               ivit, kvit, xit, kom, rak, pak, stak */

            std::basic_string_view<typename string_typeT::value_type> textView{ text };

            const auto isValidEtEnding = [&textView]()
                {
                if (textView.empty())
                    {
                    return false;
                    }
                // suffix exceptions
                if (textView.length() >= 1 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_H, common_lang_constants::UPPER_H))
                    {
                    return false;
                    }
                else if (textView.length() >= 4 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 4],
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K))
                    {
                    return false;
                    }
                else if (textView.length() >= 4 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 4],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 4 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 4],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 4 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 4],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 4 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 4],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_X, common_lang_constants::UPPER_X) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_U, common_lang_constants::UPPER_U) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return false;
                    }
                else if (textView.length() >= 3 &&
                    stem<string_typeT>::is_either(textView[textView.length() - 3],
                        common_lang_constants::LOWER_F, common_lang_constants::UPPER_F) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 2],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(textView[textView.length() - 1],
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B))
                    {
                    return false;
                    }

                return true;
                };

            
            if (stem<string_typeT>::is_suffix_in_r1(text,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                {
                textView.remove_suffix(2);
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S))
                {
                textView.remove_suffix(3);
                }
            else
                {
                return false;
                }

            if (textView.length() < 3)
                {
                return false;
                }

            const auto lastVowel = textView.find_last_of(SWEDISH_VOWELS);
            // we need one letter, a vowel, and non-vowel in front of the 'et'
            if (lastVowel == std::basic_string_view<typename string_typeT::value_type>::npos ||
                lastVowel != textView.length() - 2)
                {
                return false;
                }
            
            if (isValidEtEnding())
                {
                text.erase(text.length() - (text.length() - textView.length()));
                stem<string_typeT>::update_r_sections(text);
                return true;
                }
            else
                {
                return false;
                }
            }
        };
    }

/** @}*/

#endif // OLEAN_SWEDISH_STEM_H
