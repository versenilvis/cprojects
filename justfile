# you can use this justfile in root with "just ${filename}" and it will find that file and compile and run it
# E.g. just fw
# or even many files at once.
# E.g. just qr qrcodegen

[group('compile')]
[linux, macos]
cp *targets:
    #!/usr/bin/env bash
    srcs=""
    for name in {{targets}}; do
        file=$(find . -name "${name}.c" -print -quit)
        if [ -z "$file" ]; then
            echo "Cannot find ${name}.c"
            exit 1
        fi
        srcs="$srcs $file"
    done
    gcc -o a $srcs && ./a

clean:
    rm -f a
