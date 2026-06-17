# Agent Notes

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
