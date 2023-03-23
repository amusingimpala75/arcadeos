.PHONY: all
all:

.PHONY: build
build:
	rm -rf ./kernel.elf
	make -C src -j `nproc`
	make -C src cleanup-after-build
	mv src/kernel.elf ./
.PHONY: clean
clean:
	make -C src clean
.PHONY: iso
iso: build
	rm -rf iso
	mkdir iso
	cp limine/limine.sys limine/*.bin kernel.elf limine.cfg iso/
	mkdir -p iso/EFI/BOOT
	cp limine/*.EFI iso/EFI/BOOT/
	xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-cd-efi.bin \
		--efi-boot-part --efi-boot-image --protective-msdos-label iso -o arcadeos.iso &> /dev/null
	limine/limine-deploy arcadeos.iso &> /dev/null
	rm -rf iso
.PHONY: run
run: iso
	qemu-system-x86_64 -cdrom arcadeos.iso -no-reboot -smp 2 -serial stdio
.PHONY: burn
burn: iso
	diskutil list
	@read -p "Which disk to burn to? " DISK; \
	diskutil unmount $$DISK; \
	diskutil unmountDisk $$DISK; \
	sudo dd if=./arcadeos.iso of=$$DISK bs=1m; \
	diskutil eject $$DISK
