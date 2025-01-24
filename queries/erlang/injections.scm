(call
  expr: (remote
    module: (remote_module
      module: (atom) @module (#eq? @module "arizona_render"))
    fun: (atom) @fun (#match? @fun "^view_template|component_template$"))
  args: (expr_args
    args: (var)
    args: (var)
    args: (string) @injection.content
            (#gsub! @injection.content "\"+(.*)[^\"]" "%1")
            (#set! injection.language "herl")
            (#set! injection.include-children)))

(call
  expr: (remote
    module: (remote_module
      module: (atom) @module (#eq? @module "arizona_render"))
    fun: (atom) @fun (#eq? @fun "template"))
  args: (expr_args
    args: (string) @injection.content
            (#gsub! @injection.content "\"+(.*)[^\"]" "%1")
            (#set! injection.language "herl")
            (#set! injection.include-children)))
