/******************************************************************************
 * File Name: std_types.h
 *
 * Description: header file for the standard types
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#ifndef std_types_H_
#define std_types_H_


/* Boolean and Standard Values */
#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#ifndef NULL
#define NULL            (void *)0
#endif

#define HIGH        (1u)
#define LOW         (0u)

/*Standard Types */
typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef float                 float32;
typedef double                float64;

#endif  /*std_types_H_*/
