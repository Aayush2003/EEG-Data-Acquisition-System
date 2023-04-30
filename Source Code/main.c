/*!
 * @file main.c
 * @brief ECG2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the ECG 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and UART communication, configures INT pin as INPUT, RST pin as OUTPUT, CS pin as 
 * OUTPUT and PWM pin as OUTPUT. Initializes SPI driver, initializes ECG2 click, sends START and 
 * RDATAC opcodes.
 *
 * ## Application Task
 * Captures readings from channel and plots data to serial plotter.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ecg2.h"

static ecg2_t ecg2;
static log_t logger;
uint32_t time;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg2_cfg_t ecg2_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ecg2_cfg_setup( &ecg2_cfg );
    ECG2_MAP_MIKROBUS( ecg2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ecg2_init( &ecg2, &ecg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( ECG2_ERROR == ecg2_default_cfg ( &ecg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    ecg2_send_command ( &ecg2, ECG2_STOP_DATA_CONT_MODE);
    
    // Register Values
//     uint8_t registerValue;
//     for (uint8_t registerAddress = 0x00; registerAddress <= 0x19; registerAddress++)
//     {
//         ecg2_read_register(&ecg2, registerAddress, &registerValue);
//         log_printf( &logger, "%.8u: %.8u\r\n", registerAddress, registerValue);
//     }
    
    ecg2_send_command( &ecg2, ECG2_START_CONVERSION );
    Delay_ms( 100 );
    ecg2_send_command( &ecg2, ECG2_ENABLE_READ_DATA_CONT_MODE );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{   
    // Without daisy chaining
    uint16_t ecg_an[4];
    ecg2_read_all_channel_data( &ecg2, &ecg_an );
    log_printf( &logger, " %.6u\t%.6u\t%.6u\t%.6u\r\n", ecg_an[0], ecg_an[1], ecg_an[2], ecg_an[3]);
    
    // With daisy chaining
//     uint16_t ecg_an[8];
//     ecg2_daisy_chaining_2( &ecg2, &ecg_an);
//     log_printf( &logger, " %.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\r\n", ecg_an[0], ecg_an[1], ecg_an[2], ecg_an[3], ecg_an[4], ecg_an[5], ecg_an[6], ecg_an[7]);
    
//     uint16_t ecg_an[8];
//     ecg2_read_all_channel_data_test(&ecg2, &ecg_an);
//     log_printf( &logger, " %.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\r\n", ecg_an[0], ecg_an[1], ecg_an[2], ecg_an[3], ecg_an[4], ecg_an[5], ecg_an[6], ecg_an[7]);    
    
    // Daisy chaining test
//     uint16_t ecg_an[8];
//     ecg2_daisy_chaining_final( &ecg2, &ecg_an );
//     log_printf( &logger, " %.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\t%.6u\r\n", ecg_an[0], ecg_an[1], ecg_an[2], ecg_an[3], ecg_an[4], ecg_an[5], ecg_an[6], ecg_an[7]);
    
    // Daisy chaining debug
//     uint8_t ecg_an[23];
//     ecg2_daisy_chaining_final2( &ecg2, &ecg_an );
//     for (int i = 0; i < 23; i++)
//     {
//         log_printf( &logger, " %.6u\t", ecg_an[i]);
//     }
//     log_printf( &logger, "\r\n");
    
//     Delay_ms( 2 );   
//     Delay_410us();
//     Delay_us(200);
    Delay_410us();
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
