#ifndef __DEBUG_LOGIC_H__
#define __DEBUG_LOGIC_H__

#include <fstream>
#include <iostream>
#include <iterator>

#ifdef __PRETTY_FUNCTION__
/**
 * @brief Expands to the name of the current function. Will not be defined if
 *  compiler does not have a native function name macro.
 *
 */
#define __DEBUG_FUNCTION_NAME__ __PRETTY_FUNCTION__
#elif defined(__FUNCTION__)
/**
 * @brief Expands to the name of the current function. Will not be defined if
 *  compiler does not have a native function name macro.
 *
 */
#define __DEBUG_FUNCTION_NAME__ __FUNCTION__
#elif defined(__func__)
/**
 * @brief Expands to the name of the current function. Will not be defined if
 *  compiler does not have a native function name macro.
 *
 */
#define __DEBUG_FUNCTION_NAME__ __func__
#elif defined(__FUNCSIG__)
/**
 * @brief Expands to the name of the current function. Will not be defined if
 *  compiler does not have a native function name macro.
 *
 */
#define __DEBUG_FUNCTION_NAME__ __FUNCSIG__
#elif defined(__FUNCDNAME__)
/**
 * @brief Expands to the name of the current function. Will not be defined if
 *  compiler does not have a native function name macro.
 *
 */
#define __DEBUG_FUNCTION_NAME__ __FUNCDNAME__
#endif

//
#if !defined(NDEBUG) || defined ENABLE_LOGIC_CHECKS || defined DEBUG_ENABLE_ALL
/**
 * @brief Validates that an expression is true at compile time. If the
 *  expression is false then compilation will fail.
 *
 */
#define CASSERT(x) typedef char __C_ASSERT__[(x) ? 1 : -1]
#else
/**
 * @brief Validates that an expression is true at compile time. If the
 *  expression is false then compilation will fail.
 *
 */
#define CASSERT(x) ((void)0)
#endif

//
#ifdef __UNITTEST
/**
 * @brief If unit test symbol (__UNITTEST) is defined then does nothing;
 *  otherwise asserts. This is useful for suppressing asserts when unit
 *  testing.
 *
 */
#define NON_UNIT_TEST_ASSERT(x) ((void)0)
#else
/**
 * @brief If unit test symbol (__UNITTEST) is defined then does nothing;
 *  otherwise asserts. This is useful for suppressing asserts when unit
 *  testing.
 *
 */
#define NON_UNIT_TEST_ASSERT(x) assert(x)
#endif

#if !defined(NDEBUG) || defined DEBUG_ENABLE_ALL
/**
 * @brief Prints data stream to a specified file.
 *
 */
#define DUMP_TO_FILE(x, file) __debug::__dump_to_file((x), (file))
#else
/**
 * @brief Prints data stream to a specified file.
 *
 */
#define DUMP_TO_FILE(x, file) ((void)0)
#endif

// namespace __debug
namespace __debug
{
/* Dubug helpers */

/**
 * @brief Prints data stream to a specified file.
 *
 * @param begin
 * @param file_path
 */
inline void __dump_to_file(
    const wchar_t * begin, const std::string & file_path)
{
    if (begin == NULL)
    {
        return;
    }
    std::wofstream f(file_path.c_str());
    f.write(begin, static_cast<std::streamsize>(std::wcslen(begin)));
}

}  // namespace __debug

#endif  //__DEBUG_LOGIC_H__
