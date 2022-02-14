<p align="center">
<a href="SECTION2.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION4.md"><b>NEXT&nbsp;»</b></a>
</p>

# 3. Commenting
Code implements an algorithm; the comments communicate the code’s operation to yourself and others. Adequate comments allow you to understand the system’s operation without having to read the code itself. 
Comments can be generally divided into three categories: 

- Elaborate high-level comments for major software components like: modules, classes, and exported APIs. 
- Brief, fine granularity comments explaining algorithmic details of performed operations. 
- References and notes attached to code in form of comments. 

Comments in the first category explain high level interfaces and the code structure. With help of automatic documentation generating tools like JavaDoc for Java or DOC++ for C/C++, these comments can easily be turned into online (HTML) documentation. The Standard does not require that every top-level comment be verified in view of converting it into on-line documentation. However, adhering to the following simple rules will make such automatic documentation extraction much easier, if we want to take advantage of it: 
Top-level comments should always come before the commented object.
No right-edge in comment boxes should be used, because keeping the right-edge of the box aligned is counterproductive:

```
/* INCORRECT: */ 
/*******************************************************************************
* this is class Foo                                                            *
* . . .                                                                        *
*******************************************************************************/
class Foo { 
    ... 
};

// CORRECT: 
//==============================================================================
// class Foo performs the following 
// ... 
//
class Foo { 
    ... 
};
```

Comments in the second category are typically low-level, algorithmic details. They should be placed as close to the pertaining code as possible, preferably in the same line. Although close to the code, the comments should be visually separated from code as much as possible by right-justifying them. Following section gives examples of aligning such comments: 
References and notes should be attached in form of the "notes" comment at the end of the module as shown in the next section describing the module layout.
 
Write comments in clear English. Use simple sentences: noun, verb, object. Use active voice. Be complete. Good comments capture everything important about the problem at hand. Ideally, it should be possible to get a sense of the system’s operation by reading only the comments.
 
For portability, not use C++ comments (`//`) in C, although many C99 compilers recognize C++ comments. (But the point is that some don’t!). Conversely, avoid using C comments (`/*..*/`) in C++.


## 3.4 Module Layout
The module is organized as follows: 

- Header comment block
- `#include` statements
- Public Section Specification
- Package Section Specification
- Local Section Specification
- Implementation
- Notes

### 3.4.1 Header Comment
Each module starts with a header comment in the following format: 

```
/*==============================================================================
* Product:  . . 
* Version:  . . 
* Updated:  Dec 17 2004
*
* Copyright (C) 2002-2004 Quantum Leaps. All rights reserved.
*
* <licensing terms> (if any)
*
* <Company contact information>
==============================================================================*/
```

### 3.4.2. Included Header Files
```
#include "rtk.h"      /* Real-Time Kernel */
#include "qassert.h"  /* embedded-systems-friendly assertions */
```

### 3.4.3. Public Section Specification
Definitions of public (global) variables should appear at the top of the module: 

```
/* Public-scope objects ---------------------------------------------------*/
QActive *UI_Mgr; /* pointer to the User Interface Manager active object */
. . .
```

### 3.4.4 Package Section Specification
The public (global) variables should be followed by all package-scope variables: 

```
/* Package-scope objects -----------------------------------------------------*/
QEvent const QEP_stdEvt[] = {
    { Q_EMPTY_SIG, 0},
    { Q_INIT_SIG,  0},
    { Q_ENTRY_SIG, 0},
    { Q_EXIT_SIG,  0}
};
```

### 3.4.5 Local Section Specification
The package-scope variables should be followed by local (module-scope) declarations and local variables (module-scope). All local-scope variables should be defined static.

```
/* Local-scope objects -------------------------------------------------------*/
static uint32_t l_svMask;    /* Space Vehicle mask indicating allocated SVs */
. . .
```

### 3.4.6 Implementation Section
The implementation section contains function definitions (in C) or class method definitions (in C++). Regardless of language, keep functions small. The ideal size is less than a page; in no case should a function ever exceed two pages. Break large functions into several smaller ones.

The only exception to this rule is the very rare case where you must handle very many events in one state handler. However, even in this case you should try to use state nesting (behavioral inheritance) to move some of the events to higher-level state handlers (See also [Samek 02, Section 4.3.1]).

Define a prototype for every function, even the static helper functions called only from within their own module. (The good place for such static prototypes is the local-scope section.) Prototypes let the compiler catch the all-too-common errors of incorrect argument types and improper numbers of arguments. They are cheap insurance.
In general, function names should follow the variable naming conventions (see below). Remember that functions are the “verbs” in programs - they do things. Incorporate the concept of “action words” into the variables’ names. For example, use “readAD” instead of “ADdata”.

Elaborate function comments (or class method comments in C++) should be placed in the header files, since the header files form the API documentation. These comments, generally, should not be repeated in the implementation section because this would create double points of maintenance. The comments at function definitions should rather refer to implementation details and revision history. At a minimum, the functions should be visually separated from each other.

```
/*............................................................................*/
void swap(int *x, int *y) {
    /* @pre pointers must be valid */
    Q_REQUIRE((x != (int *)0) && (y != (int *)0));
    int temp = *x; /* store value of x in a temporary */
    *x = *y;
    *y = temp;
}
/*..........................................................................*/
int pow(int base, unsigned int exponent) {
    uint_fast8_t result = 1U;
    for (; exponent > 0U; exponent >>= 1U) {
        if ((exponent & 1U) != 0U) { /* exponent is odd? */
            result *= base;
        }
        base *= base;
    }
    return result;
}
```

### 3.4.7 Notes Section
The Notes Section is the ideal place for longer explanations that apply to multiple sections of code or would otherwise distract the reader when placed directly at the code. In the pertinent code you place just a reference to the Note:

```
/*............................................................................*/
void interrupt dumpISR() {
    . . . /* dump channel data to RAM, see NOTE03 */
}

At the end of the module, you place the Notes Section:
/*==============================================================================
* . . .
*
* NOTE03: 
* this system has two hard real-time constraints: 
* #1 processing of channel DUMP data must complete before next DUMP 
*    for the channel. This constraint is ensured in Assertion (NOTE03.1). 
* 
* #2 no accumulated data can be missed due to new DUMP for a channel 
*    before the previous data has been read. This constraint is ensured 
*    in Assertion (NOTE03.2). 
*/
```

# 4. Exact-Width Integer Types

Avoid the use of "raw" C/C++ types, as these declarations vary depending on the machine (MISRA-C rule 13). The recommended strategy is to always use a C99 `<stdint.h>` header file [C99, Section 7.18]. In case this standard header file is not available (e.g., in a pre-standard compiler), you should create it and place in the compiler’s include directory. At a minimum, this file should contain the typedefs for the following exact-width integer data types [C99 Section 7.18.1.1]:

| exact size  | signed     | unsigned    |
| ----------- | ---------- | ----------- |
| 8 bits      | `int8_t`   | `uint8_t`   |
| 16 bits     | `int16_t`  | `uint16_t`  |
| 32 bits     | `int32_t`  | `uint32_t   | 

The main goal of the <stdint.h> indirection layer is promotion of code portability across different platforms. To achieve this goal the C99-style types listed above should be consistently used instead of the "raw" C/C++ types, such as long or unsigned char, and inventing different aliases for the C/C++ types is forbidden. 


# 5 Names

## 5.1 Reserved Names
The ANSI C specification restricts the use of names that begin with an underscore and either an uppercase letter or another underscore (regular expression: _[A-Z_][0-9A-Za-z_]). Much compiler runtime code also starts with leading underscores. 

These names are also reserved by ANSI for its future expansion: 

| Regular expression               | purpose                     |
| -------------------------------- | --------------------------- |
| `E[0-9A-Z][0-9A-Za-z]*`          | POSIX errno values          |     
| `is[a-z][0-9A-Za-z]*`            | character classification    |
| `to[a-z][0-9A-Za-z]*`            | character manipulation      |
| `LC_[0-9A-Za-z_]*`               | locale                      |
| `SIG[_A-Z][0-9A-Za-z_]*`         | POSIX signals               |
| `str[a-z][0-9A-Za-z_]*`          | string manipulation         |
| `mem[a-z][0-9A-Za-z_]*`          | memory manipulation         | 
| `wcs[a-z][0-9A-Za-z_]*`          | wide character manipulation |

To improve portability and avoid name conflicts, never use a name with a leading underscore or one of the name patterns reserved for future expansion.


## 5.2 Naming Conventions
This section does not intend to impose strict "Hungarian-type" notation. However, the following simple rules in naming various identifiers are strongly recommended:

- No identifier should be longer than 31 characters (this is a stricter version of MISRA-C rule 11).
- Type names (typedef, sturct and class) should start with an upper-case letter e.g., struct Foo. Optionally, the type name can be prefixed with the module identifier, e.g., typedef uint16_t QSignal, class QActive.
- Ordinary C functions and C++ class member functions start with a lower-case letter. 
- Member functions of classes coded in C (see Section 6) are prefixed with the class name and an underscore, so per the previous rule must begin with an upper-case letter. (QActive_start()). Besides clearly distinguishing the member functions, this rule minimizes link-time name conflicts with other functions (including third-party library functions).
- Global functions are prefixed with a module name and an underscore (e.g., QF_start()). Package-scope functions, visible only from a closely related group of source files—the package, are additionally suffixed with an underscore (QF_add_()). Besides clearly distinguishing global and package-scope functions, this rule minimizes link-time name conflicts with other functions (including third-party library functions).
- Ordinary variables should start with a lower-case letter (foo).
- Global variables should be prefixed with the module name and an underscore (e.g., QK_readySet).
- Local variables (visible within one module only) should start with “l_”, e.g., l_bitmask. All local variables should be declared static at the file scope (MISRA-C rule 23).
- C++ class attributes (data members) should should start with “m_”, e.g. int8_t m_foo. This convention allows easy distinction between the class data members and other variables like, for example, member function arguments. 
- Constants (numeric macros or enumerations) should be in upper-case with underscores "_" between each word or abbreviation (FOO_BAR). Global constants should be prefixed with the module name/identifier (Q_USER_SIG).
- All other parts of identifiers composed form multiple words should be constructed with capitalizing letters at word boundaries like: fooBarTar, and not foo_bar_tar.
- Generally, the more broad the scope the more descriptive the name should be. For a very limited scope, it is recommended to use single letter identifiers. For example: 
   + `i, j, k, m, n,` for integers like loop counters
   + `p, q, r, s, t, u, v, w,` for pointers or floating point numbers

<p align="center">
<a href="SECTION1.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION3.md"><b>NEXT&nbsp;»</b></a>
</p>

