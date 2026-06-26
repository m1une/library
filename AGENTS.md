# Agent Notes

## Library Additions

When adding or updating library code, optimize for competitive programming use:
fast asymptotic complexity, small constant factors, predictable memory use, and
header-only ergonomics. Prefer well-known algorithms and data structures with
contest-proven behavior over clever but fragile variants.

Public APIs should be easy to handle during a contest:

* Match the style and naming of nearby headers.
* Keep constructors, query functions, and update functions simple and explicit.
* Use zero-based indices and half-open ranges where relevant.
* Add assertions for invalid indices, sizes, and times when the surrounding
  codebase does the same.
* Preserve old versions for persistent structures, and avoid hidden mutation in
  `const` methods.

Each new public header should usually have:

* A Markdown page under `docs/` with the same category path.
* Focused verification under `verify/`, including randomized tests against a
  naive implementation when practical.
* An update to the relevant README or index so the header is discoverable.

Documentation should be quick to understand and precise enough to use without
reading the source. Include:

* A short overview of what problem the structure solves.
* Any template requirements or algebraic assumptions.
* Exact public interface signatures in the methods table.
* Time complexity for every constructor and public method.
* Important behavioral notes, such as whether an update mutates the object,
  returns a new version, advances time, or can fail.
* A compact example that demonstrates the main workflow.

Before finishing a library addition, prefer verification against a relevant
problem from Library Checker, AOJ, yukicoder, or another judge already used in
this repository. Use `aplusb` only as a fallback when no suitable
library-specific verification problem is available; in that case, include
focused assertions and randomized tests against a naive implementation when
practical. Compile the relevant verification files with the repository's C++
standard, and run local tests when possible.

## Documentation Rendering

This repository's documentation is published through Jekyll/GitHub Pages, so
Liquid syntax is active while pages are generated. Do not introduce two
consecutive opening braces in Markdown examples, public headers, or verification
sources that may be rendered by verification-helper.

In C++ examples and source listings, prefer brace elision, explicit default
initialization plus assignments, `emplace_back`, or named expected values instead
of nested aggregate initializer shorthand that contains consecutive opening
braces. Otherwise the published page may silently drop or rewrite code.

Before finishing documentation or source changes, run:

```sh
rg -n "\\{\\{" .
```

The command should report no matches unless the occurrence is intentionally
protected from Liquid rendering.
