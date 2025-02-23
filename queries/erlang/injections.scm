; arizona_render:view_template/2 orelse
; arizona_render:component_template/2 orelse
; arizona_render:nested_template/2
(call
  expr: (remote
    module: (remote_module
      module: (atom) @module (#eq? @module "arizona_render"))
    fun: (atom) @fun (#any-of? @fun "view_template" "component_template" "nested_template"))
  args: (expr_args
    args: (_) ; First argument (View)
    args: (string) @injection.content ; Second argument (Template)
            (#set! injection.language "herl")
            (#set! injection.include-children)))

; arizona_render:nested_template/1
(call
  expr: (remote
    module: (remote_module
      module: (atom) @module (#eq? @module "arizona_render"))
    fun: (atom) @fun (#eq? @fun "nested_template"))
  args: (expr_args
    args: (string) @injection.content ; First argument (Template)
            (#set! injection.language "herl")
            (#set! injection.include-children)))

; arizona_scanner:scan/2
(call
  expr: (remote
    module: (remote_module
      module: (atom) @module (#eq? @module "arizona_scanner"))
    fun: (atom) @fun (#eq? @fun "scan"))
  args: (expr_args
    args: (_)  ; First argument (Options)
    args: (string) @injection.content ; Second argument (Template)
            (#set! injection.language "herl")
            (#set! injection.include-children)))
