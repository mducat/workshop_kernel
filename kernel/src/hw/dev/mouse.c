
#include <screen.h>
#include <irq.h>

#include <sys/io.h>

uint64_t m_x = 0;
uint64_t m_y = 0;

void irq12_handler(void)
{

    out:
    end_of_interrupt(12);
}

void init_mouse()
{
    m_x = disp->screen->x_len / 2;
    m_y = disp->screen->y_len / 2;
}
