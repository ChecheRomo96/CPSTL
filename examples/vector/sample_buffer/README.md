# Sample buffer

Use `reserve` to establish a capture budget and inspect `size` versus
`capacity`. A full application should reserve for its worst expected burst and
observe whether a growth operation could not change the container.
