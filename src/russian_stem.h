/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
    it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_RUSSIAN_STEM_H
#define OLEAN_RUSSIAN_STEM_H

#include "stemming.h"

namespace stemming
    {
    static const wchar_t RUSSIAN_VOWELS[] = { 0x0410, 0x0430, 0x0415, 0x0435, 0x0418, 0x0438,
                                              0x041E, 0x043E, 0x423, 0x0443, 0x042B, 0x044B,
                                              0x042D, 0x044D, 0x042E, 0x044E, 0x042F, 0x044F, 0 };

    static constexpr wchar_t RUSSIAN_A_UPPER = 0x0410;
    static constexpr wchar_t RUSSIAN_A_LOWER = 0x0430;

    static constexpr wchar_t RUSSIAN_BE_UPPER = 0x0411;
    static constexpr wchar_t RUSSIAN_BE_LOWER = 0x0431;

    static constexpr wchar_t RUSSIAN_VE_UPPER = 0x0412;
    static constexpr wchar_t RUSSIAN_VE_LOWER = 0x0432;

    static constexpr wchar_t RUSSIAN_GHE_UPPER = 0x0413;
    static constexpr wchar_t RUSSIAN_GHE_LOWER = 0x0433;

    static constexpr wchar_t RUSSIAN_DE_UPPER = 0x0414;
    static constexpr wchar_t RUSSIAN_DE_LOWER = 0x0434;

    static constexpr wchar_t RUSSIAN_IE_UPPER = 0x0415;
    static constexpr wchar_t RUSSIAN_IE_LOWER = 0x0435;

    static constexpr wchar_t RUSSIAN_ZHE_UPPER = 0x0416;
    static constexpr wchar_t RUSSIAN_ZHE_LOWER = 0x0436;

    static constexpr wchar_t RUSSIAN_ZE_UPPER = 0x0417;
    static constexpr wchar_t RUSSIAN_ZE_LOWER = 0x0437;

    static constexpr wchar_t RUSSIAN_I_UPPER = 0x0418;
    static constexpr wchar_t RUSSIAN_I_LOWER = 0x0438;

    static constexpr wchar_t RUSSIAN_SHORT_I_UPPER = 0x0419;
    static constexpr wchar_t RUSSIAN_SHORT_I_LOWER = 0x0439;

    static constexpr wchar_t RUSSIAN_KA_UPPER = 0x041A;
    static constexpr wchar_t RUSSIAN_KA_LOWER = 0x043A;

    static constexpr wchar_t RUSSIAN_EL_UPPER = 0x041B;
    static constexpr wchar_t RUSSIAN_EL_LOWER = 0x043B;

    static constexpr wchar_t RUSSIAN_EM_UPPER = 0x041C;
    static constexpr wchar_t RUSSIAN_EM_LOWER = 0x043C;

    static constexpr wchar_t RUSSIAN_EN_UPPER = 0x041D;
    static constexpr wchar_t RUSSIAN_EN_LOWER = 0x043D;

    static constexpr wchar_t RUSSIAN_O_UPPER = 0x041E;
    static constexpr wchar_t RUSSIAN_O_LOWER = 0x043E;

    static constexpr wchar_t RUSSIAN_PE_UPPER = 0x041F;
    static constexpr wchar_t RUSSIAN_PE_LOWER = 0x043F;

    static constexpr wchar_t RUSSIAN_ER_UPPER = 0x0420;
    static constexpr wchar_t RUSSIAN_ER_LOWER = 0x0440;

    static constexpr wchar_t RUSSIAN_ES_UPPER = 0x0421;
    static constexpr wchar_t RUSSIAN_ES_LOWER = 0x0441;

    static constexpr wchar_t RUSSIAN_TE_UPPER = 0x0422;
    static constexpr wchar_t RUSSIAN_TE_LOWER = 0x0442;

    static constexpr wchar_t RUSSIAN_U_UPPER = 0x0423;
    static constexpr wchar_t RUSSIAN_U_LOWER = 0x0443;

    static constexpr wchar_t RUSSIAN_EF_UPPER = 0x0424;
    static constexpr wchar_t RUSSIAN_EF_LOWER = 0x0444;

    static constexpr wchar_t RUSSIAN_HA_UPPER = 0x0425;
    static constexpr wchar_t RUSSIAN_HA_LOWER = 0x0445;

    static constexpr wchar_t RUSSIAN_TSE_UPPER = 0x0426;
    static constexpr wchar_t RUSSIAN_TSE_LOWER = 0x0446;

    static constexpr wchar_t RUSSIAN_CHE_UPPER = 0x0427;
    static constexpr wchar_t RUSSIAN_CHE_LOWER = 0x0447;

    static constexpr wchar_t RUSSIAN_SHA_UPPER = 0x0428;
    static constexpr wchar_t RUSSIAN_SHA_LOWER = 0x0448;

    static constexpr wchar_t RUSSIAN_SHCHA_UPPER = 0x0429;
    static constexpr wchar_t RUSSIAN_SHCHA_LOWER = 0x0449;

    static constexpr wchar_t RUSSIAN_HARD_SIGN_UPPER = 0x042A;
    static constexpr wchar_t RUSSIAN_HARD_SIGN_LOWER = 0x044A;

    static constexpr wchar_t RUSSIAN_YERU_UPPER = 0x042B;
    static constexpr wchar_t RUSSIAN_YERU_LOWER = 0x044B;

    static constexpr wchar_t RUSSIAN_SOFT_SIGN_UPPER = 0x042C;
    static constexpr wchar_t RUSSIAN_SOFT_SIGN_LOWER = 0x044C;

    static constexpr wchar_t RUSSIAN_E_UPPER = 0x042D;
    static constexpr wchar_t RUSSIAN_E_LOWER = 0x044D;

    static constexpr wchar_t RUSSIAN_YU_UPPER = 0x042E;
    static constexpr wchar_t RUSSIAN_YU_LOWER = 0x044E;

    static constexpr wchar_t RUSSIAN_YA_UPPER = 0x042F;
    static constexpr wchar_t RUSSIAN_YA_LOWER = 0x044F;

    /**
        @brief Russian stemmer.
    */
    template <typename string_typeT = std::wstring>
    class russian_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Stems a Russian word.
            @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            if (text.length() < 2)
                { return; }

            std::transform(text.cbegin(), text.cend(), text.begin(), full_width_to_narrow);
            // change 33rd letter ('&#x0451;') to '&#x0435;'
            std::transform(text.cbegin(), text.cend(), text.begin(),
                [](auto& ch) noexcept
                {
                return (ch == 0x0451 ? RUSSIAN_IE_LOWER :
                        ch == 0x0401 ? RUSSIAN_IE_UPPER:
                        ch);
                });

            // reset internal data
            stem<string_typeT>::reset_r_values();

            stem<string_typeT>::find_r1(text, RUSSIAN_VOWELS);
            stem<string_typeT>::find_r2(text, RUSSIAN_VOWELS);
            stem<string_typeT>::find_russian_rv(text, RUSSIAN_VOWELS);

            step_1(text);
            step_2(text);
            step_3(text);
            step_4(text);
            }
        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::russian; }
    private:
        void step_1(string_typeT& text)
            {
            // search for a perfect gerund
            // group 2
            if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                                   RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                   RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                   RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                   RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                   RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                   RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                   RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                   RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                   RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                   RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) )
                { return; }
            // group 1
            else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                        RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                        RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                        RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                        RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) )
                {
                if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                    RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                    RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) )
                    {
                    text.erase(text.end()-5, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }
            // group 2
            else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                        RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                        RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                     stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                        RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                        RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) )
                { return; }
            // group 1
            else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                        RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                        RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) )
                {
                if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
                                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) )
                    {
                    text.erase(text.end()-3, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }
            // group 2
            else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) )
                { return; }
            // group 1
            else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER) )
                {
                if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER) )
                    {
                    text.erase(text.end()-1, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }
            // reflexive
            if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) )
                { /*NOOP*/ }
            // adjectival
            if (stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_UPPER, RUSSIAN_YERU_LOWER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_GHE_LOWER, RUSSIAN_GHE_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_GHE_LOWER, RUSSIAN_GHE_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) )
                {
                // delete participles
                // group 2
                if (stem<string_typeT>::delete_if_is_in_rv(text,
                        RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, false) ||
                    stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, false) ||
                    stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                        RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER, false) )
                    { /*NOOP*/ }
                // group 1
                else if (
                    stem<string_typeT>::is_suffix_in_rv(text,
                        RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text,
                        RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text,
                        RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER) ||
                    stem<string_typeT>::is_suffix_in_rv(text,
                        RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER) )
                    {
                    if (text.length() >= 3 &&
                        stem<string_typeT>::get_rv() <= text.length()-3 &&
                        (stem<string_typeT>::is_either(text[text.length()-3], RUSSIAN_A_LOWER,
                            RUSSIAN_A_UPPER) ||
                        stem<string_typeT>::is_either(text[text.length()-3], RUSSIAN_YA_LOWER,
                            RUSSIAN_YA_UPPER)) )
                        {
                        text.erase(text.end()-2, text.end() );
                        stem<string_typeT>::update_r_sections(text);
                        return;
                        }
                    }
                else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER) )
                    {
                    if (text.length() >= 2 &&
                        stem<string_typeT>::get_rv() <= text.length()-2 &&
                        (stem<string_typeT>::is_either(text[text.length()-2], RUSSIAN_A_LOWER,
                            RUSSIAN_A_UPPER) ||
                        stem<string_typeT>::is_either(text[text.length()-2], RUSSIAN_YA_LOWER,
                            RUSSIAN_YA_UPPER)) )
                        {
                        text.erase(text.end()-1, text.end() );
                        stem<string_typeT>::update_r_sections(text);
                        return;
                        }
                    }
                return;
                }
            // verb
            // group 2
            else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||/*4*/
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER,
                    RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) )
                {
                return;
                }
            // group 1
            if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHORT_I_LOWER,
                    RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER,
                    RUSSIAN_IE_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, RUSSIAN_SOFT_SIGN_LOWER,
                    RUSSIAN_SOFT_SIGN_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                    RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER) )
                {
                if (text.length() >= 4 &&
                    stem<string_typeT>::get_rv() <= text.length()-4 &&
                    (stem<string_typeT>::is_either(text[text.length()-4], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
                    stem<string_typeT>::is_either(text[text.length()-4], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)) )
                    {
                    text.erase(text.end()-3, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }
            // group 2
            else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) )
                {
                return;
                }
            // group 1
            else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER,
                    RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                    RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) )
                {
                if (text.length() >= 3 &&
                    stem<string_typeT>::get_rv() <= text.length()-3 &&
                    (stem<string_typeT>::is_either(text[text.length()-3], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
                    stem<string_typeT>::is_either(text[text.length()-3], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)) )
                    {
                    text.erase(text.end()-2, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }
            if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHORT_I_LOWER,
                                                    RUSSIAN_SHORT_I_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER) ||
                stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER) )
                {
                if (text.length() >= 2 &&
                    stem<string_typeT>::get_rv() <= text.length()-2 &&
                    (stem<string_typeT>::is_either(text[text.length()-2], RUSSIAN_A_LOWER,
                        RUSSIAN_A_UPPER) ||
                    stem<string_typeT>::is_either(text[text.length()-2], RUSSIAN_YA_LOWER,
                        RUSSIAN_YA_UPPER)) )
                    {
                    text.erase(text.end()-1, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    return;
                    }
                }

            // noun
            if (stem<string_typeT>::delete_if_is_in_rv(
                text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
                    RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
                    RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) )
                { return; }
            }
        void step_2(string_typeT& text)
            { stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_UPPER, RUSSIAN_I_LOWER); }
        void step_3(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                                   RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                   RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
                                   RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                                   RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                   RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
                                   RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER);
                }
            else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                                RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
                                   RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
                                   RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER);
                }
            }
        void step_4(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                                RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER) )
                {
                text.erase(text.end()-1, text.end() );
                stem<string_typeT>::update_r_sections(text);
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                                          RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER,
                                          RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
                                          RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER) ||
                stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
                                          RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER,
                                          RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER))
                {
                if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
                                RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER) )
                    {
                    text.erase(text.end()-1, text.end() );
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            else
                { stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER,
                    RUSSIAN_SOFT_SIGN_UPPER); }
            }
        };
    }

/** @}*/

#endif // OLEAN_RUSSIAN_STEM_H
