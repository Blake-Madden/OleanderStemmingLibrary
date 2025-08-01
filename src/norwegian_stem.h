/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
    it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_NORWEGIAN_STEM_H
#define OLEAN_NORWEGIAN_STEM_H

#include "stemming.h"

namespace stemming
    {
    /**
        @brief Norwegian stemmer.
    */
    //------------------------------------------------------
    template <typename string_typeT = std::wstring>
    class norwegian_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Stems a Norwegian word.
            @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            // reset internal data
            stem<string_typeT>::reset_r_values();

            std::transform(text.begin(), text.end(), text.begin(), full_width_to_narrow);
            stem<string_typeT>::remove_possessive_suffix(text);

            if (text.length() < 3)
                { return; }

            stem<string_typeT>::find_r1(text, NORWEGIAN_VOWELS);
            if (stem<string_typeT>::get_r1() == text.length() )
                { return; }
            // R1 must have at least 3 characters in front of it
            if (stem<string_typeT>::get_r1() < 3)
                { stem<string_typeT>::set_r1(3); }
            // Norwegian does not use R2

            step_1(text);
            step_2(text);
            step_3(text);
            }

        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::norwegian; }
    private:
        //---------------------------------------------
        void step_1(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*hetenes*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*hetene*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*hetens*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*heter*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*heten*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*endes*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ande*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ende*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*edes*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*enes*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*erte*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                text.erase(text.length()-2);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*ers*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S))
                {
                if (text.length() >= 7 &&
                    stem<string_typeT>::is_either(text[text.length() - 7],
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P))
                    {
                    text.erase(text.length() - 3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_G, common_lang_constants::UPPER_G) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V))
                    {
                    text.erase(text.length() - 3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V))
                    {
                    text.erase(text.length() - 3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_D, common_lang_constants::UPPER_D))
                    {
                    return;
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P))
                    {
                    return;
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return;
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_O_STROKE, common_lang_constants::UPPER_O_STROKE) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return;
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M))
                    {
                    return;
                    }
                else if (text.length() >= 6 &&
                    stem<string_typeT>::is_either(text[text.length() - 6],
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M))
                    {
                    return;
                    }
                else if (text.length() >= 5 &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T))
                    {
                    return;
                    }
                else if (text.length() >= 5 &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_K, common_lang_constants::UPPER_K))
                    {
                    return;
                    }
                else if (text.length() >= 5 &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                    common_lang_constants::LOWER_K, common_lang_constants::UPPER_K))
                    {
                    return;
                    }
                else if (text.length() >= 5 &&
                    stem<string_typeT>::is_either(text[text.length() - 5],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P) &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_P, common_lang_constants::UPPER_P))
                    {
                    return;
                    }
                else if (text.length() >= 4 &&
                    stem<string_typeT>::is_either(text[text.length() - 4],
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V))
                    {
                    return;
                    }
                else
                    {
                    text.erase(text.length() - 3);
                    stem<string_typeT>::update_r_sections(text);
                    }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ets*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*het*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ast*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ens*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ene*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ane*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ede*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*ert*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*et*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*es*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*as*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ar*/
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*er*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*en*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                {
                if (stem<string_typeT>::get_r1() <= text.length()-1)
                    {
                    // only delete if a valid "s" ending
                    if (text.length() >= 2 &&
                        stem<string_typeT>::is_one_of(text[text.length()-2],
                        L"bcdfghjlmnoptvyzBCDFGHJLMNOPTVYZ") )
                        {
                        text.erase(text.length()-1);
                        stem<string_typeT>::update_r_sections(text);
                        return;
                        }
                    else if (text.length() >= 3 &&
                        stem<string_typeT>::is_either(text[text.length()-2],
                            common_lang_constants::LOWER_K, common_lang_constants::UPPER_K) &&
                        !stem<string_typeT>::is_one_of(text[text.length()-3], NORWEGIAN_VOWELS))
                        {
                        text.erase(text.length()-1);
                        stem<string_typeT>::update_r_sections(text);
                        return;
                        }
                    else if (text.length() >= 3 &&
                        stem<string_typeT>::is_either(text[text.length()-2],
                            common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) &&
                        stem<string_typeT>::is_neither(text[text.length() - 3],
                            common_lang_constants::LOWER_E, common_lang_constants::UPPER_E))
                        {
                        text.erase(text.length()-1);
                        stem<string_typeT>::update_r_sections(text);
                        return;
                        }
                    }
                }
            }

        //---------------------------------------------
        void step_2(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_r1(text,
                /*dt*/
                common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::is_suffix_in_r1(text,
                /*vt*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            }
        //---------------------------------------------
        void step_3(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*hetslov*/
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*slov*/
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*elov*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*elig*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*eleg*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*lov*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*els*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*lig*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*eig*/
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*leg*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                /*ig*/
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G, false) )
                {
                return;
                }
            }
        };
    }

/** @}*/

#endif // OLEAN_NORWEGIAN_STEM_H
