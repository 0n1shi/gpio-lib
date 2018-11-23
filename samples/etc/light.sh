#!/bin/bash
GPIO_NUMBER="4"

LIGHT_STATUS_ON=1
LIGHT_STATUS_OFF=0

LIGHT_MODE_OUT="out"
LIGHT_MODE_IN="in"

echo $GPIO_NUMBER > /sys/class/gpio/export
echo $LIGHT_MODE_OUT > /sys/class/gpio/gpio$GPIO_NUMBER/direction

echo $LIGHT_STATUS_OFF > /sys/class/gpio/gpio$GPIO_NUMBER/value
echo $LIGHT_STATUS_ON > /sys/class/gpio/gpio$GPIO_NUMBER/value; sleep 1
echo $LIGHT_STATUS_OFF > /sys/class/gpio/gpio$GPIO_NUMBER/value

echo $GPIO_NUMBER > /sys/class/gpio/unexport
