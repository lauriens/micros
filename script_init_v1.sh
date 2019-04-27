#! /bin/sh
### BEGIN INIT INFO
# Provides:          script_init_v1
# Required-Start:
# Should-Start:
# Required-Stop:
# Default-Start:     S
# Default-Stop:
# Short-Description: Configures gpios and pwm for use with libv1.
# Description:       Configures gpios and pwm for use with libv1.
### END INIT INFO

case "$1" in
    start|restart|force-reload)
        #IO0 - Decoder, bit 0/8
        if [ ! -d /sys/class/gpio/gpio11 ] ; then
    echo -n "11" > /sys/class/gpio/export
        fi
        echo -n "in" > /sys/class/gpio/gpio11/direction
        chgrp gpio /sys/class/gpio/gpio11/value
        chmod g+rw /sys/class/gpio/gpio11/value

        if [ ! -d /sys/class/gpio/gpio32 ] ; then
            echo -n "32" > /sys/class/gpio/export
        fi
    echo -n "in" > /sys/class/gpio/gpio32/direction
    echo -n "1" > /sys/class/gpio/gpio32/value

    #IO1 - Decoder, bit 1/9
    if [ ! -d /sys/class/gpio/gpio12 ] ; then
        echo -n "12" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio12/direction
    chgrp gpio /sys/class/gpio/gpio12/value
    chmod g+rw /sys/class/gpio/gpio12/value

    if [ ! -d /sys/class/gpio/gpio28 ] ; then
        echo -n "28" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio28/direction
    echo -n "1" > /sys/class/gpio/gpio28/value

    if [ ! -d /sys/class/gpio/gpio45 ] ; then
        echo -n "45" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio45/value

    #IO2 - Decoder, bit 2/10
    if [ ! -d /sys/class/gpio/gpio13 ] ; then
        echo -n "13" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio13/direction
    chgrp gpio /sys/class/gpio/gpio13/value
    chmod g+rw /sys/class/gpio/gpio13/value

    if [ ! -d /sys/class/gpio/gpio34 ] ; then
        echo -n "34" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio34/direction
    echo -n "1" > /sys/class/gpio/gpio34/value

    if [ ! -d /sys/class/gpio/gpio77 ] ; then
        echo -n "77" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio77/value

    #IO3 - Decoder, bit 3/11
    if [ ! -d /sys/class/gpio/gpio14 ] ; then
        echo -n "14" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio14/direction
    chgrp gpio /sys/class/gpio/gpio14/value
    chmod g+rw /sys/class/gpio/gpio14/value

    if [ ! -d /sys/class/gpio/gpio16 ] ; then
        echo -n "16" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio16/direction
    echo -n "1" > /sys/class/gpio/gpio16/value

    if [ ! -d /sys/class/gpio/gpio76 ] ; then
        echo -n "76" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio76/value

    if [ ! -d /sys/class/gpio/gpio64 ] ; then
        echo -n "64" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio64/value

    #IO4 - Decoder, bit 4/12
    if [ ! -d /sys/class/gpio/gpio6 ] ; then
        echo -n "6" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio6/direction
    chgrp gpio /sys/class/gpio/gpio6/value
    chmod g+rw /sys/class/gpio/gpio6/value

    if [ ! -d /sys/class/gpio/gpio36 ] ; then
        echo -n "36" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio36/direction
    echo -n "1" > /sys/class/gpio/gpio36/value

    #IO5 - Decoder, bit 5/13
    if [ ! -d /sys/class/gpio/gpio0 ] ; then
        echo -n "0" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio0/direction
    chgrp gpio /sys/class/gpio/gpio0/value
    chmod g+rw /sys/class/gpio/gpio0/value

    if [ ! -d /sys/class/gpio/gpio18 ] ; then
        echo -n "18" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio18/direction
    echo -n "1" > /sys/class/gpio/gpio18/value

    if [ ! -d /sys/class/gpio/gpio66 ] ; then
        echo -n "66" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio66/value

    #IO6 - Decoder, bit 6/14
    if [ ! -d /sys/class/gpio/gpio1 ] ; then
        echo -n "1" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio1/direction
    chgrp gpio /sys/class/gpio/gpio1/value
    chmod g+rw /sys/class/gpio/gpio1/value

    if [ ! -d /sys/class/gpio/gpio20 ] ; then
        echo -n "20" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio20/direction
    echo -n "1" > /sys/class/gpio/gpio20/value

    if [ ! -d /sys/class/gpio/gpio68 ] ; then
        echo -n "68" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio68/value

    #IO7 - Sensor de Fim de Curso
    if [ ! -d /sys/class/gpio/gpio38 ] ; then
        echo -n "38" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio38/direction
    chgrp gpio /sys/class/gpio/gpio38/value
    chmod g+rw /sys/class/gpio/gpio38/value

    #IO8 - Sensor de Fim de Curso
    if [ ! -d /sys/class/gpio/gpio40 ] ; then
        echo -n "40" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio40/direction
    chgrp gpio /sys/class/gpio/gpio40/value
    chmod g+r /sys/class/gpio/gpio40/value

    #IO9 - Decoder, bit 7/15
    if [ ! -d /sys/class/gpio/gpio4 ] ; then
        echo -n "4" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio4/direction
    chgrp gpio /sys/class/gpio/gpio4/value
    chmod g+rw /sys/class/gpio/gpio4/value

    if [ ! -d /sys/class/gpio/gpio22 ] ; then
        echo -n "22" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio22/direction
    echo -n "1" > /sys/class/gpio/gpio22/value

    if [ ! -d /sys/class/gpio/gpio70 ] ; then
        echo -n "70" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio70/value

    #IO10 - RPWM
    if [ ! -d /sys/class/pwm/pwmchip0/pwm11 ] ; then
        echo -n "11" > /sys/class/pwm/pwmchip0/export
    fi
    chgrp gpio /sys/class/pwm/pwmchip0/device/pwm_period
    chmod g+rw /sys/class/pwm/pwmchip0/device/pwm_period
    chgrp gpio /sys/class/pwm/pwmchip0/pwm11/duty_cycle
    chmod g+rw /sys/class/pwm/pwmchip0/pwm11/duty_cycle
    chgrp gpio /sys/class/pwm/pwmchip0/pwm11/enable
    chmod g+rw /sys/class/pwm/pwmchip0/pwm11/enable

    if [ ! -d /sys/class/gpio/gpio26 ] ; then
        echo -n "26" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio26/direction
    echo -n "0" > /sys/class/gpio/gpio26/value

    #gpio27 => NO PULL UP, NOR PULL DOWN
    if [ ! -d /sys/class/gpio/gpio27 ] ; then
        echo -n "27" > /sys/class/gpio/export
    fi
    echo -n "in" > /sys/class/gpio/gpio27/direction

    if [ ! -d /sys/class/gpio/gpio74 ] ; then
        echo -n "74" > /sys/class/gpio/export
    fi
    echo -n "1" > /sys/class/gpio/gpio74/value

    #IO11 - Decoder, Output Enable
    if [ ! -d /sys/class/gpio/gpio5 ] ; then
        echo -n "5" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio5/direction
    chgrp gpio /sys/class/gpio/gpio5/value
    chmod g+rw /sys/class/gpio/gpio5/value

    if [ ! -d /sys/class/gpio/gpio24 ] ; then
        echo -n "24" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio24/direction
    echo -n "0" > /sys/class/gpio/gpio24/value

    if [ ! -d /sys/class/gpio/gpio44 ] ; then
        echo -n "44" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio44/value

    if [ ! -d /sys/class/gpio/gpio72 ] ; then
        echo -n "72" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio72/value

    #IO12 - Decoder, SEL
    if [ ! -d /sys/class/gpio/gpio15 ] ; then
        echo -n "15" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio15/direction
    chgrp gpio /sys/class/gpio/gpio15/value
    chmod g+rw /sys/class/gpio/gpio15/value

    if [ ! -d /sys/class/gpio/gpio42 ] ; then
        echo -n "42" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio42/direction
    echo -n "0" > /sys/class/gpio/gpio42/value

    #IO13 - Decoder, RST
    if [ ! -d /sys/class/gpio/gpio7 ] ; then
        echo -n "7" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio7/direction
    chgrp gpio /sys/class/gpio/gpio7/value
    chmod g+rw /sys/class/gpio/gpio7/value

    if [ ! -d /sys/class/gpio/gpio30 ] ; then
        echo -n "30" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio30/direction
    echo -n "0" > /sys/class/gpio/gpio30/value

    if [ ! -d /sys/class/gpio/gpio46 ] ; then
        echo -n "46" > /sys/class/gpio/export
    fi
    echo -n "0" > /sys/class/gpio/gpio46/value

    #IO14 - H Bridge Driver, R_EN
    if [ ! -d /sys/class/gpio/gpio48 ] ; then
        echo -n "48" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio48/direction
    chgrp gpio /sys/class/gpio/gpio48/value
    chmod g+rw /sys/class/gpio/gpio48/value

    #IO15 - H Bridge Driver, L_EN
    if [ ! -d /sys/class/gpio/gpio50 ] ; then
        echo -n "50" > /sys/class/gpio/export
    fi
    echo -n "out" > /sys/class/gpio/gpio50/direction
    chgrp gpio /sys/class/gpio/gpio50/value
    chmod g+rw /sys/class/gpio/gpio50/value
	;;
    stop)
        echo -n "11" > /sys/class/gpio/unexport
        echo -n "32" > /sys/class/gpio/unexport
        echo -n "12" > /sys/class/gpio/unexport
        echo -n "28" > /sys/class/gpio/unexport
        echo -n "45" > /sys/class/gpio/unexport
        echo -n "13" > /sys/class/gpio/unexport
        echo -n "34" > /sys/class/gpio/unexport
        echo -n "77" > /sys/class/gpio/unexport
        echo -n "14" > /sys/class/gpio/unexport
        echo -n "16" > /sys/class/gpio/unexport
        echo -n "76" > /sys/class/gpio/unexport
        echo -n "64" > /sys/class/gpio/unexport
        echo -n "6" > /sys/class/gpio/unexport
        echo -n "36" > /sys/class/gpio/unexport
        echo -n "0" > /sys/class/gpio/unexport
        echo -n "18" > /sys/class/gpio/unexport
        echo -n "66" > /sys/class/gpio/unexport
        echo -n "1" > /sys/class/gpio/unexport
        echo -n "20" > /sys/class/gpio/unexport
        echo -n "68" > /sys/class/gpio/unexport
        echo -n "4" > /sys/class/gpio/unexport
        echo -n "22" > /sys/class/gpio/unexport
        echo -n "70" > /sys/class/gpio/unexport
        echo -n "38" > /sys/class/gpio/unexport
        echo -n "40" > /sys/class/gpio/unexport
        echo -n "4" > /sys/class/gpio/unexport
        echo -n "22" > /sys/class/gpio/unexport
        echo -n "70" > /sys/class/gpio/unexport
        echo -n "11" > /sys/class/gpio/unexport
        echo -n "26" > /sys/class/gpio/unexport
        echo -n "27" > /sys/class/gpio/unexport
        echo -n "74" > /sys/class/gpio/unexport
        echo -n "24" > /sys/class/gpio/unexport
        echo -n "25" > /sys/class/gpio/unexport
        echo -n "72" > /sys/class/gpio/unexport
        echo -n "15" > /sys/class/gpio/unexport
        echo -n "42" > /sys/class/gpio/unexport
        echo -n "7" > /sys/class/gpio/unexport
        echo -n "30" > /sys/class/gpio/unexport
        echo -n "46" > /sys/class/gpio/unexport
        echo -n "48" > /sys/class/gpio/unexport
        echo -n "50" > /sys/class/gpio/unexport

        echo -n "0" > /sys/class/pwm/pwmchip0/pwm11/enable
        echo -n "0" > /sys/class/gpio/gpio74/value

        echo -n "11" > /sys/class/pwm/pwmchip0/unexport

   	;;
    status)
	;;
    *)
    echo -n "Usage: $0 "
    echo "{start|stop|restart|force-reload|status}"
    exit 1
    ;;
esac

exit 0
