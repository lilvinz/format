/* ****************************************************************************
 * Format - lightweight string formatting library.
 * Copyright (C) 2011, Neil Johnson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ************************************************************************* */

#ifndef PRINTF_H
#define PRINTF_H

#include "hal.h"

#include <stdarg.h> /* for va_list */
#include <stddef.h> /* for size_t */

extern int qchprintf( BaseSequentialStream* stream, const char *, ... );
extern int qchprintft( BaseChannel* channel, systime_t timeout, const char *, ... );
extern int qchsnprintf( char *, size_t, const char *, ... );

extern int qchvprintf( BaseSequentialStream* stream, const char *, va_list );
extern int qchvprintft( BaseChannel* channel, systime_t timeout, const char *, va_list );
extern int qchvsnprintf( char *, size_t, const char *, va_list );

#if FORMAT_INCLUDE_FATFS
#if HAS_FATFS
#include "ff.h"
#else
#include "fatfs_posix.h"
#endif
extern int qchfprintf( FIL* fp, const char *, ... );
extern int qchfvprintf( FIL* fp, const char *, va_list );
#endif /* FORMAT_INCLUDE_FATFS */

#endif /* PRINTF_H */

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
