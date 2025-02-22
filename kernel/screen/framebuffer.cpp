#include <limine/limine.h>
#include <stl/types.hpp>
#include <kernel/intrinsics.hpp>
#include <kernel/screen/framebuffer.hpp>
#include <kernel/log.hpp>

static volatile limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0,
	.response = nullptr,
};

Canvas* kernel::framebuffer::get_framebuffer() {
	static Canvas instance(nullptr, 0, 0);
	return &instance;
}

void kernel::framebuffer::init() {
	if (!framebuffer_request.response || framebuffer_request.response->framebuffer_count < 1)
		panic("None or invalid response for framebuffer request");

	auto* framebuffer = framebuffer_request.response->framebuffers[0];

	// Note: we assume the framebuffer model is RGB with 32-bit pixels.
	auto* const fb_ptr = reinterpret_cast<u32*>(framebuffer->address);
	const auto stride = framebuffer->pitch / 4;
	for (usize y = 0; y < framebuffer->height; y++) {
		for (usize x = 0; x < framebuffer->width; x++) {
			u8 blue = 255 - (x * (y + 400) >> 8 & 0xFF) / 2;
			u8 red = blue / 2;
			u8 green = blue / 2;
			u32 color = (red << 16) | (green << 8) | blue;
			fb_ptr[y * stride + x] = color;
		}
	}

	*get_framebuffer() = Canvas(fb_ptr, framebuffer->width, framebuffer->height, stride);

	kdbgln("Framebuffer initialized");
}
