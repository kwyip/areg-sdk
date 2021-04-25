#ifndef AREG_BASE_CESTRING_HPP
#define AREG_BASE_CESTRING_HPP
/************************************************************************
 * \file        areg/src/base/CEString.hpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit 
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform, String Class to handle basic
 *              null-terminated string operations.
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/
#include "areg/src/base/GEGlobal.h"
#include "areg/src/base/TEString.hpp"
#include <stdio.h>
#include <stdarg.h>

/************************************************************************
 * Dependencies.
 ************************************************************************/
class IEInStream;
class IEOutStream;
class CEWideString;

/**
 * \brief       ASCII string class declaration. Has basic functionalities
 *              to handle null-terminated string operations. It does not 
 *              have any special encoding.
 *
 * \details     Use this class to declare member variables if it will 
 *              be used to support streaming. This class also used
 *              in hash map since has operator to covert string value
 *              into hash integer value.
 **/

//////////////////////////////////////////////////////////////////////////
// CEString class declaration.
//////////////////////////////////////////////////////////////////////////
class AREG_API CEString : public TEString<char, TEStringImpl<char>>
{
//////////////////////////////////////////////////////////////////////////
// defined constants
//////////////////////////////////////////////////////////////////////////
public:
    static const char * const   EmptyString     /*= ""*/    ;   //!< Empty String
    static const char * const   BOOLEAN_TRUE    /*= "true"*/;   //!< Boolean value 'true' as string
    static const char * const   BOOLEAN_FALSE   /*= "false"*/;  //!< Boolean value 'false' as string

//////////////////////////////////////////////////////////////////////////
// Constructors / Destructor
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief   Default constructor.
     **/
    inline CEString( void );
    /**
     * \brief    Initialization constructor. Copies data from source
     * \param    source    The string data source. If NULL, sets empty string.
     **/
    inline CEString( const char * source );
    /**
     * \brief    Initialization constructor. Copies carCount chars from source
     * \param    source       The string source
     * \param    charCount    The number of characters to copy.
     **/
    inline CEString( const char * source, int charCount );
    /**
     * \brief    Initialization constructor. Copies char as source
     * \param    ch    Char as string.
     **/
    inline CEString( char ch );
    /**
     * \brief   Copy constructor.
     * \param   source  The source to copy data.
     **/
    inline CEString( const CEString & source );
    /**
     * \brief   Initialization constructor. Converts wide char and copies string
     * \param   source  The source of wide char string
     **/
    inline CEString( const wchar_t* source );
    /**
     * \brief   Initialization constructor. Converts wide char string and
     *          copied first charCount symbols.
     * \param   source      The source of wide char string
     * \param   charCount   The number of character to copy from 
     *                      given string source
     **/
    inline CEString( const wchar_t* source, int charCount );
    /**
    * \brief   Initialization constructor. Copies data from wide char string
    * \param   source  The source object of wide char string
    **/
    CEString( const CEWideString & source );
    /**
     * \brief   Constructor, initializes string from streaming object
     **/
    CEString( const IEInStream & stream );

    /**
     * \brief   Destructor.
     **/
    virtual ~CEString( void );

//////////////////////////////////////////////////////////////////////////
// operators
//////////////////////////////////////////////////////////////////////////
public:

    /**
     * \brief   Converting operator, converts object to unsigned int primitive
     **/
    operator unsigned int ( void ) const;

    /**
     * \brief   Converting operator, converts object to string buffer
     **/
    inline operator const char * ( void ) const;

    /**
     * \brief   Assigning operator, copies data from given string source
     * \param   strSource   The source of string to copy.
     * \return  Returns the string object.
     **/
    const CEString & operator = ( const CEString & strSource );

    /**
     * \brief   Assigning operator, copies data from given null-terminated string source
     * \param   strSource   The source of null-terminated string to copy.
     * \return  Returns the string object.
     **/
    const CEString & operator = ( const char * strSource );

    /**
     * \brief   Assigning operator, copies data from given null-terminated wide-char string source
     * \param   strSource   The source of null-terminated wide-char string to copy.
     * \return  Returns the string object.
     **/
    const CEString & operator = ( const wchar_t * strSource );

    /**
     * \brief   Assigning operator, copies data from given character source
     * \param   chSource    The source of character to copy.
     * \return  Returns the string object.
     **/
    const CEString & operator = ( char chSource );

    /**
     * \brief   Assigning operator, copies data from given wide-string source
     * \param   strSource   The source of wide-string to copy.
     * \return  Returns the string object.
     **/
    const CEString & operator = ( const CEWideString & strSource );

    /**
     * \brief   Determines equality of two strings.
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The second string to compare
     * \return  Returns true if 2 strings are equal.
     * \see     Compare
     **/
    inline bool operator == (const CEString & other) const;
           bool operator == (const CEWideString & other) const;

    /**
     * \brief   Determines equality of two strings.
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The null-terminated string to compare
     * \return  Returns true if 2 strings are equal.
     * \see     Compare
     **/
    inline bool operator == (const char * other) const;
    inline bool operator == (const wchar_t * other) const;

    /**
     * \brief   Determines whether the string is equal to character, i.e. it is one symbol
     *          string and this symbol is equal to specified character.
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   ch      A character to compare.
     * \return  Returns true if the length of string is 1 and the single symbol is equal
     *          to specified character.
     * \see     Compare
     **/
    inline bool operator == (char ch) const;
    inline bool operator == (wchar_t ch) const;

    /**
     * \brief   Determines inequality of two strings.
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The second string to compare
     * \return  Returns true if 2 strings are unequal.
     * \see     Compare
     **/
    inline bool operator != (const CEString & other) const;

    /**
     * \brief   Determines inequality of two strings.
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The null-terminated string to compare
     * \return  Returns true if 2 strings are unequal.
     * \see     Compare
     **/
    inline bool operator != (const char * other) const;

    /**
     * \brief   Determines whether existing string is more than given strings.
     *          The operator is needed for sorting algorithms
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The second string to compare
     * \return  Returns true if existing string is more than given.
     * \see     Compare
     **/
    inline bool operator > ( const CEString & other ) const;

    /**
     * \brief   Determines whether existing string is less than given strings.
     *          The operator is needed for sorting algorithms
     * \remark  The comparing of strings is case-sensitive.
     *          To compare case-insensitive, use Compare() method.
     * \param   other   The second string to compare
     * \return  Returns true if existing string is less than given.
     * \see     Compare
     **/
    inline bool operator < ( const CEString & other ) const;

    /**
     * \brief   Appends given string at the end of existing string.
     * \param   strSource   The source of string to append at the end
     * \return  Returns string object
     **/
    CEString & operator += ( const CEString & strSource );

    /**
     * \brief   Appends given null-terminated string at the end of existing string.
     * \param   strSource   The source of null-terminated string to append at the end
     * \return  Returns string object
     **/
    CEString & operator += ( const char * strSource );

    /**
     * \brief   Appends given null-terminated wide-char string at the end of existing string.
     * \param   strSource   The source of null-terminated wide-char string to append at the end
     * \return  Returns string object
     **/
    CEString & operator += ( const wchar_t * strSource );

    /**
     * \brief   Appends given wide string at the end of existing string.
     * \param   strSource   The source of wide string to append at the end
     * \return  Returns string object
     **/
    CEString & operator += ( const CEWideString & strSource );

    /**
     * \brief   Appends given character at the end of existing string.
     * \param   chSource   The source of character to append at the end
     * \return  Returns string object
     **/
    CEString & operator += ( char chSource );

    /**
     * \brief   Returns character at given position. The position should be valid.
     * \param   atPos   The valid position in string buffer.
     * \return  Returns character at given position.
     **/
    char operator [ ] (int atPos) const;

/************************************************************************/
// Friend global operators to operate String
/************************************************************************/
    /**
     * \brief   Operator to concatenate 2 strings.
     * \param   lhs     Left-hand side string object
     * \param   rhs     Right-hand side string object
     * \return  Returns newly constructed string object by concatenating 2 strings
     **/
    friend AREG_API CEString operator + (const CEString & lhs, const CEString & rhs);
    
    /**
     * \brief   Operator to concatenate 2 strings.
     * \param   lhs     Left-hand side string object
     * \param   rhs     Right-hand side null-terminated string
     * \return  Returns newly constructed string object by concatenating 2 strings
     **/
    friend AREG_API CEString operator + (const CEString & lhs, const char * rhs);
    
    /**
     * \brief   Operator to concatenate 2 strings.
     * \param   lhs     Left-hand side null-terminated string
     * \param   rhs     Right-hand side string object
     * \return  Returns newly constructed string object by concatenating 2 strings
     **/
    friend AREG_API CEString operator + (const char * lhs, const CEString & rhs);
    
    /**
     * \brief   Operator to concatenate string and 8-bit character.
     * \param   lhs     Left-hand side string object
     * \param   rhs     Right-hand side 8-bit character
     * \return  Returns newly constructed string object by concatenating string and char
     **/
    friend AREG_API CEString operator + (const CEString & lhs, char chRhs);
    
    /**
     * \brief   Operator to concatenate 8-bit character and string.
     * \param   lhs     Left-hand side 8-bit character
     * \param   rhs     Right-hand side string object
     * \return  Returns newly constructed string object by concatenating char and string
     **/
    friend AREG_API CEString operator + (char chLhs, const CEString & rhs);

/************************************************************************/
// Friend global operators to stream String
/************************************************************************/
    /**
     * \brief   Streams to input object, i.e. reads data from streaming object to string,
     *          and initialize string data.
     * \param    stream  Streaming object to read string data
     * \param    input    String object to initialize and write string data.
     * \return    Reference to stream object.
     **/
    friend AREG_API const IEInStream & operator >> (const IEInStream & stream, CEString & input);
    
    /**
     * \brief    Streams from output object, i.e. write data from string to streaming object.
     * \param    stream    Streaming object to write data.
     * \param    output    String object to read data from
     * \return    Reference to stream object.
     **/
    friend AREG_API IEOutStream & operator << (IEOutStream & stream, const CEString & output);

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////

public:
/************************************************************************/
// Static methods
/************************************************************************/
    /**
     * \brief   Searches given phrase in the string buffer until the end of string.
     *          If found, returns string with data until the found position.
     *          On output, if 'out_next' is not NULL, contains pointer to the next position
     *          after phrase in given string buffer, or NULL if phrase not found.
     * \param   strSource   The source of string
     * \param   strPhrase   The phrase to search in the string.
     * \param   out_next    If not NULL, on return contains value of pointer next after phrase in string buffer,
     *                      or NULL if could not find the string.
     * \return  Returns string copied until matched phrase.
     *
     * \example CEString::GetSubstring
     * 
     *  CEString test("0123 456 789 0123");
     * 
     *  const char * next = static_cast<const char *>(test);                        // next == "0123 456 789 0123"
     *  CEString result1 = CEString::GetSubstring( next, "0123", &next);            // results: result1 == ""           , next == " 456 789 0123"
     *  CEString result2 = CEString::GetSubstring( next, "0123", &next);            // results: result2 == " 456 789 "  , next == ""
     *  CEString result3 = CEString::GetSubstring( next, "0123", &next);            // results: result3 == ""           , next == NULL;
     *  
     *  next = static_cast<const char *>(test);                                     // next == "0123 456 789 0123"
     *  CEString result4 = CEString::GetSubstring( next, " ", &next);               // results: result4 == "0123"          , next == "456 789 0123"
     *  CEString result5 = CEString::GetSubstring( next, " ", &next);               // results: result5 == "456 789"       , next == "789 0123"
     *  CEString result6 = CEString::GetSubstring( next, " ", &next);               // results: result6 == "789"           , next == "0123";
     *  CEString result7 = CEString::GetSubstring( next, " ", &next);               // results: result7 == "0123"          , next == NULL;
     **/
    static CEString GetSubstring( const char * strSource, const char * strPhrase, const char ** out_next = static_cast<const char **>(NULL) );

    /**
     * \brief   Converts given string of digits to 32-bit integer
     * \param   strDigit    The string with digits. Can contain negative or positive sign in front
     * \param   radix       The base value when calculate integer.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 32-bit integer
     **/
    static int32_t StringToInt32( const char * strDigit, NEString::eRadix radix = NEString::RadixDecimal, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string of digits to 32-bit unsigned integer
     * \param   strDigit    The string with digits.
     * \param   radix       The base value when calculate integer.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 32-bit unsigned integer
     **/
    static uint32_t StringToUInt32( const char * strDigit, NEString::eRadix radix = NEString::RadixDecimal, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string of digits to 64-bit integer
     * \param   strDigit    The string with digits. Can contain negative or positive sign in front
     * \param   radix       The base value when calculate integer.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 64-bit integer
     **/
    static int64_t StringToInt64( const char * strDigit, NEString::eRadix radix = NEString::RadixDecimal, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string of digits to 64-bit unsigned integer
     * \param   strDigit    The string with digits.
     * \param   radix       The base value when calculate integer.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 64-bit unsigned integer
     **/
    static uint64_t StringToUInt64( const char * strDigit, NEString::eRadix radix = NEString::RadixDecimal, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string of digits to 32-bit digit with floating point
     * \param   strDigit    The string with digits.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 32-bit digit with floating point
     **/
    static float StringToFloat( const char * strDigit, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string of digits to 64-bit digit with floating point
     * \param   strDigit    The string with digits.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strDigit buffer after the numerical value.
     * \return  Returns the 64-bit digit with floating point
     **/
    static double StringToDouble( const char * strDigit, const char ** end = static_cast<const char **>(NULL) );
    /**
     * \brief   Converts given string to boolean value
     * \param   strBoolean  The string to convert.
     * \param   end [out]   If not null, on output this contains value of pointer to the next character in strBoolean buffer after the numerical value.
     * \return  Returns the 64-bit digit with floating point
     **/
    static bool StringToBoolean( const char * strBoolean, const char ** end = static_cast<const char **>(NULL) );

    /**
     * \brief   Converts given signed 32-bit integer into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \param   radix       The base value to make conversion. The lowest is 2 (binary) and the highest is hexadecimal (16)
     * \return  Returns converted string.
     **/
    static CEString Int32ToString( int32_t number, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts given unsigned 32-bit integer into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \param   radix       The base value to make conversion. The lowest is 2 (binary) and the highest is hexadecimal (16)
     * \return  Returns converted string.
     **/
    static CEString UInt32ToString( uint32_t number, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts given signed 64-bit integer into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \param   radix       The base value to make conversion. The lowest is 2 (binary) and the highest is hexadecimal (16)
     * \return  Returns converted string.
     **/
    static CEString Int64ToString( int64_t number, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts given unsigned 64-bit integer into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \param   radix       The base value to make conversion. The lowest is 2 (binary) and the highest is hexadecimal (16)
     * \return  Returns converted string.
     **/
    static CEString UInt64ToString( uint64_t number, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts given 32-bit digit with floating point into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \return  Returns converted string.
     **/
    static CEString FloatToString( float number );
    /**
     * \brief   Converts given 32-bit digit with floating point into the string. The conversion is done on radix base, which by default is decimal (10).
     * \param   number      The number to convert to string
     * \return  Returns converted string.
     **/
    static CEString DoubleToString( double number );
    /**
     * \brief   Converts given boolean value to string.
     * \param   value   The boolean value to convert to string
     * \return  Returns converted string.
     **/
    static CEString BooleanToString( bool value );

    /**
     * \brief   Formats the string. The classic rules similar of 'spintf' are applied.
     * \param   strDst  The destination where formated string is copied.
     * \param   count   The length of destination buffer.
     * \param   format  The format of string, then followed values to output if they exist.
     * \param   ...     Additional arguments
     * \return  Returns the number of characters copied in the buffer.
     *          Return zero if nothing is copied.
     *          Returns negative value if error occurred (for example, formating syntax error).
     **/
    static int PrintString( char * strDst, int count, const char * format, ... );

    /**
     * \brief   Formats the string. The classic rules similar of 'vsprintf' are applied.
     * \param   strDst  The destination where formated string is copied.
     * \param   count   The length of destination buffer.
     * \param   format  The format of string, then followed values to output if they exist.
     * \param   argptr  The list of arguments.
     * \return  Returns the number of characters copied in the buffer.
     *          Return zero if nothing is copied.
     *          Returns negative value if error occurred (for example, formating syntax error).
     **/
    static int PrintStringList( char * strDst, int count, const char * format, va_list argptr );

public:
    /**
     * \brief   Returns substring of existing string. The substring is formed starting at given position in string buffer
     *          and number of characters to get in string or until end of string if 'charCount' is NEString::CountAll
     * \param   startPos    The starting position in existing string buffer. Should be valid position.
     *                      By default, starting position is begin of string buffer, i.e. NEString::StartPos
     * \param   charCount   The number of characters to copy to substring. If equal to NEString::CountAll,
     *                      it copies characters until end of string.
     * \return  Returns created substring.
     **/
    inline CEString Substr( NEString::CharPos startPos = NEString::StartPos, NEString::CharCount charCount = NEString::CountAll ) const;

    /**
     * \brief   Searches given phrase in the string starting from given position until the end of string.
     *          If found, copies the string data into the result until the found position and returns position
     *          next after phrase. If not found, will copy complete string until end.
     * \param   outResult   On output, the string contains result of copied data until found position
     *                      or contains the complete string until the end.
     * \param   strPhrase   The phrase to search in the string.
     * \param   startPos    The starting position to search the string.
     * \return  Returns following values:
     *              -   Valid string position not equal to NEString::EndPos,
     *                  if found phrase and the phrase is not at the end;
     *              -   NEString::EndPos if found the phrase at end of string;
     *              -   NEString::InvalidPos if could not find the phrase.
     *
     * \example CEString::Substr
     *
     *  CEString test("0123 456 789 0123");
     *  CEString result;
     *  NEString::CharPos next = NEString::StartPos;
     *  next = test.Substr(result, "0123", next);   // results: next == 4, result == ""
     *  next = test.Substr(result, "0123", next);   // results: next == NEString::EndPos, result == " 456 789 "
     *
     *  next = NEString::StartPos;
     *  next = test.Substr(result, " ", next);      // results: next == 5, result == "0123"
     *  next = test.Substr(result, " ", next);      // results: next == 9, result == "456"
     *  next = test.Substr(result, " ", next);      // results: next == NEString::InvalidPos, result == "0123"
     **/
    inline NEString::CharPos Substr( CEString & outResult, const char * strPhrase, NEString::CharPos startPos = NEString::StartPos ) const;

    /**
     * \brief   Searches given symbol in the string starting from given position until end of string.
     *          If found, copies the string data into the result until the found position and returns position
     *          next after symbol. If not found, will copy complete string until end.
     * \param   outResult   On output, the string contains result of copied data until found position
     *                      or contains the complete string until the end.
     * \param   chSymbol    The symbol to search in the string.
     * \param   startPos    The starting position to search the symbol.
     * \return  Returns next position after searched symbol and value are followings:
     *              -   Valid string position not equal to NEString::EndPos,
     *                  if found phrase and the symbol is not at the end;
     *              -   NEString::EndPos if found the symbol at end of string;
     *              -   NEString::InvalidPos if could not find the phrase.
     **/
    inline NEString::CharPos Substr( CEString & outResult, char chSymbol, NEString::CharPos startPos = NEString::StartPos ) const;

    /**
     * \brief   Returns left side (begin) substring of length 'charCount'
     * \param   charCount   The number of characters to extract.
     * \return  Returns the left side substring of length 'charCount' or empty string is string is empty.
     **/
    inline CEString LeftStr( NEString::CharCount charCount ) const;

    /**
     * \brief   Returns right side (end) substring of length 'charCount'
     * \param   charCount   The number of characters to extract.
     * \return  Returns the right side substring of length 'charCount' or empty string is string is empty.
     **/
    inline CEString RightStr( NEString::CharCount charCount ) const;

    /**
     * \brief   Formats the string. The classic rules similar of 'spintf' are applied.
     * \param   format  The format of string, then followed values to output if they exist.
     * \param   ...     Additional arguments
     * \return  Returns the resulting string.
     * \note    By default, it will be 128 character space allocated to format string.
     *          If fails, will try repeat operation with 512 chars
     **/
    const CEString & Format( const char * format, ... );

    /**
     * \brief   Formats the string. The classic rules similar of 'vsprintf' are applied.
     * \param   format  The format of string, then followed values to output if they exist.
     * \param   argptr  The list of arguments.
     * \return  Returns the resulting string.
     * \note    By default, it will be 128 character space allocated to format string.
     *          If fails, will try repeat operation with 512 chars
     **/
    const CEString & FormatList( const char * format, va_list argptr );

    /**
     * \brief   Converts string of digits to 32-bit integer
     * \param   radix       The base value when calculate integer.
     * \return  Returns the 32-bit integer
     **/
    inline int32_t ToInt32( NEString::eRadix radix = NEString::RadixDecimal ) const;
    /**
     * \brief   Converts string of digits to 32-bit unsigned integer
     * \param   radix       The base value when calculate integer.
     * \return  Returns the 32-bit unsigned integer
     **/
    inline uint32_t ToUInt32( NEString::eRadix radix = NEString::RadixDecimal ) const;
    /**
     * \brief   Converts string of digits to 64-bit integer
     * \param   radix       The base value when calculate integer.
     * \return  Returns the 64-bit integer
     **/
    inline int64_t ToInt64( NEString::eRadix radix = NEString::RadixDecimal ) const;
    /**
     * \brief   Converts string of digits to 64-bit unsigned integer
     * \param   radix       The base value when calculate integer.
     * \return  Returns the 64-bit unsigned integer
     **/
    inline uint64_t ToUInt64( NEString::eRadix radix = NEString::RadixDecimal ) const;
    /**
     * \brief   Converts string of digits to 32-bit digit with floating point
     * \return  Returns the 32-bit digit with floating point
     **/
    inline float ToFloat( void ) const;
    /**
     * \brief   Converts string of digits to 64-bit digit with floating point
     * \return  Returns the 64-bit digit with floating point
     **/
    inline double ToDouble( void ) const;
    /**
     * \brief   Converts string to boolean value. If value is "true", it returns true. Otherwise returns false.
     * \return  Returns boolean value.
     **/
    inline bool ToBoolean( void ) const;

    /**
     * \brief   Converts and sets 32-bit signed digit in the string based on radix bases.
     * \param   value   The 32-bit signed integer value to set in the string.
     * \param   radix   The base of conversion. It set RadixAutomatic, it will use
     *                  RadixDecimal. By default, conversion is done in RadixDecimal.
     * \return  Returns string with value.
     * \note    If value is negative, the minus sign is added at begin.
     *          Except decimal (base 10), in other cases it might make less sense.
     *          If need to convert negative number to Hexadecimal or Octal,
     *          might make sense to use FromUInt32 method.
     **/
    inline CEString & FromInt32( int32_t value, NEString::eRadix radix = NEString::RadixDecimal );

    /**
     * \brief   Converts and sets 32-bit unsigned digit in the string based on radix bases.
     * \param   value   The 32-bit unsigned integer value to set in the string.
     * \param   radix   The base of conversion. It set RadixAutomatic, it will use
     *                  RadixDecimal. By default, conversion is done in RadixDecimal.
     * \return  Returns string with value.
     * \note    In case of RadixHexadecimal, it adds "0x" at the begin and the total length
     *          of string is 10, where first 2 positions are "0x" and the rest 8 positions
     *          are filled with 
     **/
    inline CEString & FromUInt32( uint32_t value, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts and sets 64-bit signed digit in the string based on radix bases.
     * \param   value   The 64-bit signed integer value to set in the string.
     * \param   radix   The base of conversion. It set RadixAutomatic, it will use
     *                  RadixDecimal. By default, conversion is done in RadixDecimal.
     * \return  Returns string with value.
     * \note    If value is negative, the minus sign is added at begin.
     *          Except decimal (base 10), in other cases it might make less sense.
     *          If need to convert negative number to Hexadecimal or Octal,
     *          might make sense to use FromUInt32 method.
     **/
    inline CEString & FromInt64( int64_t value, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts and sets 64-bit unsigned digit in the string based on radix bases.
     * \param   value   The 64-bit unsigned integer value to set in the string.
     * \param   radix   The base of conversion. It set RadixAutomatic, it will use
     *                  RadixDecimal. By default, conversion is done in RadixDecimal.
     * \return  Returns string with value.
     * \note    In case of RadixHexadecimal, it adds "0x" at the begin and the total length
     *          of string is 10, where first 2 positions are "0x" and the rest 8 positions
     *          are filled with 
     **/
    inline CEString & FromUInt64( uint64_t value, NEString::eRadix radix = NEString::RadixDecimal );
    /**
     * \brief   Converts and sets float digit in the string.
     * \param   value   The value of number with floating point to set in the string.
     * \return  Returns string with value.
     **/
    inline CEString & FromFloat( float value );
    /**
     * \brief   Converts and sets double digit in the string.
     * \param   value   The value of number with floating point to set in the string.
     * \return  Returns string with value.
     **/
    inline CEString & FromDouble( double value );
    /**
     * \brief   Converts and sets boolean value in the string.
     * \param   value   The boolean value to set in the string.
     * \return  Returns string with value.
     **/
    inline CEString & FromBoolean( bool value );

/************************************************************************/
// String overrides
/************************************************************************/
protected:
    /**
    * \brief   Reads string data from streaming object.
    * \param   stream  The streaming object, which contains string source data
    **/
    virtual void readStream(const IEInStream & stream);

    /**
    * \brief   Writes string data to streaming object.
    * \param   stream  The streaming object to write string data.
    **/
    virtual void writeStream(IEOutStream & stream) const;

//////////////////////////////////////////////////////////////////////////
// Hidden methods
//////////////////////////////////////////////////////////////////////////
private:
    inline CEString & self( void );                 //!< Returns reference object of string itself
    inline const CEString & self( void ) const;     //!< Returns reference object of string itself
};

//////////////////////////////////////////////////////////////////////////
// CEString class inline function implementation
//////////////////////////////////////////////////////////////////////////

inline CEString & CEString::self( void )
{   return (*this);     }

inline const CEString & CEString::self( void ) const
{   return (*this);     }

inline CEString::CEString( void )
    : TEString<char>( NEString::EncodeAscii )
{   ;   }

inline CEString::CEString( const char * source )
    : TEString<char>( source, NEString::EncodeAscii )
{   ;   }

inline CEString::CEString( char ch )
    : TEString<char>( ch, NEString::EncodeAscii )
{   ;   }

inline CEString::CEString( const CEString & source )
    : TEString<char>( static_cast<const TEString<char> &>(source) )
{   ;   }

inline CEString::CEString( const char * source, int charCount )
    : TEString<char>( source, charCount, NEString::EncodeAscii )
{   ;   }

inline CEString::CEString( const wchar_t* source )
    : TEString<char>( NULL_STRING, NEString::getStringLength<wchar_t>( source ), NEString::EncodeAscii )
{   NEString::copyString<char, wchar_t>( getString( ), source );                                }

inline CEString::CEString( const wchar_t* source, int charCount )
    : TEString<char>( NULL_STRING, charCount, NEString::EncodeAscii )
{   NEString::copyString<char, wchar_t>( getString( ), source, NEString::StartPos, charCount ); }

inline CEString::operator const char *(void) const
{   return getChars(NEString::StartPos);                                                        }

inline bool CEString::operator == (const CEString & other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other.GetBuffer( ) ) == 0);        }

inline bool CEString::operator == (const char * other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other ) == 0);                     }

inline bool CEString::operator == (const wchar_t * other) const
{   return (NEString::compareFast<char, wchar_t>( GetBuffer( ), other ) == 0);                  }

inline bool CEString::operator == (const char ch) const
{   return ((GetLength() == 1) && (GetCharAt(0) == ch));                                        }

inline bool CEString::operator == (const wchar_t ch) const
        {   return ((GetLength() == 1) && (static_cast<wchar_t>(GetCharAt(0)) == ch));          }

inline bool CEString::operator != (const CEString & other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other.GetBuffer( ) ) != 0);        }

inline bool CEString::operator != (const char * other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other ) != 0);                     }

inline bool CEString::operator > (const CEString & other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other.GetBuffer() ) < 0);          }

inline bool CEString::operator < (const CEString & other) const
{   return (NEString::compareFast<char, char>( GetBuffer( ), other.GetBuffer() ) > 0);          }

inline NEString::CharPos CEString::Substr( CEString & outResult, const char * strPhrase, NEString::CharPos startPos /*= NEString::StartPos*/ ) const
{   return TEString<char>::Substr( outResult, strPhrase, startPos );                            }

inline NEString::CharPos CEString::Substr( CEString & outResult, char chSymbol, NEString::CharPos startPos /*= NEString::StartPos */ ) const
{   return TEString<char>::Substr(outResult, chSymbol, startPos);                               }

inline CEString CEString::Substr( NEString::CharPos startPos /*= NEString::StartPos*/, NEString::CharCount charCount /*= NEString::CountAll*/ ) const
{
    CEString result(getInitEncoding());
    TEString<char>::Substr(result, startPos, charCount);
    return result;
}

inline CEString CEString::LeftStr( NEString::CharCount charCount ) const
{
    CEString result( getInitEncoding( ) );
    TEString<char>::Substr( result, NEString::StartPos, charCount );
    return result;
}

inline CEString CEString::RightStr( NEString::CharCount charCount ) const
{
    CEString result( getInitEncoding( ) );
    NEString::CharPos pos = charCount < GetLength() ? GetLength() - charCount : NEString::StartPos;
    TEString<char>::Substr( result, pos, NEString::CountAll );
    return result;
}

inline int32_t CEString::ToInt32( NEString::eRadix radix /*= NEString::RadixDecimal */ ) const
{   return CEString::StringToInt32(GetBuffer(), radix, static_cast<const char **>(NULL) );  }

inline uint32_t CEString::ToUInt32( NEString::eRadix radix /*= NEString::RadixDecimal */ ) const
{   return CEString::StringToUInt32(GetBuffer(), radix, static_cast<const char **>(NULL) ); }

inline int64_t CEString::ToInt64( NEString::eRadix radix /*= NEString::RadixDecimal */ ) const
{   return CEString::StringToInt64(GetBuffer(), radix, static_cast<const char **>(NULL) );  }

inline uint64_t CEString::ToUInt64( NEString::eRadix radix /*= NEString::RadixDecimal */ ) const
{   return CEString::StringToUInt64(GetBuffer(), radix, static_cast<const char **>(NULL) ); }

inline float CEString::ToFloat( void ) const
{   return CEString::StringToFloat(GetBuffer(), static_cast<const char **>(NULL) );         }

inline double CEString::ToDouble( void ) const
{   return CEString::StringToDouble(GetBuffer(), static_cast<const char **>(NULL) );        }

inline bool CEString::ToBoolean( void ) const
{   return (NEString::compareIgnoreCase<char, char>( String(), BOOLEAN_TRUE ) == 0);        }

inline CEString & CEString::FromInt32( int32_t value, NEString::eRadix radix /*= NEString::RadixDecimal */ )
{
    self() = CEString::Int32ToString(value, radix);
    return self();
}

inline CEString & CEString::FromUInt32( uint32_t value, NEString::eRadix radix /*= NEString::RadixDecimal */ )
{
    self( ) = CEString::UInt32ToString( value, radix );
    return self( );
}

inline CEString & CEString::FromInt64( int64_t value, NEString::eRadix radix /*= NEString::RadixDecimal */ )
{
    self( ) = CEString::Int64ToString( value, radix );
    return self( );
}

inline CEString & CEString::FromUInt64( uint64_t value, NEString::eRadix radix /*= NEString::RadixDecimal */ )
{
    self( ) = CEString::UInt64ToString( value, radix );
    return self( );
}

inline CEString & CEString::FromFloat( float value )
{
    self( ) = CEString::FloatToString( value );
    return self( );
}

inline CEString & CEString::FromDouble( double value )
{
    self( ) = CEString::DoubleToString( value );
    return self( );
}

inline CEString & CEString::FromBoolean( bool value )
{
    self( ) = CEString::BooleanToString( value );
    return self( );
}

#endif  // AREG_BASE_CESTRING_HPP