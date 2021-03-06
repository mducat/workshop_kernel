
#include <gdt.h>
#include <irq.h>
#include <malloc.h>
#include <string.h>

#include <screen.h>
#include <kboot.h>

void freeze(void)
{
    __asm__ __volatile__ ("cli\n\r"
                          "hlt");
}

void k_start(boot_t *data)
{
    if (data->sig != 0x42)
        freeze(); 

    init_malloc(MEM_START, MEM_END);

    disp = malloc(sizeof(disp_t));
    disp->screen = data->screen;
    disp->back = malloc(data->screen->buf_size + 256);
    clear();

    init_interrupts();

    asm volatile("hlt");
    // prevent $pc from exiting kernel
}
