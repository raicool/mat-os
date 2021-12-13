#include "kernel.hpp"
#include "terminal.hpp"
#include "stdio.hpp"
#include "serial.hpp"
#include "idt.hpp"
#include "pic.hpp"
#include "gdt.hpp"
#include "keyboard.hpp"
#include "string.hpp"
#include "array.hpp"
#include "vector.hpp"

#if defined(__linux__) || !defined(__i386__)
	#error "Compilation options are incorrect"
#endif


extern "C" void kernel_main() {
	terminal_init();

	serial_init();

	gdt_init();

	pic_init();

	keyboard_init();

	idt_init();

	serial_put_string("hello\n");

	printf("Hello, kernel World!\n");
	printf("I am mat\n");
	printf("I am mat 2");
	printf("its me mat once again\n");


	asm volatile("int3" :);
	serial_put_string("after int 3\n");

	asm volatile("int3" :);
	serial_put_string("another int 3\n");

	serial("Going to allocate 8 bytes\n"_sv);
	char* data = (char*)malloc(8);
	if (data != nullptr) {
		data[0] = 'H';
		data[1] = 'e';
		data[2] = 'l';
		data[3] = 'l';
		data[4] = 'o';
		data[5] = '\n';
		data[6] = 0;

		terminal_write_string(data);

		free(data);
	} else {
		serial_put_string("malloc failed\n");
	}

	terminal("hello {} there! {} + {} = {}\n"_sv, 23, 1, 2, 3);
	terminal("this shouldnt get formatted {{}} {{hello}} {{ world {} }}, but this should {}\n"_sv, 31, 42);

	serial("-- begin vector test --\n"_sv);
	Vector<int> test;
	for (const auto i : test) { terminal("vec: {}\n", i); }
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	for (int& i : test) { terminal("vec: {}\n", i++); }
	for (int i = 0; i < 5; ++i) {
		terminal("adding {}\n", i * 13);
		test.push_back(i * 13);
	}
	for (const auto i : test) { terminal("vec: {}\n", i); }
	serial("-- end vector test --\n"_sv);

	terminal("Check out this hex number {x}, pretty cool right {} {x}\n"_sv, 1337, i8(-127), i8(-127));
	terminal("Hello {}!\n"_sv, "world");

	String str = "hi";
	terminal("{} there\n", str);
}
