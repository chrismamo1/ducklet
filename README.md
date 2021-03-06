# Ducklet

Ducklet is an experimental application server written in C to facilitate the
development of web applications with arbitrary languages and frameworks.

## Ducklet Server

The Ducklet server is a thin web server written entirely in C. It is extremely
minimalistic, intended to be run behind a reverse-proxy. It is configured
through a `ducklet.conf` file which is structured as an HTTP header, in order to
save the effort of writing an additional configuration parser or introducing a
new dependency.

## Ducklet Compiler

The Ducklet compiler is a small and truly horrifying Perl script for converting
Ducklet templates into source code files in languages such as C and OCaml, which
may then be used with the Ducklet Server.

## Hello, Ducklet!.ml.html

```
<html>
  <title>
    <?ml
      Random.self_init();;
      Printf.printf "%d" (Random.int 10_000);;
    ?>
  </title>
  <body></body>
</html>
```

## Why use Ducklet?

The Ducklet compiler is easily extended, so Ducklet applications may be written
in essentially any programming language. This enables developers to write
server-side code in the best language for the application without relying on the
existence of extensive web programming toolkits for the language.

## To-do

 * Right now, the Ducklet server uses recipes specified in a site's
 `ducklet.conf` to serve resources. This method is less than ideal because it
 may execute arbitrary code and it requires quite a bit of overhead (dynamic
 resources must be invoked using `popen`, which creates an entirely new process
 and file descriptor which must be managed). I would prefer to use dynamic
 linking where possible in order to minimize runtime overhead and complexity.
