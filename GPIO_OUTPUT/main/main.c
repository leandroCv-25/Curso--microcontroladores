#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"

#define light 4

void app_main(void)
{

    // Configura o pino como GPIO
	esp_rom_gpio_pad_select_gpio(light);
	// Configura o GPIO como saída OUTPUT
	gpio_set_direction(light, GPIO_MODE_OUTPUT);

	while (true)
	{
		//seta como nível 1 ou HIGH a saída
		gpio_set_level(light,1);
		//delay de 2000 ms o microcontrolador fica em estado idle se não tiver outra task em andamento
		vTaskDelay(pdMS_TO_TICKS(2000));
		//seta como nível 0 ou LOW a saída
		gpio_set_level(light,0);
		//delay de 2000 ms o microcontrolador fica em estado idle se não tiver outra task em andamento
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}
