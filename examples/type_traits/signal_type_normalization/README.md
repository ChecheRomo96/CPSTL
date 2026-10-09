# Signal type normalization

Remove `const` and `volatile` qualifiers before applying generic signal logic.
The `static_assert` documents the compile-time guarantee; it has no runtime
cost on either desktop or embedded builds.
