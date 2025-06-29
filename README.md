# robscript

`robscript` is a lightweight C program builder. It allows you to combine
reusable "blocks" of C code with your own source files to quickly assemble
applications. Each block lives under the `blocks/` directory and exposes a
header and source file that you are free to edit.

The tool provided is `robbuilder`. It simply invokes `gcc` with all block
sources so you can focus on your program logic instead of a complicated build
system.

## Building robbuilder

```
cd src
make
```

This produces the `robbuilder` binary inside the `src` directory.

## Using robbuilder

Provide your C source files on the command line.  The helper compiles them
alongside every block under `../blocks/`.

```
./robbuilder ../examples/hello_main.c -o hello
./hello
```

### Adding your own blocks

1. Create `blocks/my_block.c` and `blocks/my_block.h`.
2. Implement any functions you like in that source file.
3. Include the header from your program.
4. Run `robbuilder` with your source file.

All `.c` files inside `blocks/` are automatically compiled.

## Example: simple web server

A small block named `web_block` demonstrates building a tiny HTTP server.
Compile and run the example with:

```
./robbuilder ../examples/web_main.c -o web_example
./web_example
```

Then visit <http://localhost:8080> in your browser to see a greeting generated
entirely from C code blocks.

## Included blocks

- `hello_block` – prints a greeting
- `math_block` – a minimal math helper
- `web_block` – serves a single HTTP response on port 8080
