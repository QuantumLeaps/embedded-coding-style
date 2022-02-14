[<b>« PREVIOUS</b>](README.md) <span style="float:right">[<b>NEXT »</b>](SECTION7.md)</span>

# 6. Object Oriented Programming in C
The following guidelines are intended to help in adoption of best practices from Object Oriented Programming into C programming. Contrary to widespread beliefs, it’s quite easy to implement encapsulation, single inheritance, and even polymorphism (late binding) in procedural languages, such as C [Samek 97]. Knowing how to implement encapsulation, inheritance, or even polymorphism in C can be very beneficial, because it leads to better code organization and better code reuse.

At the C programming level, encapsulation and inheritance become two simple design patterns. The following section describes the recommended ways of implementing these patterns.


## 6.1. Encapsulation
Encapsulation is the ability to package data with functions into classes. This concept should actually come as very familiar to any C programmer because it’s quite often used even in the traditional C. For example, in the Standard C runtime library, the family of functions that includes fopen(), fclose(), fread(), and fwrite() operates on objects of type FILE. The FILE structure is thus encapsulated because client programmers have no need to access the internal attributes of the FILE struct and instead the whole interface to files consists only of the aforementioned functions. You can think of the FILE structure and the associated C-functions that operate on it as the FILE class. The following bullet items summarize how the C runtime library implements the FILE "class": 

- Attributes of the class are defined with a C struct (the FILE struct). 
- Methods of the class are defined as C functions. Each function takes a pointer to the attribute structure (FILE *) as an argument. Class methods typically follow a common naming convention (e.g., all FILE class methods start with prefix f). 
- Special methods initialize and clean up the attribute structure (fopen() and fclose()). These methods play the roles of class constructor and destructor, respectively. 

This is exactly how QP/C and QP-nano frameworks implement classes. For instance, the following snippet of QP/C code declares the QActive (active object) "class". Please note that all class methods start with the class prefix ("QActive" in this case) and all take a pointer to the attribute structure as the first argument "me": 

```
typedef struct QActiveTag {
    QHsm super; /* inherit QHsm */
    . . .
/* private: */
    uint8_t prio; /* private priority of the active object */
} QActive; /* Active Object base struct */

/* public operations... */
int QActive_start(QActive * const me, uint8_t prio,
                  QEvent *qSto[], uint16_t qLen,
                  void *stkSto, uint32_t stkSize, 
                  QEvent const *ie);
void QActive_postFIFO(QActive * const me, QEvent const *e);
void QActive_postLIFO(QActive * const me, QEvent const *e);

/* protected operations ...*/
void QActive_ctor(QActive * const me, QPseudoState initial);
void QActive_xtor(QActive * const me);
void QActive_stop(QActive * const me);    /* stopps thread; nothing happens after */
void QActive_subscribe(QActive const * const me, QSignal sig);
*/
```

## 6.2 Inheritance
Inheritance is the ability to define new classes based on existing classes in order to reuse and organize code. QP/C and QP-nano implement single inheritance by literally embedding the parent class attribute structure as the first member of the child class structure. As shown in the following figure, this arrangement lets you treat any pointer to the Child class as a pointer to the Parent: 


In particular, such memory alignment of the Child attributes with the Parent attributes allows you to always pass a pointer to the Child class to a C function that expects a pointer to the Parent class. (To be strictly correct in C, you should explicitly upcast this pointer.) Therefore, all methods designed for the Parent class are automatically available to Child classes; that is, they are inherited. 

For example, in the code snippet from the previous section class QActive inherits from class QHsm. Please note the first protected attribute "super" of type QHsm in the QActive struct definition.



[<b>« PREVIOUS</b>](README.md) <span style="float:right">[<b>NEXT »</b>](SECTION7.md)</span>
