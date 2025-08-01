/** @addtogroup Stemming
    @brief Library for stemming words down to their root words.
    @date 2004-2025
    @copyright Oleander Software, Ltd.
    @author Blake Madden
    @details This program is free software; you can redistribute it and/or modify
    it under the terms of the BSD License.

    SPDX-License-Identifier: BSD-3-Clause
* @{*/

#ifndef OLEAN_ITALIAN_STEM_H
#define OLEAN_ITALIAN_STEM_H

#include "stemming.h"

namespace stemming
    {
    /**
        @brief Italian stemmer.
    */
    //------------------------------------------------------
    template <typename string_typeT = std::wstring>
    class italian_stem final : public stem<string_typeT>
        {
    public:
        /** @brief Stems an Italian word.
            @param[in,out] text string to stem.*/
        void operator()(string_typeT& text) final
            {
            // reset internal data
            stem<string_typeT>::reset_r_values();

            if (is_exception(text))
                { return; }

            std::transform(text.begin(), text.end(), text.begin(), full_width_to_narrow);
            stem<string_typeT>::remove_possessive_suffix(text);
            stem<string_typeT>::italian_acutes_to_graves(text);
            if (text.length() < 3)
                { return; }
            stem<string_typeT>::hash_italian_ui(text, ITALIAN_VOWELS);

            stem<string_typeT>::find_r1(text, ITALIAN_VOWELS);
            stem<string_typeT>::find_r2(text, ITALIAN_VOWELS);
            stem<string_typeT>::find_spanish_rv(text, ITALIAN_VOWELS);

            step_0(text);

            const size_t text_length = text.length();
            step_1(text);

            // step 2 is called only if step 1 did not remove a suffix
            if (text_length == text.length() )
                { step_2(text); }

            step_3a(text);
            step_3b(text);

            stem<string_typeT>::unhash_italian_ui(text);
            }
        /// @returns The stemmer's language.
        [[nodiscard]]
        stemming_type get_language() const noexcept final
            { return stemming_type::italian; }
    private:
        //---------------------------------------------
        [[nodiscard]]
        bool is_exception(string_typeT& text)
            {
            if (text.length() == 6 &&
                stem<string_typeT>::is_suffix(text,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O))
                {
                text = L"divan";
                return true;
                }
            return false;
            }
        //---------------------------------------------
        void step_0(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix(text,
                /*gliela*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 6) || step_0b(text, 6) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*gliele*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 6) || step_0b(text, 6) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*glieli*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 6) || step_0b(text, 6) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*glielo*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 6) || step_0b(text, 6) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*gliene*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 6) || step_0b(text, 6) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*sene*/
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*mela*/
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*mele*/
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*meli*/
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*melo*/
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*mene*/
                common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*tela*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*tele*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*teli*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*telo*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*tene*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*cela*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*cela*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*celi*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*celo*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*cene*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*vela*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*vele*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*veli*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*velo*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*vene*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 4) || step_0b(text, 4) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*gli*/
                common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 3) || step_0b(text, 3) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*ci*/
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*la*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*le*/
                common_lang_constants::LOWER_L,
                common_lang_constants::UPPER_L, common_lang_constants::LOWER_E,
                common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*li*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*lo*/
                common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*mi*/
                common_lang_constants::LOWER_M,
                common_lang_constants::UPPER_M, common_lang_constants::LOWER_I,
                common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*ne*/
                common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*si*/
                common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*ti*/
                common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::is_suffix(text,
                /*vi*/
                common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                if (step_0a(text, 2) || step_0b(text, 2) ) { /*NOOP*/ }
                return;
                }
            }
        //---------------------------------------------
        bool step_0a(string_typeT& text, size_t suffix_length)
            {
            if (text.length() >= (suffix_length+4) &&
                stem<string_typeT>::get_rv() <= text.length()-(4+suffix_length) &&
                (/*ando*/
                (stem<string_typeT>::is_either(text[text.length()-(4+suffix_length)],
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                    stem<string_typeT>::is_either(text[text.length()-(3+suffix_length)],
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_either(text[text.length()-(2+suffix_length)],
                        common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) &&
                    stem<string_typeT>::is_either(text[text.length()-(1+suffix_length)],
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ) ||
                /*endo*/
                (stem<string_typeT>::is_either(text[text.length()-(4+suffix_length)],
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) &&
                    stem<string_typeT>::is_either(text[text.length()-(3+suffix_length)],
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N) &&
                    stem<string_typeT>::is_either(text[text.length()-(2+suffix_length)],
                        common_lang_constants::LOWER_D, common_lang_constants::UPPER_D) &&
                    stem<string_typeT>::is_either(text[text.length()-(1+suffix_length)],
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ) ) )
                {
                text.erase(text.length()-suffix_length);
                stem<string_typeT>::update_r_sections(text);
                return true;
                }
            return false;
            }
        //---------------------------------------------
        bool step_0b(string_typeT& text, size_t suffix_length)
            {
            if ((text.length() >= suffix_length+2) &&
                stem<string_typeT>::get_rv() <= (text.length()-(2+suffix_length)) &&
                (
                /*ar*/
                (stem<string_typeT>::is_either(text[text.length()-(2+suffix_length)],
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) &&
                stem<string_typeT>::is_either(text[text.length()-1-suffix_length],
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) ) ||
                /*er*/
                (stem<string_typeT>::is_either(text[text.length()-(2+suffix_length)],
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) &&
                stem<string_typeT>::is_either(text[text.length()-1-suffix_length],
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) ) ||
                /*or*/
                (stem<string_typeT>::is_either(text[text.length()-(2+suffix_length)],
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) &&
                stem<string_typeT>::is_either(text[text.length()-1-suffix_length],
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R) )
                ) )
                {
                text.replace(text.end()-suffix_length, text.end(), L"e");
                stem<string_typeT>::update_r_sections(text);
                return true;
                }
            return false;
            }
        //---------------------------------------------
        void step_1(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*amento*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    /*amenti*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    /*imento*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ||
                stem<string_typeT>::delete_if_is_in_rv(text,
                    /*imenti*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*azione*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text,
                /*ic*/
                common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                common_lang_constants::LOWER_C, common_lang_constants::UPPER_C);
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*azioni*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ic*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C);
                return;
                }
            else if (
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*uzione*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*uzioni*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*usione*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*usioni*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                text.erase(text.length()-5);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r1(text,
                    /*amente*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*iv*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V) )
                    {
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*at*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T);
                    }
                else if (
                    stem<string_typeT>::delete_if_is_in_r2(text,
                    /*abil*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ic*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*os*/
                        common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                        common_lang_constants::LOWER_S, common_lang_constants::UPPER_S) )
                    { /*NOOP*/ }
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                        /*atrice*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*atrici*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                        /*abile*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*abili*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ibile*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ibili*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*mente*/
                        common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                        common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                        common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                        common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*atore*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ic*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C);
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*atori*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ic*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C);
                return;
                }
            else if (
                stem<string_typeT>::is_suffix_in_r2(text,
                /*logia*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*logie*/
                    common_lang_constants::LOWER_L, common_lang_constants::UPPER_L,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                text.erase(text.length()-2);
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*enza*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::is_suffix_in_r2(text,
                    /*enze*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                text.replace(text.end()-2, text.end(), L"te");
                stem<string_typeT>::update_r_sections(text);
                return;
                }
            else if (
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ante*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*anti*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*anza*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*anze*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_Z, common_lang_constants::UPPER_Z,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*iche*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ichi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ismo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ismi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ista*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*iste*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*isti*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*istà*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_GRAVE, common_lang_constants::UPPER_A_GRAVE) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*istè*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E_GRAVE, common_lang_constants::UPPER_E_GRAVE) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*istì*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I_GRAVE, common_lang_constants::UPPER_I_GRAVE) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ico*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ici*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ica*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ice*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*oso*/
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*osi*/
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*osa*/
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ose*/
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ità*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A_GRAVE, common_lang_constants::UPPER_A_GRAVE) )
                {
                if (stem<string_typeT>::delete_if_is_in_r2(text,
                        /*abil*/
                        common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                        common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_L, common_lang_constants::UPPER_L) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ic*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C) ||
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*iv*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_V, common_lang_constants::UPPER_V) )
                    { /*NOOP*/ }
                return;
                }
            else if (
                stem<string_typeT>::delete_if_is_in_r2(text,
                /*ivo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ivi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*iva*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A) ||
                stem<string_typeT>::delete_if_is_in_r2(text,
                    /*ive*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E) )
                {
                if (stem<string_typeT>::delete_if_is_in_r2(text,
                    /*at*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T) )
                    {
                    stem<string_typeT>::delete_if_is_in_r2(text,
                        /*ic*/
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                        common_lang_constants::LOWER_C, common_lang_constants::UPPER_C);
                    }
                return;
                }
            }
        //---------------------------------------------
        void step_2(string_typeT& text)
            {
            if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erebbero*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irebbero*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*assero*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*assimo*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*eranno*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erebbe*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*eremmo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ereste*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*eresti*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*essero*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iranno*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irebbe*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_B, common_lang_constants::UPPER_B,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iremmo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ireste*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iresti*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iscano*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iscono*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*issero*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*arono*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*avamo*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*avano*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*avate*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*eremo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erete*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erono*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*evamo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*evano*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*evate*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iremo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irete*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irono*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ivamo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ivano*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ivate*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ammo*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ando*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*asse*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*assi*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*emmo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*enda*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ende*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*endi*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*endo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_D, common_lang_constants::UPPER_D,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erai*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erei*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*yamo*/
                    common_lang_constants::LOWER_Y, common_lang_constants::UPPER_Y,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iamo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*immo*/common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_M, common_lang_constants::UPPER_M,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irai*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irei*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*isca*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*isce*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*isci*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*isco*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_S, common_lang_constants::UPPER_S,
                    common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ano*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*are*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ata*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ate*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ati*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ato*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ava*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*avi*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*avo*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erà*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A_GRAVE, common_lang_constants::UPPER_A_GRAVE, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ere*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*erò*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O_GRAVE, common_lang_constants::UPPER_O_GRAVE, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ete*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*eva*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*evi*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*evo*/
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irà*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_A_GRAVE, common_lang_constants::UPPER_A_GRAVE, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ire*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*irò*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R,
                    common_lang_constants::LOWER_O_GRAVE, common_lang_constants::UPPER_O_GRAVE, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ita*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ite*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iti*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ito*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*iva*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ivi*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ivo*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_V, common_lang_constants::UPPER_V,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ono*/
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O,
                    common_lang_constants::LOWER_N, common_lang_constants::UPPER_N,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*uta*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ute*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_E, common_lang_constants::UPPER_E, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*uti*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*uto*/
                    common_lang_constants::LOWER_U, common_lang_constants::UPPER_U,
                    common_lang_constants::LOWER_T, common_lang_constants::UPPER_T,
                    common_lang_constants::LOWER_O, common_lang_constants::UPPER_O, false) )
                {
                return;
                }
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ar*/
                    common_lang_constants::LOWER_A, common_lang_constants::UPPER_A,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                {
                return;
                }
            // 'ir' not in original specification, but used in general implementation
            else if (stem<string_typeT>::delete_if_is_in_rv(text,
                    /*ir*/
                    common_lang_constants::LOWER_I, common_lang_constants::UPPER_I,
                    common_lang_constants::LOWER_R, common_lang_constants::UPPER_R, false) )
                {
                return;
                }
            /** deletion or 'er' from rv is considered problematic,
                but part of the standard*/
            }
        //---------------------------------------------
        void step_3a(string_typeT& text)
            {
            if (text.length() >= 1 &&
                stem<string_typeT>::get_rv() <= text.length()-1 &&
                stem<string_typeT>::is_one_of(text[text.length()-1], ITALIAN_VOWELS_SIMPLE) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                if (stem<string_typeT>::get_rv() <= text.length()-1 &&
                    stem<string_typeT>::is_either(text[text.length()-1],
                        common_lang_constants::LOWER_I, common_lang_constants::UPPER_I) )
                    {
                    text.erase(text.length()-1);
                    stem<string_typeT>::update_r_sections(text);
                    }
                }
            }
        //---------------------------------------------
        void step_3b(string_typeT& text)
            {
            if (stem<string_typeT>::is_suffix_in_rv(text,
                    /*ch*/common_lang_constants::LOWER_C, common_lang_constants::UPPER_C,
                common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) ||
                stem<string_typeT>::is_suffix_in_rv(text,
                    /*gh*/common_lang_constants::LOWER_G, common_lang_constants::UPPER_G,
                    common_lang_constants::LOWER_H, common_lang_constants::UPPER_H) )
                {
                text.erase(text.length()-1);
                stem<string_typeT>::update_r_sections(text);
                }
            }
        };
    }

/** @}*/

#endif // OLEAN_ITALIAN_STEM_H
