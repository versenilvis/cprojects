# you can use this makefile in root with "make ${filename}" and it will find that file and compile and run it
SRCS := $(shell find . -name "*.c")

%:
	@$(eval TARGET_FILE := $(shell find . -name "$*.c" -print -quit))
	@if [ -z "$(TARGET_FILE)" ]; then \
		echo "Cannot find file $*.c in any subfolder"; \
	else \
		gcc -o a "$(TARGET_FILE)" && ./a; \
	fi
clean:
	rm -f a
