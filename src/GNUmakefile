override KERNEL := "kernel.elf"

override LD=x86_64-elf-ld
override CC=x86_64-elf-gcc

# todo: allow stack check
override CFLAGS +=       \
    -std=c11             \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-lto             \
    -fno-pie             \
    -fno-pic             \
    -m64                 \
    -march=x86-64        \
    -mabi=sysv           \
    -mno-80387           \
    -mno-mmx             \
    -mno-sse             \
    -mno-sse2            \
    -mno-red-zone        \
    -mcmodel=kernel      \
    -MMD                 \
    -I../include         \
    -I../limine          \
    -O2

override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -T linker.ld            \
    -no-pie

override CFILES := $(shell find . -type f -name '*.c')
override ASFILES := $(shell find . -type f -name '*.S')
override OBJ := $(CFILES:.c=.o) $(ASFILES:.S=.o)
override HEADER_DEPS := $(CFILES:.c=.d) $(ASFILES:.S=.d)

.PHONY: all
all: $(KERNEL)
limine:
	cd ..;\
	if [ ! -d "limine" ]; then\
		clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1;\
		make -C limine;\
	fi
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@
-include HEADER_DEPS
%.o: %.c limine
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
%.o: %.S limine
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)
.PHONY: cleanup-after-build
cleanup-after-build:
	rm -rf $(OBJ) $(HEADER_DEPS)
