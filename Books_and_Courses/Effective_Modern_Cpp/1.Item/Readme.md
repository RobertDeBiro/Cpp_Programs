# Understand template type deduction

Template function:  

    template<typename T>
    void f(ParamType param);

Template function call:  

    f(expr)

- during compilation, compilers use *expr* to deduce two types:
    - one for T
    - one for *ParamType*
- these types are frequently different, because *ParamType* often contains adornments, e.g. **const** or **reference** qualifiers
- the type deduced for T is dependent not just on the type of *expr*, but also on the form of *ParamType*:
    - Case1: *ParamType* is a pointer or reference type, but not a universal reference
    - Case2: *ParamType* is a universal reference
    - Case3: *ParamType* is neither a pointer nor a reference