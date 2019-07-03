#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int avaliable_ports[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
int script_file;
char aux[100];

void process_uart_port(int port);
void process_gpio_port(int port, int gpio);
void process_pwm_port(int port);
void process_spi_port(int port);
void process_adc_port(int port);
void process_i2c_port(int port);
int contains(int *list, int port, int size);
void update_list(int port);
void replace_X(char* string, char n1, char n2);

int main(int argc, char** argv)
{
    int one_more_port = 1;
    int spi_mosi = 11;
    int spi_miso = 12;
    int spi_sck = 13;
    int i2c_sda = 18;
    int i2c_scl = 19;
    int uart0_tx = 1;
    int uart0_rx = 0;
    int uart1_tx = 3;
    int uart1_rx = 2;
    int current_port;
    int port_mode;
    char string[] = "#! /bin/sh\ncase \"$1\" in\n    start|restart|force-reload)\n";
    
    script_file = open("init_script", O_WRONLY);
    
    write(script_file, string, sizeof(string));
    
    while (one_more_port)
    {
        printf("Which port do you want to add to the script?\n");
        scanf("%d", &current_port);
        if(current_port < 0 || current_port > 19)
            printf("Port number must be between 0 and 19\n");
        else
        {
            switch(current_port)
            {
                case 0:
                case 1: printf("Which mode do you want this port on?\n0 - GPIO\n1 - UART\n");
                        scanf("%d", &port_mode);
                        if(port_mode)
                            process_uart_port(current_port);
                        else
                            process_gpio_port(current_port, -1);
                        break;
                case 2: printf("Which mode do you want this port on?\n0 - GPIO13\n1 - UART\n2 - GPIO61\n");
                        scanf("%d", &port_mode);
                        if(port_mode == 1)
                            process_uart_port(current_port);
                        else if(port_mode == 0)
                            process_gpio_port(current_port, 13);
                        else
                            process_gpio_port(current_port, 61);
                        break;
                case 3: printf("Which mode do you want this port on?\n0 - GPIO14\n1 - UART\n2 - PWM\n3 - GPIO62\n");
                        scanf("%d", &port_mode);
                        if(port_mode == 1)
                            process_uart_port(current_port);
                        else if(port_mode == 0)
                            process_gpio_port(current_port, 14);
                        else if(port_mode == 2)
                            process_pwm_port(current_port);
                        else
                            process_gpio_port(current_port, 62);
                        break;
                case 4: process_gpio_port(current_port, -1);
                        break;
                case 5:
                case 6: printf("Which mode do you want this port on?\n0 - GPIO\n1 - PWM\n");
                        scanf("%d", &port_mode);
                        if(!port_mode)
                            process_gpio_port(current_port, -1);
                        else
                            process_pwm_port(current_port);
                        break;
                case 7:
                case 8: process_gpio_port(current_port, -1);
                        break;
                case 9: 
                case 10: printf("Which mode do you want this port on?\n0 - GPIO\n1 - PWM\n");
                         scanf("%d", &port_mode);
                         if(!port_mode)
                            process_gpio_port(current_port, -1);
                         else
                            process_pwm_port(current_port);
                         break;
                case 11: printf("Which mode do you want this port on?\n0 - GPIO\n1 - PWM\n2 - SPI\n");
                         scanf("%d", &port_mode);
                         if(!port_mode)
                            process_gpio_port(current_port, -1);
                         else if(port_mode == 1)
                            process_pwm_port(current_port);
                         else
                            process_spi_port(current_port);
                         break;
                case 12:
                case 13: printf("Which mode do you want this port on?\n0 - GPIO14\n1 - SPI\n");
                         scanf("%d", &port_mode);
                         if(!port_mode)
                            process_gpio_port(current_port, -1);
                         else
                            process_spi_port(current_port);
                         break;
                case 14:
                case 15:
                case 16:
                case 17: printf("Which mode do you want this port on?\n0 - GPIO\n1 - ADC\n");
                         scanf("%d", &port_mode);
                         if(!port_mode)
                            process_gpio_port(current_port, -1);
                         else
                            process_adc_port(current_port);
                         break;
                case 18:
                case 19: printf("Which mode do you want this port on?\n0 - GPIO\n1 - ADC\n2 - I2C\n");
                         scanf("%d", &port_mode);
                         if(!port_mode)
                            process_gpio_port(current_port, -1);
                         else if(port_mode == 1)
                            process_adc_port(current_port);
                         else
                            process_i2c_port(current_port);
                         break;
            }
            printf("Would you like to add one more port to the script?\n0 - No\n1 - Yes\n");
            scanf("%d", &one_more_port);
        }
    }
    close(script_file);
}

void process_uart_port(int port)
{
    char string[] = "if [ ! -d /sys/class/gpio/gpioXX ]\n";
    if(!contains(avaliable_ports, port, 20))
    {
        printf("Port was already added to the script. Choose another.");
        return;
    }
    
    switch(port)
    {
        case 0: //string[30] = '';
                //string[31] = '';
                //printf("%s", string);
                break;
    }
    
    update_list(port);
}

void process_gpio_port(int port, int gpio)
{
    int direction = 0;
    int resistor = 0;
    char if_string[] = "    if [ ! -d /sys/class/gpio/gpioXX ] ; then\n";
    char export_string[] = "        echo -n \"XX\" > /sys/class/gpio/export\n";
    char end_if[] = "    fi\n";
    char echo_direction_out[] = "    echo -n \"out\" > /sys/class/gpio/gpioXX/direction\n";
    char echo_direction_in[] = "    echo -n \"in\" > /sys/class/gpio/gpioXX/direction\n";
    char echo_value[] = "    echo -n \"X\" > /sys/class/gpio/gpioXX/value\n";
    char chg_group[] = "    chgrp gpio /sys/class/gpio/gpioXX/value\n";
    char chmod_write[] = "    chmod g+rw /sys/class/gpio/gpioXX/value\n";
    char chmod_read[] = "    chmod g+r /sys/class/gpio/gpioXX/value\n";
    if(!contains(avaliable_ports, port, 20))
    {
        printf("Port was already added to the script. Choose another.");
        return;
    }
    
    printf("Which direction should the port be?\n0 - in\n1 - out\n");
    scanf("%d", &direction);
    
    switch(port)
    {
        case 0: if(!direction)
                {
                    replace_X(if_string, '1', '1');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '1', '1');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, sizeof(end_if));
                    replace_X(chg_group, '1', '1');
                    write(script_file, aux, strlen(aux));
                    replace_X(chmod_read, '1', '1');
                    write(script_file, aux, strlen(aux));
                    
                    replace_X(if_string, '3', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '3', '2');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, sizeof(end_if));
                    replace_X(echo_direction_out, '3', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(echo_value, '1', NULL);
                    replace_X(aux, '3', '2');
                    write(script_file, aux, strlen(aux));
		    
		    printf("Do you need a pull up or pull down resistor?\n0 - No\n1 - Pull Up\n2 - Pull Down\n");
		    scanf("%d", &resistor);
		    if(!resistor)
		    {
			replace_X(if_string,'3','3');
			write(script_file, aux, strlen(aux));
			replace_X(export_string,'3','3');
			write(script_file,aux,strlen(aux));
			write(script_file,end_if,strlen(end_if));
			replace_X(echo_direction_in,'3','3');
			write(script_file,aux,strlen(aux));
		    }
		    else if(resistor == 1)
		    {
			replace_X(if_string, '3', '3');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '3');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '3');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '1', NULL);
			replace_X(aux, '3', '3');
			write(script_file, aux, strlen(aux));
		    }
		    else
		    {
			replace_X(if_string, '3', '3');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '3');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '3');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '0', NULL);
			replace_X(aux, '3', '3');
			write(script_file, aux, strlen(aux));
		    }
		    break;
                }
                else
		{
		    replace_X(if_string, '1', '1');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '1', '1');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(chg_group, '1', '1');
                    write(script_file, aux, strlen(aux));
                    replace_X(chmod_write, '1', '1');
                    write(script_file, aux, strlen(aux));
                    
                    replace_X(if_string, '3', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '3', '2');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(echo_direction_out, '3', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(echo_value, '0', NULL);
                    replace_X(aux, '3', '2');
                    write(script_file, aux, strlen(aux));
		}
        case 1: if(!direction)
		{
		    replace_X(if_string, '1', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '1', '2');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(chg_group, '1', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(chmod_read, '1', '2');
                    write(script_file, aux, strlen(aux));
                    
                    replace_X(if_string, '2', '8');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '2', '8');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(echo_direction_out, '2', '8');
                    write(script_file, aux, strlen(aux));
                    replace_X(echo_value, '1', NULL);
                    replace_X(aux, '2', '8');
                    write(script_file, aux, strlen(aux));
		    
		    if(!resistor)
		    {
			replace_X(if_string,'2','9');
			write(script_file, aux, strlen(aux));
			replace_X(export_string,'2','9');
			write(script_file,aux,strlen(aux));
			write(script_file,end_if,strlen(end_if));
			replace_X(echo_direction_in,'2','9');
			write(script_file,aux,strlen(aux));
		    }
		    else if(resistor == 1)
		    {
			replace_X(if_string, '2', '9');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '2', '9');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '2', '9');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '1', NULL);
			replace_X(aux, '2', '9');
			write(script_file, aux, strlen(aux));
		    }
		    else
		    {
			replace_X(if_string, '2', '9');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '2', '9');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '2', '9');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '0', NULL);
			replace_X(aux, '2', '9');
			write(script_file, aux, strlen(aux));
		    }
		    replace_X(if_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    replace_X(export_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    write(script_file, end_if, strlen(end_if));
		    replace_X(echo_direction_out, '4', '5');
		    write(script_file,aux,strlen(aux));
		    replace_X(echo_value, '0', NULL);
		    replace_X(aux, '4', '5');
		    write(script_file, aux, strlen(aux));
		    break;
		}
		else
		{
		    replace_X(if_string, '1', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '1', '2');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(chg_group, '1', '2');
                    write(script_file, aux, strlen(aux));
                    replace_X(chmod_write, '1', '2');
                    write(script_file, aux, strlen(aux));
                    
                    replace_X(if_string, '2', '8');
                    write(script_file, aux, strlen(aux));
                    replace_X(export_string, '2', '8');
                    write(script_file, aux, strlen(aux));
                    write(script_file, end_if, strlen(end_if));
                    replace_X(echo_direction_out, '2', '8');
                    write(script_file, aux, strlen(aux));
                    replace_X(echo_value, '0', NULL);
                    replace_X(aux, '2', '8');
                    write(script_file, aux, strlen(aux));
		    
		    replace_X(if_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    replace_X(export_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    write(script_file, end_if, strlen(end_if));
		    replace_X(echo_direction_out, '4', '5');
		    write(script_file,aux,strlen(aux));
		    replace_X(echo_value, '0', NULL);
		    replace_X(aux, '4', '5');
		    write(script_file, aux, strlen(aux));
		    break;
		}
	case 2: if(!direction)
		{
		    if(gpio == 13)
		    {
			replace_X(if_string, '1', '3');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '1', '3');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(chg_group, '1', '3');
			write(script_file, aux, strlen(aux));
			replace_X(chmod_read, '1', '3');
			write(script_file, aux, strlen(aux));
			
			replace_X(if_string, '3', '4');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '4');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '4');
			write(script_file, aux, strlen(aux));
			replace_X(echo_value, '1', NULL);
			replace_X(aux, '3', '4');
			write(script_file, aux, strlen(aux));
		    }
		    else
		    {
			replace_X(if_string, '6', '1');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '6', '1');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(chg_group, '6', '1');
			write(script_file, aux, strlen(aux));
			replace_X(chmod_read, '6', '1');
			write(script_file, aux, strlen(aux));
		    }
			
		    if(!resistor)
		    {
			replace_X(if_string,'3','5');
			write(script_file, aux, strlen(aux));
			replace_X(export_string,'3','5');
			write(script_file,aux,strlen(aux));
			write(script_file,end_if,strlen(end_if));
			replace_X(echo_direction_in,'3','5');
			write(script_file,aux,strlen(aux));
		    }
		    else if(resistor == 1)
		    {
			replace_X(if_string, '3', '5');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '5');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '5');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '1', NULL);
			replace_X(aux, '3', '5');
			write(script_file, aux, strlen(aux));
		    }
		    else
		    {
			replace_X(if_string, '3', '5');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '5');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '5');
			write(script_file,aux,strlen(aux));
			replace_X(echo_value, '0', NULL);
			replace_X(aux, '3', '5');
			write(script_file, aux, strlen(aux));
		    }
		    replace_X(if_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    replace_X(export_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    write(script_file, end_if, strlen(end_if));
		    replace_X(echo_direction_out, '4', '5');
		    write(script_file,aux,strlen(aux));
		    replace_X(echo_value, '0', NULL);
		    replace_X(aux, '4', '5');
		    write(script_file, aux, strlen(aux)); 
		}
		else
		{
		    if(gpio == 13)
		    {
			replace_X(if_string, '1', '3');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '1', '3');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(chg_group, '1', '3');
			write(script_file, aux, strlen(aux));
			replace_X(chmod_write, '1', '3');
			write(script_file, aux, strlen(aux));
			
			replace_X(if_string, '3', '4');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '3', '4');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(echo_direction_out, '3', '4');
			write(script_file, aux, strlen(aux));
			replace_X(echo_value, '0', NULL);
			replace_X(aux, '3', '4');
			write(script_file, aux, strlen(aux));
		    }
		    else
		    {
			replace_X(if_string, '6', '1');
			write(script_file, aux, strlen(aux));
			replace_X(export_string, '6', '1');
			write(script_file, aux, strlen(aux));
			write(script_file, end_if, strlen(end_if));
			replace_X(chg_group, '6', '1');
			write(script_file, aux, strlen(aux));
			replace_X(chmod_write, '6', '1');
			write(script_file, aux, strlen(aux));
		    }
		    replace_X(if_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    replace_X(export_string, '4', '5');
		    write(script_file, aux, strlen(aux));
		    write(script_file, end_if, strlen(end_if));
		    replace_X(echo_direction_out, '4', '5');
		    write(script_file,aux,strlen(aux));
		    replace_X(echo_value, '0', NULL);
		    replace_X(aux, '4', '5');
		    write(script_file, aux, strlen(aux));
		}
		break;
	case 3: if(!direction)
		{
		    if(gpio == 14)
		    {
			
		    }
		}
    }
    
    update_list(port);
    
}

void process_pwm_port(int port)
{
    char if_string[] = "	if [ ! -d /sys/class/pwm/pwmchip0/pwmX ] ; then\n";
    char if_gpio[] = "	if [ ! -d /sys/class/gpio/gpioXX ] ; then";
    char export_string[] = "	    echo -n \"X\" > /sys/class/pwm/pwmchip0/export\n";
    char export_gpio[] = "	    echo -n \"XX\" > /sys/class/gpio/export";
    char end_if[] = "	fi\n";
    char group_period[] = "	chgrp gpio /sys/class/pwm/pwmchip0/device/pwm_period\n";
    char chmod_period[] = "	chmod g+w /sys/class/pwm/pwmchip0/device/pwm_period\n";
    char group_cycle[] = "	chgrp gpio /sys/class/pwm/pwmchip0/pwmX/duty_cycle\n";
    char chmod_cycle[] = "	chmod g+w /sys/class/pwm/pwmchip0/pwmX/duty_cycle\n";
    char group_enable[] = "	chgrp gpio /sys/class/pwm/pwmchip0/pwmX/enable\n";
    char chmod_enable[] = "	chmod g+w /sys/class/pwm/pwmchip0/pwmX/enable\n";
    char echo_direction_out[] = "	echo -n \"out\" > /sys/class/gpio/gpioXX/direction";
    char echo_direction_in[] = "	echo -n \"in\" > /sys/class/gpio/gpioXX/direction";
    char echo_value[] = "	echo -n \"X\" > /sys/class/gpio/gpioXX/value\n";
    
    if(!contains(avaliable_ports, port, 20))
    {
        printf("Port was already added to the script. Choose another.");
        return;
    }
    switch(port)
    {
        case 3: replace_X(if_string, '1', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(export_string, '1', NULL);
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                write(script_file, group_period, strlen(group_period));
                write(script_file, chmod_period, strlen(chmod_period));
                replace_X(group_cycle, '1', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(chmod_cycle, '1', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(group_enable, '1', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(chmod_enable, '1', NULL);
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '1', '6');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '1', '6');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_direction_out, '1', '6');
                write(script_file, aux, strlen(aux));
                replace_X(echo_value, '0', NULL);
                replace_X(aux, '1', '6');
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '1', '7');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '1', '7');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_direction_in, '1', '7');
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '7', '6');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '7', '6');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_value, '0', NULL);
                replace_X(aux, '7', '6');
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '6', '4');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '6', '4');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_value, '1', NULL);
                replace_X(aux, '6', '4');
                write(script_file, aux, strlen(aux));
                break;
        case 5: replace_X(if_string, '3', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(export_string, '3', NULL);
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                write(script_file, group_period, strlen(group_period));
                write(script_file, chmod_period, strlen(chmod_period));
                replace_X(group_cycle, '3', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(chmod_cycle, '3', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(group_enable, '3', NULL);
                write(script_file, aux, strlen(aux));
                replace_X(chmod_enable, '3', NULL);
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '1', '8');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '1', '8');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_direction_out, '1', '8');
                write(script_file, aux, strlen(aux));
                replace_X(echo_value, '0', NULL);
                replace_X(aux, '1', '8');
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '1', '9');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '1', '9');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_direction_in, '1', '9');
                write(script_file, aux, strlen(aux));
                
                replace_X(if_gpio, '6', '6');
                write(script_file, aux, strlen(aux));
                replace_X(export_gpio, '6', '6');
                write(script_file, aux, strlen(aux));
                write(script_file, end_if, strlen(end_if));
                replace_X(echo_value, '0', NULL);
                replace_X(aux, '6', '6');
                write(script_file, aux, strlen(aux));
                break;
                
        case 6:
        case 9:
        case 10:
        case 11: break;
    }
    update_list(port);
}

void process_spi_port(int port)
{
}

void process_adc_port(int port)
{
    char if_gpio[] = "    if [ ! -d /sys/class/gpio/gpioXX ] ; then\n";
    char export[] = "        echo -n \"XX\" > /sys/class/gpio/export\n";
    char end_if[] = "    fi\n";
    char echo_in[] = "    echo -n \"in\" > /sys/class/gpio/gpioXX/direction\n";
    char group_scale[] = "    chgrp gpio /sys/bus/iio/devices/iio:device0/in_voltage\"X\"_scale\n";
    char chmod_scale[] = "    chmod g+r /sys/bus/iio/devices/iio:device0/in_voltage\"X\"_scale\n";
    char group_en[] = "    chgrp gpio /sys/bus/iio/devices/iio:device0/scan_elements/in_voltage\"X\"_en\n";
    char chmod_en[] = "    chmod g+rw /sys/bus/iio/devices/iio:device0/scan_elements/in_voltage\"X\"_en\n";
    char grp_times[] = "    chgrp gpio /sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en\n";
    char chmod_times[] = "    chmod g+rw /sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en\n";
    char grp_enable[] = "    chgrp gpio /sys/bus/iio/devices/iio:device0/buffer/enable\n";
    char chmod_enable[] = "    chmod g+rw /sys/bus/iio/devices/iio:device0/buffer/enable\n";
    char grp_length[] = "    chgrp gpio /sys/bus/iio/devices/iio:device0/buffer/length\n";
    char chmod_length[] = "	chmod g+rw /sys/bus/iio/devices/iio:device0/buffer/length\n";
    char modprobe_t[] = "    modprobe iio-trig-sysfs\n";
    char add_trigger_t[] = "    echo -n \"0\" > /sys/bus/iio/devices/iio_sysfs_trigger/add_trigger\n";
    char grp_trg_now_t[] = "    chgrp gpio /sys/bus/iio/devices/trigger0/trigger_now\n";
    char chmod_trg_now_t[] = "	chmod g+w /sys/bus/iio/devices/trigger0/trigger_now\n";
    char modprobe_h[] = "	modprobe iio-trig-hrtimer\n";
    char add_trigger_h[] = "    echo -n \"1\" > /sys/bus/iio/devices/iio_hrtimer_trigger/add_trigger\n";
    char grp_freq[] = "    chgrp adc /sys/bus/iio/devices/trigger1/frequency\n";
    char chmod_freq[] = "    chmod g+rw /sys/bus/iio/devices/trigger1/frequency\n";
    char grp_ct[] = "    chgrp adc /sys/bus/iio/devices/iio:device0/trigger/current_trigger\n"; 
    char chmod_ct[] = "	chmod g+rw /sys/bus/iio/devices/iio:device0/trigger/current_trigger\n";
    char grp_d0[] = "	chgrp adc /dev/iio:device0\n";
    char chmodd0[] = "	chmod g+r /dev/iio:device0\n";
    
    
}

void process_i2c_port(int port)
{
    char if_string[] = "	if [ ! -d /sys/class/gpio/gpioXX ] ; then\n";
    char export_string[] = "    		echo -n \"XX\" > /sys/class/gpio/export\n";
    char end_if[] = "	fi\n";
    char echo_direction_out[] = "	echo \"out\" > /sys/class/gpio/gpioXX/direction\n";
    char echo_value[] = "	echo \"X\" > /sys/class/gpio/gpioXX/value\n";
    char group[] = "	chgrp gpio /dev/i2c-0\n";
    char chmod[] = "	chmod g+rw /dev/i2c-0\n";
    
    if(!contains(avaliable_ports, port, 20))
    {
        printf("Port was already added to the script. Choose another.");
        return;
    }
    
    switch(port)
    {
        case 18: replace_X(if_string, '5', '7');
                 write(script_file, aux, strlen(aux));
                 replace_X(export_string, '5', '7');
                 write(script_file, aux, strlen(aux));
                 write(script_file, end_if, strlen(end_if));
                 replace_X(echo_direction_out, '5', '7');
                 write(script_file, aux, strlen(aux));
                 replace_X(echo_value, '1', NULL);
                 replace_X(aux, '5', '7');
                 write(script_file, aux, strlen(aux));
                 
                 replace_X(if_string, '6', '0');
                 write(script_file, aux, strlen(aux));
                 replace_X(export_string, '6', '0');
                 write(script_file, aux, strlen(aux));
                 write(script_file, end_if, strlen(end_if));
                 replace_X(echo_direction_out, '6', '0');
                 write(script_file, aux, strlen(aux));
                 replace_X(echo_value, '0', NULL);
                 replace_X(aux, '6', '0');
                 write(script_file, aux, strlen(aux));
                 
                 write(script_file, group, strlen(group));
                 write(script_file, chmod, strlen(chmod));
                 break;
        case 19: replace_X(if_string, '5', '9');
                 write(script_file, aux, strlen(aux));
                 replace_X(export_string, '5', '9');
                 write(script_file, aux, strlen(aux));
                 write(script_file, end_if, strlen(end_if));
                 replace_X(echo_direction_out, '5', '9');
                 write(script_file, aux, strlen(aux));
                 replace_X(echo_value, '1', NULL);
                 replace_X(aux, '5', '9');
                 write(script_file, aux, strlen(aux));
                 
                 replace_X(if_string, '6', '0');
                 write(script_file, aux, strlen(aux));
                 replace_X(export_string, '6', '0');
                 write(script_file, aux, strlen(aux));
                 write(script_file, end_if, strlen(end_if));
                 replace_X(echo_direction_out, '6', '0');
                 write(script_file, aux, strlen(aux));
                 replace_X(echo_value, '0', NULL);
                 replace_X(aux, '6', '0');
                 write(script_file, aux, strlen(aux));
                 
                 write(script_file, group, strlen(group));
                 write(script_file, chmod, strlen(chmod));
                 break;
    }
    update_list(port);
}

int contains(int *list, int port, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if(list[i] == port)
            return 1;
    }
    return 0;
}

void update_list(int port)
{
    int i = 0;
    for(i; i < 20; i++)
    {
        if(avaliable_ports[i] == port)
            avaliable_ports[i] = -1;
    }
}

void replace_X(char* string, char n1, char n2)
{
    int i = 0;
    int n1_found = 0;
    
    strcpy(aux, string);
    while(string[i] != '\n')
    {
        if(!n1_found && string[i] == 'X')
        {
            aux[i] = n1;
            n1_found = 1;
        }
        else if(n1_found && n2 != NULL && string[i] == 'X')
        {
            aux[i] = n2;
            break;
        }
        i++;
    }
    printf("%s", aux);
}



