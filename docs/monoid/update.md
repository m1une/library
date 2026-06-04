---
title: Update Monoid
documentation_of: ../../monoid/update.hpp
---

## Overview

A monoid for range updates/assignments. It uses `std::optional<T>` to safely represent whether an assignment operation exists or not (the identity element is `std::nullopt`).

When two operations are composed, the newer operation (on the left, when applied) completely overwrites the older operation (on the right), unless the newer operation is empty.

## Template Parameters

* `T`: The underlying data type being assigned.
