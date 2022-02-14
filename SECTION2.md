<p align="center">
<a href="SECTION1.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION3.md"><b>NEXT&nbsp;»</b></a>
</p>

# 2. C/C++ Layout
The fundamental principle underlying the guidelines in this section is that good layout needs to show the _structure_ of the code clearly and accurately. If one technique shows the structure better and the other simply looks better, the one that represents the structure is preferred. Additionally, the preference is for layouts that can prevent errors due to misinterpretation as well as those that are more robust in view of likely changes, even if the layouts might not look as "neat" as the alternatives.

# 2.1 Pure-Block Layout
The general layout of C/C++ code shall be based on the _pure-block_ layout [[CODE2]](README.md#07-references)), which looks as follows:
```
<declarator | control-statement> {
    <statement>;
    . . .
}
```
where  `<declarator | control-statement>` may be one of the following: 
- function declarator
- structure/class declarator
- enumeration
- structure/array initializer
- control-statement (`if`, `else`, `while`, `do`, `for`, `switch` and `case`)

**Rationale**<br>
The pure-block layout has three main benefits:
- it clearly shows the code structure;
- it eliminates possible misinterpretation with incorrect scope of the nested statements or other blocks within a block;
- it is robust with respect of future modifications, such as adding or removing nested blocks.

Variations of the pure-block layout are used in several other coding styles ([K&R:78], [PPP:11], [FDS:11])

The concrete examples of this layout will be provided in the following sub-sections, but the main point is that _all_ elements in the source code are formatted _consistently_ according to the same pure-block layout.


# 2.2 Use of Braces
The statement following a `<control-statement>` (statement beginning with: `if`, `else`, `while`, `do`, `for`, `switch` and `case`) must be compound, that is, use of braces (`{...}`) is **obligatory**.

This requirement corresponds to MISRA-C rule 59. Although not strictly required by the C/C++ syntax, this rule is imposed to remove any doubts as far as statement nesting is concerned, and to allow easy addition/removal of nested statements with minimal differences showing when differencing the code using a VCS. For example, consider adding a statement to a while loop:

```
/* not a compound statement—NOT RECOMMENDED */    /* compound statement-RECOMMENDED */
while (i > 0)                                     while (i > 0) {
    *t++ = *s++;                                      *t++ = *s++;
                                                  }
```

after modification:

```
/* not a compound statement—NOT RECOMMENDED */    /* compound statement-RECOMMENDED */
while (i > 0)                                     while (i > 0) {
    *t++ = *s++;                                      *t++ = *s++;
    --i;                                              --i;
                                                  }
```

With the not-compound statement case you either make a mistake by forgetting the braces (although the indentation clearly indicates the intention), or you must introduce the braces, which then show as a big difference when merging the code or checking it into the VCS.
If the `<declarator | control-statement>` is so complex that it cannot fit in one line, then it should be formatted in the following manner: 

```
<declarator | control-statement ...>
    <... declarator | control-statement ...>
    <... declarator | control-statement>
{
    <statement>;
    . . .
}
```

The arguments of a declarator should be split into separate lines leaving separating comma ‘,’ as the last character in the line. The condition of the control statement should be split into separate lines starting new lines with a binary operator. This formatting intends to avoid confusing continuation of the control statement with its body. For example:

```
if (!decodeData(&s, &dataType, 
        &format, &version)
    && (format != 2U)    /* expecting only format 2 */
    && (version != 1U))  /* expecting only version 1 */
{
    log("data corrupt");
}
```

### 3.2.1 The `if` Statement

```
if (x < 0) {
    z = 25; 
} 
if (--cnt == 0) { 
    z = 10; 
    cnt = 1000; 
}
else {
    z = 200; 
}
if (x > y) { 
    foo(x, y); 
    z = 100; 
}
else {
    if (y < x) { 
        foo(y, x); 
        z = 200; 
    } 
    else { 
        x = 0; 
        y = 0; 
    } 
}
```

### 3.2.2 The `for` Statement
```
for (i = 0; i < MAX_ITER; ++i) {
    *p2++ = *p1++;
    xx[i] = 0; 
}
```

### 3.2.3 The `while` Statement
```
while (--ctr != 0) {
    *p2++ = *p1++; 
    *p3++ = 0; 
}
```

### 3.2.4 The `do..while` Statement
```
do { 
    --ctr; 
    *p2++ = *p1++; 
} while (cnt > 0);
```

# 3.2.5. The `switch` Statement
```
switch (key) {
    case KEY_BS: {
        if (--me->ctr == 0) { 
            me->ctr = PERIOD; 
        } 
        break;
    }
    case KEY_CR: {
        ++me->crCtr;
        /* intentionally fall through */
    }
    case KEY_LF: {
        ++p;
        break;
    }
    default: {
        Q_ERROR(); /* should never be reached */
        break;
    }
}
```

Any fall though cases must be documented with comments confirming intentional fall through rather then an omission. 


### 3.2.6 Function Definition
```
void clrBuf(char *buf[], int len) { 
    char *b = &buf[0]; 
    while (len-- != 0) { 
        *b++ = '\0'; 
    } 
}
```

### 3.2.7 C++ Class Declaration
```
class Foo : public Bar { 
public: 
    Foo(int8_t x, int16_t y, int32_t z)    // ctor
        : Bar(x, y), m_z(z)
    {}
    virtual ~Foo();                        // xtor
    virtual int32_t doSomething(int8_t x); // operation

protected: 
    virtual void *bar();

private:
    friend class Tar; 
    friend void *fxyz(int16_t i);

    int8_t   m_x;
    uint16_t m_y;
    int32_t  m_z;
};
```
# 3.1 Expressions
The following binary operators are written with no space around them: 

|   Operator | Description                | Example           |
| ---------- | -------------------------- | ----------------- |
| `->`       | Structure pointer operator | `me->foo`         |
| `.`        | Structure member operator  | `s.foo`           |
| `[]`       | Array subscripting         | `a[i]`            |
| `()`       | Function call              | `foo(x, y, z);`   |


Parentheses after function names have no space before them. A space should be introduced after each comma to separate each actual argument in a function. Expressions within parentheses are written with no space after the opening parenthesis and no space before the closing parenthesis. Terminating semicolons should follow the instructions immediately with no space(s) before them: 
`strncat(t, s, n);`

The unary operators are written with no spaces between them and their operands: 
```
!p     ~b    ++i     j--     (void *)ptr    *p     &x   -k
```

The binary operators are preceded and followed by one (1) space, as is the ternary operator: 
```
c1 == c2     x + y     i += 2     n > 0 ? n : -n
```
The keywords: `if`, `while`, `for`, `switch` and `return` are followed by one (1) space: 
```
return foo(me->x) + y;
```

In case of compound expressions, parenthesizing should be used whenever the precedence is not "obvious". In general, over parenthesizing is recommended to remove any doubt and guessing. In the extreme case of MISRA-C Rules [MISRA 98], no dependence should be placed on C’s operator precedence whatsoever (MISRA-C rule 47), so every expression must be parenthesized. In addition, MISRA rules require that the operands of && and || shall be primary expressions (MISRA-C rule 34).
Following are examples of parenthesizing consistent with the strict MISRA-C rules: 
(a < b) && (b < c) /* operands of && are primary expressions (MISRA rule 34) */
x = (a * b) + c;                  /* don’t rely on precedence of ‘*’over ‘+’ */

<p align="center">
<a href="SECTION1.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION3.md"><b>NEXT&nbsp;»</b></a>
</p>

