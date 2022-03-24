
#include <irq.h>

#include <sys/io.h>

#include <dev/ps2.h>
#include <dev/mouse.h>

void write_ps2(uint8_t port, uint8_t data)
{
    uint16_t tm_out = 10000;

    while ((inb(PS2_CMD) & 2) && tm_out-- != 0) {
        __asm__ __volatile__ ("nop");
    }

    outb(port, data);
}

uint8_t read_ps2(uint8_t port)
{
    uint16_t tm_out = 10000;

    while (!(inb(PS2_CMD) & 1) && tm_out-- != 0) {
        __asm__ __volatile__ ("nop");
    }

    return inb(port);
}

void write_mouse(uint8_t data)
{
    write_ps2(PS2_CMD, 0xD4);
    write_ps2(PS2_DATA, data);
}

uint8_t ps2_ack(void)
{
    return (read_ps2(PS2_DATA) != PS2_ACK);
}

void ps2_wconf(uint8_t conf)
{
    write_ps2(PS2_CMD, PS2_CWD_W_CONF);
    write_ps2(PS2_DATA, conf);
}

uint8_t ps2_rconf(void)
{
    write_ps2(PS2_CMD, PS2_CWD_R_CONF);
    return read_ps2(PS2_DATA);
}

void init_ps2()
{
    deactivate_interrupts();
    
    // configure software-side
    init_mouse();

    activate_interrupts();
}
