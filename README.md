# tree-sitter-herl

Injects HTML and Erlang languages in `.herl` files.
The code between curly braces is Erlang and the rest is HTML.

## Example

### HErl File

In a `*.herl` file:

```herl
<div>Hello, {maps:get(name, Who, ~"World")}!</div>
```

The injection transforms it into mixed HTML and Erlang tokens:

```text
(tokens ; [0, 0] - [1, 0]
  (document ; [0, 0] - [1, 0]
    (element ; [0, 0] - [0, 50]
      (start_tag ; [0, 0] - [0, 5]
        (tag_name)) ; [0, 1] - [0, 4]
      (text) ; [0, 5] - [0, 44]
      (end_tag ; [0, 44] - [0, 50]
        (tag_name)))) ; [0, 46] - [0, 49]
  (text) ; [0, 0] - [0, 12]
  (expression ; [0, 13] - [0, 42]
    (source_file ; [0, 13] - [0, 42]
      exprs: (call ; [0, 13] - [0, 42]
        expr: (remote ; [0, 13] - [0, 21]
          module: (remote_module ; [0, 13] - [0, 18]
            module: (atom)) ; [0, 13] - [0, 17]
          fun: (atom)) ; [0, 18] - [0, 21]
        args: (expr_args ; [0, 21] - [0, 42]
          args: (atom) ; [0, 22] - [0, 26]
          args: (var) ; [0, 28] - [0, 31]
          args: (string))))) ; [0, 33] - [0, 41]
  (text)) ; [0, 43] - [1, 0]
```

That is highlighted as:

![HErl highlight example][herl_highlight_example]

### Erlang

In a Erlang `*.erl` file:

```erl
-module(hello).
-export([world/1]).

world(View) ->
    arizona_render:view_template(View, ~"""
    <div>Hello, {maps:get(name, Who, ~"World")}!</div>
    """).
```

It is highlighted as:

![Erl highlight example][erl_highlight_example]

> [!NOTE]
>
> **Atom Highlighting Issue**
>
> Currently, atoms in Erlang code are not highlighted correctly due to a priority
> conflict in the Tree-sitter grammar. Specifically:
>
> - Atoms are captured as `@constant.erlang` with a priority of `90`.
> - Strings (`@string.erlang`) have a higher priority of `100`, causing them to
>   take precedence over atoms.
>
> When using the `:Inspect` command in Neovim, you’ll see the following:
>
> ```text
> Treesitter
>  - @string.erlang links to String   priority: 100   language: erlang
>  - @erlang.herl links to @erlang   priority: 100   language: herl
>  - @constant.erlang links to Constant   priority: 90   language: erlang
>  - @none.html links to @none   priority: 100   language: html
>  - @spell.html links to @spell   priority: 100   language: html
> ```
>
> **Attempted Solutions**
>
> - Overriding the priority for `@constant.erlang` via `injections.scm` and
>   `highlights.scm` did not resolve the issue.
> - The root cause may lie in the Erlang Tree-sitter grammar itself, where the
>   priority for `@constant.erlang` is set lower than `@string.erlang`.
>
> **Next Steps**
>
> This issue might need to be addressed in the Erlang Tree-sitter grammar by
> increasing the priority of `@constant.erlang` to ensure atoms are highlighted
> correctly.
>
> Contributions or suggestions for resolving this issue are welcome!

[herl_highlight_example]: ./assets/herl_highlight_example.png
[erl_highlight_example]: ./assets/erl_highlight_example.png
