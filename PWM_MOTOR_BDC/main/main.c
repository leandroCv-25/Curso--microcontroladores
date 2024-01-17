#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "motor_drive.h"

static const char *TAG = "Main - PWM MOTOR BDC";

void app_main(void)
{
    static motor_control_context_t motor_ctrl_ctx = {
        .pcnt_encoder = NULL,
        .expect_speed = 50, 
        .direction = MOTOR_FORWARD};

    motor_drive_config(&motor_ctrl_ctx, 18, 19, 33, 32, 0);

    vTaskDelay(pdMS_TO_TICKS(1000));

    while (true)
    {
        
        ESP_LOGI(TAG, "Setando velocidade 50 e Sentido horario");
        set_motor_direction(&motor_ctrl_ctx, MOTOR_FORWARD);
        set_motor_speed(&motor_ctrl_ctx, 50);
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGI(TAG, "Velocidade %d",motor_ctrl_ctx.report_pulses);

        ESP_LOGI(TAG, "Setando velocidade 100 e Sentido horario");
        set_motor_speed(&motor_ctrl_ctx, 100);
        ESP_LOGI(TAG, "Velocidade %d",motor_ctrl_ctx.report_pulses);
        vTaskDelay(pdMS_TO_TICKS(10000));

        ESP_LOGI(TAG, "FREIANDO");
        motor_brake(&motor_ctrl_ctx);
        vTaskDelay(pdMS_TO_TICKS(10000));

        ESP_LOGI(TAG, "Setando velocidade 50 e Sentido anti-horario");
        set_motor_direction(&motor_ctrl_ctx, MOTOR_REVERSE);
        set_motor_speed(&motor_ctrl_ctx, 50);
        ESP_LOGI(TAG, "Velocidade %d",motor_ctrl_ctx.report_pulses);
        vTaskDelay(pdMS_TO_TICKS(10000));

        ESP_LOGI(TAG, "FREIANDO");
        motor_brake(&motor_ctrl_ctx);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}