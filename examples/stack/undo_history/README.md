# Undo history

Use `cpstd::stack` for last-in-first-out user actions. Inspect `top` before
`pop`; an application should also check `empty` before undoing when no action
has been recorded.
