((tokens
  (text) @injection.content)
  (#set! injection.language "html")
  (#set! injection.combined))

((tokens
  (expression) @injection.content)
  (#set! injection.language "erlang"))
