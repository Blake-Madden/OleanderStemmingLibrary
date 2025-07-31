/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
     it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_FINNISH_STEM_H
#define OLEAN_FINNISH_STEM_H

#include "stemming.h"

namespace stemming
    {
    /**
    @brief Finnish stemmer.
    */
    //------------------------------------------------------
    template <typename string_typeT = std::wstring>
    class finnish_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Stems a Finnish word.
            @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            // reset internal data
            m_step_3_successful = false;
            stem<string_typeT>::reset_r_values();

            std::transform(text.begin(), text.end(), text.begin(), full_width_to_narrow);
            stem<string_typeT>::remove_possessive_suffix(text);

            if (text.length() < 2)
                { return; }

            stem<string_typeT>::find_r1(text, FINNISH_VOWELS);
            stem<string_typeT>::find_r2(text, FINNISH_VOWELS);

            step_1(text);
            step_2(text);
            step_3(text);
            step_4(text);
            step_5(text);
            step_6(text);
            }
        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::finnish; }
    private:
        //---------------------------------------------
        void step_1(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*kaan*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*kään*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                if (text.length() >= 5 &&
                    stem<string_typeT>::is_one_of(text[text.length()-5], FINNISH_STEP_1_SUFFIX) )
                    {
                    text.erase(text.length()-4);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*kin*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*han*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hän*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                if (text.length() >= 4 &&
                    stem<string_typeT>::is_one_of(text[text.length()-4], FINNISH_STEP_1_SUFFIX) )
                    {
                    text.erase(text.length()-3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*sti*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*sti*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I);
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*ko*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*kö*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_O_UMLAUTS, common_lang_constants::UPPER_O_UMLAUTS) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*pa*/
                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*pä*/
                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                    common_lang_constants:: LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::is_one_of(text[text.length()-3], FINNISH_STEP_1_SUFFIX) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            }
        //---------------------------------------------
        void step_2(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r1(text,
                    /*nsa*/
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*nsä*/
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*mme*/
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*nne*/
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*si*/
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (text.length() >= 3 &&
                    !(text[text.length()-3] == common_lang_constants::LOWER_K ||
                      text[text.length()-3] == common_lang_constants::UPPER_K))
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ni*/
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                if (stem<string_typeT>::is_suffix(text,
                    /*kse*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                    {
                    text[text.length()-1] = common_lang_constants::LOWER_I;
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*an*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                if ((text.length() >= 4 &&
                    (stem<string_typeT>::is_partial_suffix(text, (text.length()-4),
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-4),
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A)) ) ||
                    (text.length() >= 5 &&
                    (stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ) ) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*än*/
                common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                if ((text.length() >= 4 &&
                    (stem<string_typeT>::is_partial_suffix(text, (text.length()-4),
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-4),
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS)) ) ||
                    (text.length() >= 5 &&
                    (stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ) ) )
                    {
                    text.erase(text.length()-2);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*en*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) )
                {
                if (text.length() >= 5 &&
                    (stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                    stem<string_typeT>::is_partial_suffix(text, (text.length()-5),
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ) )
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
            // seen followed by LV
            if (text.length() >= 6 &&
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*seen*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                stem<string_typeT>::is_one_of(text[text.length()-5], FINNISH_VOWELS_NO_Y) &&
                stem<string_typeT>::tolower_western(text[text.length()-5]) ==
                    stem<string_typeT>::tolower_western(text[text.length()-6]) )
                {
                text.erase(text.length()-4);
                stem<string_typeT>::update_r_sections(text);
                m_step_3_successful = true;
                return;
                }
            // suffix followed by Vi
            else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length()-5],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    (stem<string_typeT>::is_suffix_in_r1(text,
                        /*siin*/
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                    stem<string_typeT>::is_suffix_in_r1(text,
                        /*tten*/
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ) &&
                    stem<string_typeT>::is_one_of(text[text.length()-6], FINNISH_VOWELS_NO_Y) )
                {
                text.erase(text.length()-4);
                stem<string_typeT>::update_r_sections(text);
                m_step_3_successful = true;
                return;
                }
            // suffix followed by Vi
            else if (text.length() >= 5 &&
                    stem<string_typeT>::is_either(text[text.length()-4],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_suffix_in_r1(text,
                        /*den*/
                        common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_one_of(text[text.length()-5], FINNISH_VOWELS_NO_Y) )
                {
                text.erase(text.length()-3);
                stem<string_typeT>::update_r_sections(text);
                m_step_3_successful = true;
                return;
                }
            else if (
                (stem<string_typeT>::is_suffix_in_r1(text,
                    /*tta*/
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*ttä*/
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS)) &&
                stem<string_typeT>::is_either(text[text.length()-4],
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                text.erase(text.length()-3);
                stem<string_typeT>::update_r_sections(text);
                m_step_3_successful = true;
                return;
                }
            // ends if VHVN
            else if (
                (stem<string_typeT>::is_suffix_in_r1(text,
                    /*han*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hen*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hin*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hon*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hän*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*hön*/
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_O_UMLAUTS, common_lang_constants::UPPER_O_UMLAUTS,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) ) )
                {
                if (stem<string_typeT>::tolower_western(text[text.length()-2]) ==
                        stem<string_typeT>::tolower_western(text[text.length()-4]) )
                    {
                    text.erase(text.length()-3);
                    stem<string_typeT>::update_r_sections(text);
                    m_step_3_successful = true;
                    }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ssa*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ssä*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*sta*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*stä*/
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*lla*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*llä*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*lta*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ltä*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*lle*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ksi*/
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ine*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*na*/
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*nä*/
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) )
                {
                m_step_3_successful = true;
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                    /*ta*/
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r1(text,
                    /*tä*/
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) )
                {
                m_step_3_successful = true;
                return;
                }
            // suffix followed by cv
            else if (text.length() >= 3 &&
                    (stem<string_typeT>::is_suffix_in_r1(text, common_lang_constants::LOWER_A,
                                                         common_lang_constants::UPPER_A) ||
                        stem<string_typeT>::is_suffix_in_r1(text, common_lang_constants::LOWER_A_UMLAUTS,
                                                            common_lang_constants::UPPER_A_UMLAUTS) ) &&
                    !stem<string_typeT>::is_one_of(text[text.length()-3], FINNISH_VOWELS) &&
                    stem<string_typeT>::is_one_of(text[text.length()-2], FINNISH_VOWELS) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                m_step_3_successful = true;
                return;
                }
            // suffix followed by LV or ie
            else if (stem<string_typeT>::is_suffix_in_r1(text, common_lang_constants::LOWER_N,
                                                         common_lang_constants::UPPER_N) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                if (text.length() >= 2 &&
                    ((stem<string_typeT>::is_one_of(text[text.length()-1], FINNISH_VOWELS_NO_Y) &&
                      stem<string_typeT>::tolower_western(text[text.length()-1]) ==
                        stem<string_typeT>::tolower_western(text[text.length()-2])) ||
                     stem<string_typeT>::is_suffix_in_r1(text,
                         /*ie*/
                         common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                         common_lang_constants::LOWER_E, common_lang_constants::UPPER_E)) )
                    {
                    text.erase(text.length()-1);
                    stem<string_typeT>::update_r_sections(text);
                    }
                m_step_3_successful = true;
                return;
                }
            }
        //---------------------------------------------
        void step_4(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*impi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*impa*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*impä*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*immi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*imma*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*immä*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*eja*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_J, common_lang_constants::UPPER_J,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ejä*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_J, common_lang_constants::UPPER_J,
                    common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS, false) )
                {
                return;
                }
            else if (text.length() >= 5 &&
                    (stem<string_typeT>::is_suffix_in_r2(text,
                        /*mpi*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*mpa*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*mpä*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ||
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*mmi*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*mma*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                    stem<string_typeT>::is_suffix_in_r2(text,
                        /*mmä*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_A_UMLAUTS, common_lang_constants::UPPER_A_UMLAUTS) ) )
                {
                if (!(stem<string_typeT>::is_either(text[text.length()-5],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) &&
                    stem<string_typeT>::is_either(text[text.length()-4],
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ) )
                    {
                    text.erase(text.length()-3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            return;
            }
        //---------------------------------------------
        void step_5(string_typeT& text)
            {
            // if step 3 was successful in removing a suffix
            if (m_step_3_successful)
                {
                if (stem<string_typeT>::delete_if_is_in_r1(text,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                    stem<string_typeT>::delete_if_is_in_r1(text,
                        common_lang_constants::LOWER_J, common_lang_constants::UPPER_J) )
                    {
                    // NOOP
                    }
                }
            else
                {
                if (text.length() >= 2 &&
                    stem<string_typeT>::is_one_of(text[text.length()-2], FINNISH_VOWELS) )
                    {
                    if (stem<string_typeT>::delete_if_is_in_r1(text,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                        {
                        if (!stem<string_typeT>::delete_if_is_in_r2(text,
                            /*imma*/
                            common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                            common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                            common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                            common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                            {
                            if (text.length() >= 5 &&
                                stem<string_typeT>::is_suffix_in_r2(text,
                                    /*mma*/
                                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                                // isn't proceeded by "po"
                                !(stem<string_typeT>::is_either(text[text.length()-5],
                                    common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) &&
                                  stem<string_typeT>::is_either(text[text.length()-4],
                                      common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ) )
                                {
                                text.erase(text.length()-3);
                                stem<string_typeT>::update_r_sections(text);
                                }
                            }
                        }
                    }
                }
            }
        //---------------------------------------------
        void step_6(string_typeT& text)
            {
            step_6a(text);
            step_6b(text);
            step_6c(text);
            step_6d(text);
            step_6e(text);
            }
        //---------------------------------------------
        void step_6a(string_typeT& text)
            {
            if (text.length() >= 2 &&
                stem<string_typeT>::get_r1() <= text.length()-2 &&
                stem<string_typeT>::is_one_of(text[text.length()-1], FINNISH_VOWELS_NO_Y) &&
                stem<string_typeT>::tolower_western(text[text.length()-1]) ==
                    stem<string_typeT>::tolower_western(text[text.length()-2]))
                {
                text.erase(text.end()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        //---------------------------------------------
        void step_6b(string_typeT& text)
            {
            if (text.length() >= 2 &&
                stem<string_typeT>::get_r1() <= text.length()-2 &&
                stem<string_typeT>::is_one_of(text[text.length()-2], FINNISH_CONSONANTS) &&
                stem<string_typeT>::is_one_of(text[text.length()-1], FINNISH_VOWELS_SIMPLE) )
                {
                text.erase(text.end()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        //---------------------------------------------
        void step_6c(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,
                    /*oj*/
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_J, common_lang_constants::UPPER_J) ||
                stem<string_typeT>::is_suffix_in_r1(text,
                    /*uj*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_J, common_lang_constants::UPPER_J) )
                {
                text.erase(text.end()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        //---------------------------------------------
        void step_6d(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,/*jo*/common_lang_constants::LOWER_J,
                common_lang_constants::UPPER_J, common_lang_constants::LOWER_O,
                common_lang_constants::UPPER_O) )
                {
                text.erase(text.end()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        //---------------------------------------------
        void step_6e(string_typeT& text)
            {
            // find the last consonant
            const size_t index = text.find_last_not_of(FINNISH_VOWELS);
            if (index == string_typeT::npos ||
                index < 1)
                { return; }
            if (stem<string_typeT>::is_one_of(text[index], FINNISH_CONSONANTS) &&
                stem<string_typeT>::tolower_western(text[index]) ==
                    stem<string_typeT>::tolower_western(text[index-1]))
                {
                text.erase(index, 1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        // internal data specific to Finnish stemmer
        bool m_step_3_successful{ false };
        };
    }

/** @}*/

#endif // OLEAN_FINNISH_STEM_H
