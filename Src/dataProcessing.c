#include "dataProcessing.h"
#include "usart.h"


static void arrayLeftOneByte(uint8_t *arr,uint8_t length) {
	for (uint8_t i = 0; i < usart2_tx_len - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
}


static void arrayRightOneByte(uint8_t *arr, uint8_t length) {

	if (length > 127) return;
	for (uint8_t i = length; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}

void dataProcessing() {


	if (usart2_rx_flag == 1)
	{
		switch (usart2_tx_buffer[0])
		{
		case 1:
			arrayLeftOneByte(usart2_tx_buffer, usart2_tx_len);
			dma_send(&huart1, &hdma_usart1_tx, usart2_tx_buffer, usart2_tx_len - 1);
			break;
		case 3:
			arrayLeftOneByte(usart2_tx_buffer, usart2_tx_len);
			dma_send(&huart3, &hdma_usart3_tx, usart2_tx_buffer, usart2_tx_len - 1);
			break;
		case 4:
			arrayLeftOneByte(usart2_tx_buffer, usart2_tx_len);
			dma_send(&huart4, &hdma_uart4_tx, usart2_tx_buffer, usart2_tx_len - 1);
			break;
		case 5:
			arrayLeftOneByte(usart2_tx_buffer, usart2_tx_len);
			dma_send(&huart1, &hdma_uart5_tx, usart2_tx_buffer, usart2_tx_len - 1);
			break;
		default:
			break;
		}
	}

	if (usart1_rx_flag == 1)
	{
		arrayRightOneByte(usart1_tx_buffer, usart1_tx_len);
		usart1_tx_buffer[0] = 1;
		usart1_tx_len++;
		dma_send(&huart2, &hdma_usart2_tx, usart1_tx_buffer, usart1_tx_len);
	}

	if (usart3_rx_flag == 1)
	{
		arrayRightOneByte(usart3_tx_buffer, usart3_tx_len);
		usart3_tx_buffer[0] = 1;
		usart3_tx_len++;
		dma_send(&huart2, &hdma_usart2_tx, usart3_tx_buffer, usart3_tx_len);
	}

	if (uart4_rx_flag == 1)
	{
		arrayRightOneByte(uart4_tx_buffer, uart4_tx_len);
		uart4_tx_buffer[0] = 1;
		uart4_tx_len++;
		dma_send(&huart2, &hdma_usart2_tx, uart4_tx_buffer, uart4_tx_len);
	}

	if (uart4_rx_flag == 1)
	{
		arrayRightOneByte(uart5_tx_buffer, uart5_tx_len);
		uart5_tx_buffer[0] = 1;
		uart5_tx_len++;
		dma_send(&huart2, &hdma_usart2_tx, uart5_tx_buffer, uart5_tx_len);
	}
}