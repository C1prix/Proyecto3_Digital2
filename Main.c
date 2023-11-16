#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
 
void InitUART0(void); // Funcion InitUART0
void InitUART1(void); // Funcion InitUART1
void InitUART5(void); // Funcion InitUART5

int main(void) {
    // Configurar el reloj del sistema a 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Inicializar UART0, UART1 y UART5 (cambiado de UART2 a UART5)
    InitUART0(); // InitUART0
    InitUART1(); // InitUART1
    InitUART5(); // InitUART5

    while (1) {
        // Enviar mensajes a través de UART0
        UARTCharPut(UART0_BASE, 'U');
        UARTCharPut(UART0_BASE, 'A');
        UARTCharPut(UART0_BASE, 'R');
        UARTCharPut(UART0_BASE, 'T');
        UARTCharPut(UART0_BASE, '0');
        UARTCharPut(UART0_BASE, '\n');

        // Enviar mensajes a través de UART1
        UARTCharPut(UART1_BASE, 'U');
        UARTCharPut(UART1_BASE, 'A');
        UARTCharPut(UART1_BASE, 'R');
        UARTCharPut(UART1_BASE, 'T');
        UARTCharPut(UART1_BASE, '1');
        UARTCharPut(UART1_BASE, '\n');

        // Enviar mensajes a través de UART2
        UARTCharPut(UART5_BASE, 'U');
        UARTCharPut(UART5_BASE, 'A');
        UARTCharPut(UART5_BASE, 'R');
        UARTCharPut(UART5_BASE, 'T');
        UARTCharPut(UART5_BASE, '2');
        UARTCharPut(UART5_BASE, '\n');
    }
}

void InitUART0(void) {
    // Habilitar el puerto A y UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configurar pines PA0 y PA1 como UART
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configurar la UART0
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void InitUART1(void) {
    // Habilitar el puerto B y UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    // Configurar pines PB0 y PB1 como UART
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configurar la UART1
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void InitUART5(void) {
    // Habilitar el puerto E y UART5 (cambiado de D a E)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5); // Cambiado de U2 a U5

    // Configurar pines PE4 y PE5 como UART (cambiado de PD6 y PD7 a PE4 y PE5)
    GPIOPinConfigure(GPIO_PE4_U5RX); // Cambiado de GPIO_PD6_U2RX a GPIO_PE4_U5RX
    GPIOPinConfigure(GPIO_PE5_U5TX); // Cambiado de GPIO_PD7_U2TX a GPIO_PE5_U5TX
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5); // Cambiado de GPIO_PORTD_BASE a GPIO_PORTE_BASE

    // Configurar la UART5 (cambiado de U2 a U5)
    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
