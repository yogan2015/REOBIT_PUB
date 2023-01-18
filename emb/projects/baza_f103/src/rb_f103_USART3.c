#include "../inc/main.h"
// USART3 с использованием DMA
// DMA1 Channel 2 - Tx
// DMA1 Channel 3 - Rx

static inline void config_USART3() 
{
    // Настройка DMA
    DMA1_Channel2->CPAR = USART3->DR;           // wut?
    DMA1_Channel2->CMAR = *tx_str;
    DMA1_Channel2->CNDTR= 6;
    DMA1_Channel2->CCR |= (                     // Конфигурация DMA1 CH2 кроме бита включения EN 
                            DMA_CCR1_TCIE   |   // Transfer complete interrupt
                        //  DMA_CCR1_HTIE   |   // Half-transfer interrupt
                        //  DMA_CCR1_TEIE   |   // Error interrupt
                            DMA_CCR1_DIR    |   // 1 - читать из памяти в периферию
                            DMA_CCR1_CIRC   |   // circular
                        //  DMA_CCR1_PINC   |   // Peripherial increment mode
                            DMA_CCR1_MINC   |   // Memory increment mode
                        //  DMA_CCR1_PSIZE  |   // 00 - halfword    01 - word   10 - dword
                        //  DMA_CCR1_MSIZE  |   // 00 - halfword    01 - word   10 - dword
                            DMA_CCR1_PL     |   // low priority
                        //  DMA_CCR1_MEM2MEM|   // memory to memory
                            0);

    //  Настройка USART3
    USART3->CR1 |= (                            // Конфигурация кроме бита включения CR1_UE
                        USART_CR1_SBK       |   // Send break
                        USART_CR1_RWU       |   // Receiver wakeup
                        USART_CR1_RE        |   // Receiver enable
                        USART_CR1_TE        |   // Transmitter enable
                        USART_CR1_IDLEIE    |   // IDLE interrupt enable
                        USART_CR1_RXNEIE    |   // ORE=1 or RXNE=1 interrupt enable (Rx not empty)
                        USART_CR1_TCIE      |   // TC=1 interrupt enable (transmission complete)
                        USART_CR1_TXEIE     |   // TXE=1 interrupt enable (Tx empty)
                        USART_CR1_PEIE      |   // PE=1 interrupt enable 
                        USART_CR1_PS        |   // Parity selection (0 - even[чёт], 1 - odd[нечёт])
                        USART_CR1_PCE       |   // Parity control enable
                        USART_CR1_WAKE      |   // Wakeup method (0 - Idle line, 1 - Address Mark)
                        USART_CR1_M         |   // Word length (0 - 8, 1 - 9)
                        0);  
    
    USART3->CR2 |= (
                        USART_CR2_ADD       |   // Node Address (0-15)
                        USART_CR2_LBDL      |   // LIN break detection length (0 - 10, 1 - 11)
                        USART_CR2_LBDIE     |   // LBD=1 interrupt enable (LIN break detection)
                        USART_CR2_LBCL      |   // Last bit clock pulse
                        USART_CR2_CPHA      |   // Clock phase
                        USART_CR2_CPOL      |   // Clock polarity
                        USART_CR2_CLKEN     |   // Clock enable
                        USART_CR2_STOP      |   // STOP bits (00 - 1, 01 - 0.5, 10 - 2, 11 - 1.5)
                        USART_CR2_LINEN     |   // LIN mode enable
                        0);

    USART3->CR |= (
                        USART_CR3_EIE       |   // FE=1 or ORE=1 or NE=1 interrupt enable
                        USART_CR3_IREN      |   // IrDA mode enable (infrared)
                        USART_CR3_IRLP      |   // IrDA low-power
                        USART_CR3_HDSEL     |   // Half-duplex selection (onewire)
                        USART_CR3_NACK      |   // Smartcard NACK enable
                        USART_CR3_SCEN      |   // Smartcard mode enable
                        USART_CR3_DMAR      |   // DMA enable receiver
                        USART_CR3_DMAT      |   // DMA enable transmitter
                        USART_CR3_RTSE      |   // RTS enable (ready to send)
                        USART_CR3_CTSE      |   // CTS enable (clear to send)
                        USART_CR3_CTSIE     |   // CTS=1 interrupt enable
                        0);
}