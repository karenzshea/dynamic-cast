# [substitution failure is not an error](https://en.cppreference.com/w/cpp/language/sfinae)

## terms

term | definition
--- | ---
error           | A flaw in a program that causes it to behave in unexpected ways, or in ways the program was not designed to handle.
failure         | A situation where the software has ceased to deliver the expected result with respect to the specification input values.

- substition failure is therefore, somewhat expected, and compilers are designed to handle them
- refers to concept relied on to use function templates

## How function templates are processed by the compiler

[overload resolution](https://en.cppreference.com/w/cpp/language/overload_resolution)

Overload resolution is the process that takes place to select the most appropriate
function to call when there is more than one candidate for a function call.

### [Name Lookup](https://en.cppreference.com/w/cpp/language/lookup)
Name lookup is the procedure by which a name, when encountered in a program, is
associated with the declaration that introduced it.

Compiler finds where the (template) function declaration is in all the files you've given it

### Come up with candidates
Compiler assembles a set of candidate functions from function overloads and synthesized
specialized functions based on function templates;
(interesting note: Member functions have implied object arguments, i.e. the objects they are part of.)
(interesting note: Template specializations are not considered in overload resolution at all)

#### [Argument Type Deduction](https://en.cppreference.com/w/cpp/language/template_argument_deduction) / [Type Substitution](https://en.cppreference.com/w/cpp/language/function_template#Template_argument_substitution)
Compiler figures out what kind of type has been passed in to the function template
and attempts to substitute it into the function template. It synthesizes
a function declaration.

Compiler will try all given templates and overloads until it either finds that it
can use the given types exactly, or it returns an error.

There are a few ways to fix these substitution errors:
- template specialization
- modifying the template
- overload the template function

Exhaustive list of where failures can happen: https://en.cppreference.com/w/cpp/language/sfinae#Type_SFINAE

### Best candidate is picked
Pick the best, most viable, most specialize function.
Depends on context in which overload resolution happens, and difference between
qualities of all the candidate functions, i.e. least generic, fewest
implicit conversions, etc.

[Example when compiler gives you candidate suggestions!]

### Function specialization is instantiated
If a synthesized function declaration is deemed the best candidate, then the specialization
of that function is instantiated and compiled.


## resources
- https://medium.com/@MKahsari/sfinae-step-by-step-67e6ef6154da
- https://jguegant.github.io/blogs/tech/sfinae-introduction.html
- https://www.youtube.com/watch?v=NIDEjY5ywqU

# activities
- compile template without calling templated Fight, see that Fight doesn't appear in compiled code
- write Fight call with different combinations of Creatures, see the generated code
- try to compile call Fight with Healer type
