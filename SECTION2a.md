<p align="center">
<a href="SECTION1.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION3.md"><b>NEXT&nbsp;»</b></a>
</p>

The guidelines in this category are intended for visualizing the _logical code structure_ accurately and consistently, improve code readaility, minimize misinterpretation and withstand modifications. 

# 2. Layout
The fundamental principle underlying the guidelines in this section is that good layout needs to show the code's _structure_. If one technique shows the structure better and the other simply looks better, the one that represents the structure is preferred. Additionally, the preference is for layouts that can prevent errors due to misinterpretation as well as those that are more robust in view of likely changes, even if the layouts might not look as "neat" as the alternatives.


## Pure-Block Layout
Pure-block layout is based on the visualization of blocks of source code according to the following schematic view (see also [[CODE2]](README.md#07-references)):

```
XXXXXXXXXXXXXXXXXXXXXX
    YYYYYYYYYYYYY
    YYYYYYYYYYYYYYY
ZZZ
```
Where, line `XXXXXXX` begins the control block. The indented lines `YYYY` schematically show the statements hierarchically nested within the block. And finally, the line `ZZZ` explicitly ends the block. The alignment between `XXXXXXX` and `ZZZ` provides solid visual closure of the block.

The pure-block layout has three main benefits:
- it clearly shows the code structure;
- it eliminates possible misinterpretation with incorrect scope of the nested statements within a block;
- it is robust with respect of future modifications, such as adding or removing nested statements.

The concrete examples of this layout will be provided in the following guidelines, but the main point is that _all_ elements in the source code are formatted _consistently_ according to the same pure-block layout.


## 2.1 Indentation
Each level of scope within a block shall be indented by four (__4__) spaces.

__Rationale__<br>
Usability studies [[CODE2]](README.md#07-references) show that indentation of less than two spaces can be insufficient (especially for longer blocks of code), while indentation beyond 5 spaces does not improve code readability while increasing the need for wrapping long lines. Indentation of 4 spaces seems to be the "sweat spot".


## 2.2 Obligatory Braces
Use braces (`{...}`) to emulate the pure-block layout in C and C++.

__MISRA-C__<br>
This guideline overlaps the MISRA-C:2012 Rule 16.6 (Required) "The body of an iteration-statement and a selection-statement shall be a compound statement".

__Amplification__<br>
All blocks of code in a C or C++ must be surrounded by braces (`{...}`), even if not strictly required by the syntax.

__Rationale__<br>
In C and C++ the pure-block layout is not strictly enforced by the language syntax. For example, the following statement is syntactically correct, but is not a pure-block:

```
if (x < 0) 
    x = -x;
// missing the explicit end of the block
```
But the pure-block can be emulated by consistently applying braces (`{...}`) in all situations.

__Exception__<br>
The `if` statement immediately following an `else` need not be enclosed in a separate set of braces.

__Examples__<br>
```
/* compliant pure-block layout */
if (x < 0) {}
    x = -x;
}

if (x < 0) z = 25; /* NON-COMPLIANT, not a pure-block (no braces) */
else {
    z = 35; /* Compliant, braces used */
}

if (x < 0) {
    z = 25; /* Compliant, pure-block (braces used) */
}
else
    z = 35; /* NON-COMPLIANT, not a pure-block (no braces) */
    t = 25  /* incorrect indentation leads to misinterpretation */ 


if (flag1) {
    action1();
}
else { /* not necessary, see the next example */
	if (flag2) {
        action2();
    }
    else {
   	    //...
    }
}

if (flag1) {
    action1();
}
else if (flag2) { /* Compliant by exception */
    action2();
}
else {
	//...
}

/* NON-COMPLIANT, not a pure-block (no braces) */
while (millis() - start < TIMEOUT) ;

/* NON-COMPLIANT, not a pure-block (no braces) */
while (millis() - start < TIMEOUT)
    ;

/* Compliant, pure-block (braces used) */
while (millis() - start < TIMEOUT) {
}
```


# Enforcement


<p align="center">
<a href="SECTION1.md"><b>«&nbsp;PREVIOUS</b></a>&nbsp;|&nbsp;
<a href="README.md"><b>TOC</b></a>&nbsp;|&nbsp;
<a href="SECTION3.md"><b>NEXT&nbsp;»</b></a>
</p>
