[<b>« PREVIOUS</b>](SECTION6.md) <span style="float:right">[<b>NEXT »</b>](SECTION8.md)</span>

# 7. Design by Contract

Design by Contract is a very powerful set of techniques introduced by Bertrand Meyer [Meyer 97]. The techniques are based on the concept of contract that formally captures assumptions and delicate dependencies between software components. The central idea is to enforce fulfillment of these contracts by instrumenting code and explicit checking against contract violations. Contracts may be in form of preconditions, postconditions and invariants. In C/C++ they are implemented in form of assertions. Some of the listed benefits of Design by Contract include [Samek 03]:

- A better understanding of software construction
- A systematic approach to building bug free systems
- An effective framework for debugging, testing and, more generally, Software Quality Assurance (SQA) 
- A method for documenting software components
- Better understanding and control of code reuse
- A technique for dealing with abnormal cases, leading to a sage and effective language constructs for exception handling. 

In deeply embedded systems, assertion failure must be treated differently than on desktop computers. Typically, standard actions of printing out assertion failure statement and exit are not the right approach. For that reason a customized behavior in case of contract violation is coded in "qassert.h" include file [QL 04]. This header file defines the following assertions:

| Macro               | Purpose                       |
| ------------------- | ----------------------------- |
| `Q_ASSERT()`        | General-purpose assertions    |
| `Q_ALLEGE()`        | Assertions with side-effects in testing the expression,<br> when the side effects are desired even if assertions are disabled |
| `Q_REQUIRE()`       | For asserting preconditions   |
| `Q_ENSURE()`        | For asserting postconditions  |
| `Q_INVARIANT()`     | For asserting invariants      |
| `Q_ERROR()`         | For asserting incorrect paths through the code |
| `Q_ASSERT_STATIC()` | For static, compile-time assertions |

[<b>« PREVIOUS</b>](SECTION6.md) <span style="float:right">[<b>NEXT »</b>](SECTION8.md)</span>
