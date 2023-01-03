/*
 ===================================================================================================
 Name        : test_printf.c
 Author      : 
 Version     :
 Copyright   :
 Description :
 ===================================================================================================
 */

/***************************************************************************************************
 * INCLUDES
 */
#include "app_printf.h"
#include <appTasks.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "serial_handler.h"

/*! @brief Specification modifier flags for printf. */
enum printf_flag {
    flag_minus             = 0x01U,  /*!< Minus FLag. */
    flag_plus              = 0x02U,  /*!< Plus Flag. */
    flag_space             = 0x04U,  /*!< Space Flag. */
    flag_zero              = 0x08U,  /*!< Zero Flag. */
    flag_pound             = 0x10U,  /*!< Pound Flag. */
    flag_LengthChar        = 0x20U,  /*!< Length: Char Flag. */
    flag_LengthShortInt    = 0x40U,  /*!< Length: Short Int Flag. */
    flag_LengthLongInt     = 0x80U,  /*!< Length: Long Int Flag. */
    flag_LengthLongLongInt = 0x100U, /*!< Length: Long Long Int Flag. */
};

static int32_t NumToString(char *numStr,
                           void *numPtr,
                           int32_t neg,
                           int32_t radix,
                           bool use_caps);

static int formatPrintf(const char *fmt, va_list ap);

static int32_t bufChr(char chr,
                      int32_t len,
                      int32_t idx);
static void wrTxBuf(int32_t len);

//static int32_t cnt = 0;
static uint8_t txTmp[256];
//static uint8_t maxTx = TX_MAX;

/***************************************************************************************************
 * GLOBAL VARIABLES
 */

/***************************************************************************************************
 * LOCAL VARIABLES
 */

/***************************************************************************************************
 * LOCAL FUNCTIONS
 */

/****************************************************************************
 * dbgPrintf
 *
 * DESCRIPTION:
 *
 */
void dbgPrintf(char *formatString, ...) {

   va_list arg;

   va_start(arg, formatString);
   formatPrintf(formatString, arg);
   va_end(arg);

}

/****************************************************************************
 * DbgConsole_Printf
 *
 * DESCRIPTION:
 *
 */
int DbgConsole_Printf(const char *formatString, ...) {

    va_list arg;

   va_start(arg, formatString);
   formatPrintf(formatString, arg);
   va_end(arg);

   return 0;
}

/****************************************************************************
 * FormatPrintf
 *
 * DESCRIPTION:
 *
 */
static int formatPrintf(const char *fmt,
                        va_list ap) {

    char *fmtPtr;
    int32_t fmtChr;

    char valStr[33];
    char *valStrPtr = NULL;
    int32_t valStrLen = 0;

    int32_t done;

    uint32_t field_width;
    uint32_t precision_width;
    char *sVal;
    int32_t cVal;
    bool use_caps;
    uint8_t radix = 0;

    uint32_t flags_used;
    int32_t schar, dschar;
    int64_t iVal;
    uint64_t uVal = 0;
    bool valid_precision_width;
    int32_t idx;
    int32_t len;

    //cnt = 0;
    idx = 0;
    // Start parsing apart the format string and display appropriate formats and data.
    for(fmtPtr = (char*)fmt; (fmtChr = *fmtPtr) != 0; fmtPtr++) {
        if(fmtChr != '%') {
            idx = bufChr(fmtChr, 1, idx);
            continue;
        }
        use_caps = true;
        // First check for specification modifier flags.
        flags_used = 0;
        done = false;
        while(!done) {
            switch(*++fmtPtr) {
                case '-':
                    flags_used |= flag_minus;
                    break;
                case '+':
                    flags_used |= flag_plus;
                    break;
                case ' ':
                    flags_used |= flag_space;
                    break;
                case '0':
                    flags_used |= flag_zero;
                    break;
                case '#':
                    flags_used |= flag_pound;
                    break;
                default:
                    // We've gone one char too far.
                    --fmtPtr;
                    done = true;
                    break;
            }
        }
        // Next check for minimum field width.
        field_width = 0;
        done = false;
        while(!done) {
            fmtChr = *++fmtPtr;
            if((fmtChr >= '0') && (fmtChr <= '9')) {
                field_width = (field_width * 10) + (fmtChr - '0');
            }
            else if(fmtChr == '*') {
                field_width = (uint32_t)va_arg(ap, uint32_t);
            }
            else {
                // We've gone one char too far.
                --fmtPtr;
                done = true;
            }
        }
        // Next check for the width and precision field separator.
        precision_width = 6;
        valid_precision_width = false;
        if(*++fmtPtr == '.') {
            // Must get precision field width, if present.
            precision_width = 0;
            done = false;
            while(!done) {
                fmtChr = *++fmtPtr;
                if((fmtChr >= '0') && (fmtChr <= '9')) {
                    precision_width = (precision_width * 10) + (fmtChr - '0');
                    valid_precision_width = true;
                }
                else if(fmtChr == '*') {
                    precision_width = (uint32_t)va_arg(ap, uint32_t);
                    valid_precision_width = true;
                }
                else {
                    // We've gone one char too far.
                    --fmtPtr;
                    done = true;
                }
            }
        }
        else {
            // We've gone one char too far.
            --fmtPtr;
        }
        // Check for the length modifier.
        switch(/* c = */*++fmtPtr) {
            case 'h':
                if(*++fmtPtr != 'h') {
                    flags_used |= flag_LengthShortInt;
                    --fmtPtr;
                }
                else {
                    flags_used |= flag_LengthChar;
                }
                break;
            case 'l':
                if(*++fmtPtr != 'l') {
                    flags_used |= flag_LengthLongInt;
                    --fmtPtr;
                }
                else {
                    flags_used |= flag_LengthLongLongInt;
                }
                break;
            default:
                // we've gone one char too far
                --fmtPtr;
                break;
        }
        // Now we're ready to examine the format.
        fmtChr = *++fmtPtr;
        if((fmtChr == 'd') || (fmtChr == 'i') || (fmtChr == 'f') || (fmtChr == 'F') ||
           (fmtChr == 'x') || (fmtChr == 'X') || (fmtChr == 'o') || (fmtChr == 'b') ||
           (fmtChr == 'p') || (fmtChr == 'u')) {
            if((fmtChr == 'd') || (fmtChr == 'i')) {
                if(flags_used & flag_LengthLongLongInt) {
                    iVal = (int64_t)va_arg(ap, int64_t);
                }
                else {
                    iVal = (int32_t)va_arg(ap, int32_t);
                }
                valStrLen = NumToString(valStr,
                                        &iVal,
                                        true,
                                        10,
                                        use_caps);
                valStrPtr = &valStr[valStrLen];
                if(iVal < 0) {
                    schar = '-';
                    ++valStrLen;
                }
                else {
                    if(flags_used & flag_plus) {
                        schar = '+';
                        ++valStrLen;
                    }
                    else {
                        if(flags_used & flag_space) {
                            schar = ' ';
                            ++valStrLen;
                        }
                        else {
                            schar = 0;
                        }
                    }
                }
                dschar = false;
                // Do the ZERO pad.
                if(flags_used & flag_zero) {
                    if(schar) {
                        idx = bufChr(schar, 1, idx);
                    }
                    dschar = true;
                    if(field_width > valStrLen) {
                        len = field_width - valStrLen;
                        idx = bufChr('0', len, idx);
                        valStrLen = field_width;
                    }
                }
                else {
                    if(!(flags_used & flag_minus)) {
                        if(field_width > valStrLen) {
                            len = field_width - valStrLen;
                            idx = bufChr(' ', len, idx);
                        }
                        if(schar) {
                            idx = bufChr(schar, 1, idx);
                        }
                        dschar = true;
                    }
                }
                // The string was built in reverse order, now display in correct order.
                if((!dschar) && schar) {
                    idx = bufChr(schar, 1, idx);
                }
            }
            if((fmtChr == 'X') || (fmtChr == 'x')) {
                if(fmtChr == 'x') {
                    use_caps = false;
                }
                if(flags_used & flag_LengthLongLongInt) {
                    uVal = (uint64_t)va_arg(ap, uint64_t);
                }
                else {
                    uVal = (uint32_t)va_arg(ap, uint32_t);
                }
                valStrLen = NumToString(valStr,
                                        &uVal,
                                        false,
                                        16,
                                        use_caps);
                valStrPtr = &valStr[valStrLen];
                dschar = false;
                if(flags_used & flag_zero) {
                    if(flags_used & flag_pound) {
                        idx = bufChr('0', 1, idx);
                        idx = bufChr((use_caps ? 'X' : 'x'), 1, idx);
                        dschar = true;
                    }
                    if(field_width > valStrLen) {
                        len = field_width - valStrLen;
                        idx = bufChr('0', len, idx);
                        valStrLen = field_width;
                    }
                }
                else {
                    if(!(flags_used & flag_minus)) {
                        if(flags_used & flag_pound) {
                            valStrLen += 2;
                        }
                        if(field_width > valStrLen) {
                            len = field_width - valStrLen;
                            idx = bufChr(' ', len, idx);
                        }
                        if(flags_used & flag_pound) {
                            idx = bufChr('0', 1, idx);
                            idx = bufChr((use_caps ? 'X' : 'x'), 1, idx);
                            dschar = true;
                        }
                    }
                }
                if((flags_used & flag_pound) && (!dschar)) {
                    idx = bufChr('0', 1, idx);
                    idx = bufChr((use_caps ? 'X' : 'x'), 1, idx);
                    valStrLen += 2;
                }
            }
            if((fmtChr == 'o') || (fmtChr == 'b') || (fmtChr == 'p') || (fmtChr == 'u')) {
                if(flags_used & flag_LengthLongLongInt) {
                    uVal = (uint64_t)va_arg(ap, uint64_t);
                }
                else {
                    uVal = (uint32_t)va_arg(ap, uint32_t);
                }
                if(fmtChr == 'o') {
                    radix = 8;
                }
                else if(fmtChr == 'b') {
                    radix = 2;
                }
                else if(fmtChr == 'p') {
                    radix = 16;
                }
                else {
                    radix = 10;
                }
                valStrLen = NumToString(valStr,
                                        &uVal,
                                        false,
                                        radix,
                                        use_caps);
                valStrPtr = &valStr[valStrLen];
                if(flags_used & flag_zero) {
                    if(field_width > valStrLen){
                        len = field_width - valStrLen;
                        idx = bufChr('0', len, idx);
                        valStrLen = field_width;
                    }
                }
                else {
                    if(!(flags_used & flag_minus)) {
                        if(field_width > valStrLen){
                            len = field_width - valStrLen;
                            idx = bufChr(' ', len, idx);
                        }
                    }
                }
            }
            if(valStrPtr != NULL) {
                while(*valStrPtr) {
                    idx = bufChr(*valStrPtr--, 1, idx);
                }
            }
            if(flags_used & flag_minus) {
                if(field_width > valStrLen){
                    len = field_width - valStrLen;
                    idx = bufChr(' ', len, idx);
                }
            }
        }
        else if(fmtChr == 'c') {
            cVal = (char)va_arg(ap, uint32_t);
            idx = bufChr(cVal, 1, idx);
        }
        else if(fmtChr == 's') {
            sVal = (char *)va_arg(ap, char*);
            if(sVal) {
                if(valid_precision_width) {
                    valStrLen = precision_width;
                }
                else {
                    valStrLen = strlen(sVal);
                }
                if(!(flags_used & flag_minus)) {
                    if(field_width > valStrLen){
                        len = field_width - valStrLen;
                        idx = bufChr(' ', len, idx);
                    }
                }
                if(valid_precision_width) {
                    while((*sVal) && (valStrLen > 0)) {
                        idx = bufChr(*sVal++, 1, idx);
                        valStrLen--;
                    }
                    // In case that valStrLen sval is shorter than valStrLen
                    if(precision_width > valStrLen){
                        valStrLen = precision_width - valStrLen;
                    }
                }
                else {
                    while(*sVal) {
                        idx = bufChr(*sVal++, 1, idx);
                    }
                }
                if(flags_used & flag_minus) {
                    if(field_width > valStrLen){
                        len = field_width - valStrLen;
                        idx = bufChr(' ', len, idx);
                    }
                }
            }
        }
        else {
            idx = bufChr(fmtChr, 1, idx);
        }
    }
    len = idx;
    if(len) {
        wrTxBuf(len);
    }

    return len;
}

/****************************************************************************
 * NumToString
 *
 * DESCRIPTION:
 *
 */
static int32_t NumToString(char *numStr,
                           void *numPtr,
                           int32_t neg,
                           int32_t radix,
                           bool use_caps) {
    int64_t a;
    int64_t b;
    int64_t c;

    uint64_t ua;
    uint64_t ub;
    uint64_t uc;

    int32_t len;
    char *tmp;

    len = 0;
    tmp = numStr;
    *tmp++ = '\0';
    if(neg) {
        a = *(int64_t *)numPtr;
        if(a == 0) {
            *tmp = '0';
            ++len;
            return len;
        }
        while(a != 0) {
            b = (int64_t)a / (int64_t)radix;
            c = (int64_t)a - ((int64_t)b * (int64_t)radix);
            if(c < 0) {
                uc = (uint64_t)c;
                c  = (int64_t)(~uc) + 1 + '0';
            }
            else {
                c = c + '0';
            }
            a = b;
            *tmp++ = (char)c;
            ++len;
        }
    }
    else {
        ua = *(uint64_t *)numPtr;
        if(ua == 0) {
            *tmp = '0';
            ++len;
            return len;
        }
        while(ua != 0) {
            ub = (uint64_t)ua / (uint64_t)radix;
            uc = (uint64_t)ua - ((uint64_t)ub * (uint64_t)radix);
            if(uc < 10) {
                uc = uc + '0';
            }
            else {
                uc = uc - 10 + (use_caps ? 'A' : 'a');
            }
            ua = ub;
            *tmp++ = (char)uc;
            ++len;
        }
    }
    return len;
}

/****************************************************************************
 * bufChr
 *
 * DESCRIPTION:
 *
 */
static int32_t bufChr(char chr,
                      int32_t len,
                      int32_t idx) {
    if(idx < TX_MAX){
        while(len--){
            txTmp[idx++] = chr;
        }
    }
    return idx;
}

/****************************************************************************
 * wrTxBuf
 *
 * DESCRIPTION:
 *
 */
static void wrTxBuf(int32_t len) {

    txTmp[len++] = '\0';
    slWriteMsg(SL_MSG_LOG,
               len,
               &txTmp[0]);
}

