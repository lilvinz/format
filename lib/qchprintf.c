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

/*****************************************************************************/
/* System Includes                                                           */
/*****************************************************************************/

#include <stdarg.h>
#include <stddef.h>

/*****************************************************************************/
/* Project Includes                                                          */
/*****************************************************************************/

#include "qchprintf.h"

#include "format.h"

#include "memstreams.h"

struct format_args
{
    void* channel_stream;
    systime_t timeout;
};

/*****************************************************************************/
/* Private function prototypes.  Declare as static.                          */
/*****************************************************************************/

/*****************************************************************************/
/**
    General output consumer function for streams.

    This function calls the generic putchar() function, which it is assumed is
    available in the target environment.

    @param op      Opaque pointer (UNUSED).
    @param buf     Pointer to input buffer.
    @param n       Number of characters from buffer to send to output.

    @return non-NULL.
**/
static void * outfunc_stream( void * op, const char * buf, size_t n )
{
    struct format_args* args = op;

    chSequentialStreamWrite( (BaseSequentialStream*)args->channel_stream, (const uint8_t*)buf, n );

    return op;
}

/**
    General output consumer function for channel.
    
    This function calls the generic putchar() function, which it is assumed is
    available in the target environment.
    
    @param op      Opaque pointer (UNUSED).
    @param buf     Pointer to input buffer.
    @param n       Number of characters from buffer to send to output.
    
    @return non-NULL.
**/
static void * outfunc_channel( void * op, const char * buf, size_t n )
{
    struct format_args* args = op;

    chnWriteTimeout( (BaseChannel*)args->channel_stream, (const uint8_t*)buf, n, args->timeout );

    return op;
}

/*****************************************************************************/
/* Public functions.  Declared as per header file.                           */
/*****************************************************************************/

/*****************************************************************************/
/**
    Produce output according to a format string, with optional argument list.
    
    @param fmt      Format specifier.
    @param ap       Argument list.
    
    @return Number of characters printed to the output, or -1.
**/
int qchvprintf ( BaseSequentialStream* stream, const char *fmt, va_list ap )
{
    struct format_args args =
    {
        .channel_stream = stream,
    };
    return format( outfunc_stream, &args, fmt, ap );
}

/**
    Produce output according to a format string, with optional argument list.

    @param fmt      Format specifier.
    @param ap       Argument list.

    @return Number of characters printed to the output, or -1.
**/
int qchvprintft ( BaseChannel* channel, systime_t timeout, const char *fmt, va_list ap )
{
    struct format_args args =
    {
        .channel_stream = channel,
        .timeout = timeout,
    };
    return format( outfunc_channel, &args, fmt, ap );
}

/*****************************************************************************/
/**
    Produce output according to a format string, with optional arguments.
    
    @param fmt      Format specifier.
    
    @return Number of characters printed to the output, or -1.
**/
int qchprintf ( BaseSequentialStream* stream, const char *fmt, ... )
{
    va_list arg;
    int done;
    
    va_start ( arg, fmt );
    done = qchvprintf( stream, fmt, arg );
    va_end ( arg );
    
    return done;
}

/**
    Produce output according to a format string, with optional arguments.

    @param fmt      Format specifier.

    @return Number of characters printed to the output, or -1.
**/
int qchprintft ( BaseChannel* channel, systime_t timeout, const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start ( arg, fmt );
    done = qchvprintft( channel, timeout, fmt, arg );
    va_end ( arg );

    return done;
}

/*****************************************************************************/
/**
    Produce output according to a format string, with optional arguments.

    @param buf      Output buffer.
    @param n        Length of output buffer.
    @param fmt      Format specifier.
    @param ap       Argument pointer.

    @return Number of characters written into the output buffer, or -1.
**/
int qchvsnprintf( char *buf, size_t n, const char *fmt, va_list ap )
{
    MemoryStream ms;
    BaseSequentialStream *chp;

    /* Memory stream object to be used as a string writer.*/
    msObjectInit(&ms, (uint8_t *)buf, n, 0);

    /* Performing the print operation using the common code.*/
    chp = (BaseSequentialStream *)&ms;
    qchvprintf(chp, fmt, ap);

    /* Final zero and size return.*/
    chSequentialStreamPut(chp, 0);
    return ms.eos - 1;
}

/*****************************************************************************/
/**
    Produce output according to a format string, with optional arguments.

    @param buf      Output buffer.
    @param n        Length of output buffer.
    @param fmt      Format specifier.

    @return Number of characters written into the output buffer, or -1.
**/
int qchsnprintf( char *buf, size_t n, const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start ( arg, fmt );
    done = qchvsnprintf( buf, n, fmt, arg );
    va_end ( arg );

    return done;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
