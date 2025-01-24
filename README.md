# tree-sitter-herl

Injects HTML and Erlang languages in `.herl` files.
The code between curly braces is Erlang and the rest is HTML.

## Example

In a `*.herl` file:

```herl
<div>Hello, {maps:get(name, Who, world)}!</div>
```

The tree-sitter parses the file content as:

```text
(tokens [0, 0] - [1, 0]
  (text [0, 0] - [0, 12])        ; "<div>Hello, "
  (expression [0, 13] - [0, 39]) ; "maps:get(name, Who, world)"
  (text [0, 40] - [1, 0]))       ; "!</div>"
```

The injection transforms it into:

```text
(tokens ; [0, 0] - [1, 0]
  (document ; [0, 0] - [1, 0]
    (element ; [0, 0] - [0, 47]
      (start_tag ; [0, 0] - [0, 5]
        (tag_name)) ; [0, 1] - [0, 4]
      (text) ; [0, 5] - [0, 41]
      (end_tag ; [0, 41] - [0, 47]
        (tag_name)))) ; [0, 43] - [0, 46]
  (text) ; [0, 0] - [0, 12]
  (expression ; [0, 13] - [0, 39]
    (source_file ; [0, 13] - [0, 39]
      exprs: (call ; [0, 13] - [0, 39]
        expr: (remote ; [0, 13] - [0, 21]
          module: (remote_module ; [0, 13] - [0, 18]
            module: (atom)) ; [0, 13] - [0, 17]
          fun: (atom)) ; [0, 18] - [0, 21]
        args: (expr_args ; [0, 21] - [0, 39]
          args: (atom) ; [0, 22] - [0, 26]
          args: (var) ; [0, 28] - [0, 31]
          args: (atom))))) ; [0, 33] - [0, 38]
  (text)) ; [0, 40] - [1, 0]
```

That is highlighted as:

![Example][example]

[example]: ./assets/example.png
