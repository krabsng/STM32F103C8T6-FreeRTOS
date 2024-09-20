#include "stm32f10x.h"                  // Device header
#include "freertos.h"
#include "task.h"


void led_task(void *pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(500);
	}
}

int main(void)
{
	// 开启PC13外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	// 设置PC13为推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// 配置为低电平电量PC13的小灯亮起
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	xTaskCreate(led_task, "led_task", 128, NULL, 1, NULL);
	// 开启任务调度器
	vTaskStartScheduler();
	while(1)
	{
		
	}
}


