#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "U4C6O12T_Comunicacao_Serial.pio.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include <ctype.h>

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define IS_RGBW false
#define NUM_PIXELS 25
#define U4C6O12T_Comunicacao_Serial_PIN 7
#define TEMPO 400

void uart_rx_callback();

uint8_t led_r = 0;
uint8_t led_g = 0;
uint8_t led_b = 200;

const bool number_patterns[10][NUM_PIXELS] = {
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1}, // 0
    {0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 1, 1, 0, 0,
     0, 0, 1, 0, 0}, // 1
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1}, // 2
    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     0, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1}, // 3
    {0, 1, 0, 0, 0,
     0, 0, 0, 1, 0,
     1, 1, 1, 1, 1,
     1, 0, 0, 1, 0,
     0, 1, 0, 0, 1}, // 4
    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1}, // 5
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1}, // 6
     {0, 0, 0, 0, 1,
      0, 1, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 1, 0,
      1, 1, 1, 1, 1}, ///////////////7
     {1, 1, 1, 1, 1,
      1, 0, 0, 0, 1,
      1, 1, 1, 1, 1,
      1, 0, 0, 0, 1,
      1, 1, 1, 1, 1}, // 8
     {1, 1, 1, 1, 1,
      0, 0, 0, 0, 1,
      1, 1, 1, 1, 1,
      1, 0, 0, 0, 1,
      1, 1, 1, 1, 1} // 9

};

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

void display_number(uint8_t num)
{
    if (num > 9)
        return;
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (number_patterns[num][i])
        {
            put_pixel(urgb_u32(led_r, led_g, led_b));
        }
        else
        {
            put_pixel(0);
        }
    }
}

int main()
{
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &U4C6O12T_Comunicacao_Serial_program);

    U4C6O12T_Comunicacao_Serial_program_init(pio, sm, offset, U4C6O12T_Comunicacao_Serial_PIN, 800000, IS_RGBW);


    char input;
    while (1)
    {
        printf("Digite um número (0-9): ");
        input = getchar();
        if (input >= '0' && input <= '9')
        {
            display_number(input - '0');
        }
        sleep_ms(TEMPO);
    }
    return 0;
}
