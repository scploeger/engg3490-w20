EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ENGG3490 Robot"
Date "2020-03-29"
Rev "1"
Comp "S. Ploeger"
Comment1 "Group/Locker #3"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino:Arduino_Mega2560_Shield XA1
U 1 1 5E80E06E
P 5400 3550
F 0 "XA1" H 5400 1169 60  0000 C CNN
F 1 "Arduino_Mega2560_Shield" H 5400 1063 60  0000 C CNN
F 2 "" H 6100 6300 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 6100 6300 60  0001 C CNN
	1    5400 3550
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_Servo M1
U 1 1 5E825824
P 7300 1000
F 0 "M1" H 7632 1065 50  0000 L CNN
F 1 "Motor_Servo" H 7632 974 50  0000 L CNN
F 2 "" H 7300 810 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 7300 810 50  0001 C CNN
	1    7300 1000
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M4
U 1 1 5E82A619
P 10050 1900
F 0 "M4" H 10208 1896 50  0000 L CNN
F 1 "Motor_DC" H 10208 1805 50  0000 L CNN
F 2 "" H 10050 1810 50  0001 C CNN
F 3 "~" H 10050 1810 50  0001 C CNN
	1    10050 1900
	1    0    0    -1  
$EndComp
$Comp
L project_lib:GP2D120 RF1
U 1 1 5E831F1A
P 3400 2450
F 0 "RF1" H 3678 2288 50  0000 L CNN
F 1 "GP2D120" H 3678 2197 50  0000 L CNN
F 2 "" H 3400 2450 50  0001 C CNN
F 3 "" H 3400 2450 50  0001 C CNN
	1    3400 2450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5E833FCF
P 7200 4250
F 0 "SW2" H 7200 4535 50  0000 C CNN
F 1 "SW_Push" H 7200 4444 50  0000 C CNN
F 2 "" H 7200 4450 50  0001 C CNN
F 3 "~" H 7200 4450 50  0001 C CNN
	1    7200 4250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 5E835091
P 3550 5700
F 0 "SW1" H 3550 5935 50  0000 C CNN
F 1 "SW_SPST" H 3550 5844 50  0000 C CNN
F 2 "" H 3550 5700 50  0001 C CNN
F 3 "~" H 3550 5700 50  0001 C CNN
	1    3550 5700
	1    0    0    -1  
$EndComp
$Comp
L project_lib:L293 U1
U 1 1 5E85BC88
P 8700 1500
F 0 "U1" H 8800 1500 50  0000 C CNN
F 1 "L293" H 8750 600 50  0000 C CNN
F 2 "" H 8800 1650 50  0001 C CNN
F 3 "" H 8800 1650 50  0001 C CNN
	1    8700 1500
	1    0    0    -1  
$EndComp
Text Notes 2050 5600 0    50   ~ 0
-
Text Notes 2050 5750 0    50   ~ 0
+
Text Notes 1300 5650 0    50   ~ 0
From LiPo Battery
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5E83651A
P 2200 5700
F 0 "J1" H 2118 5375 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 2118 5466 50  0000 C CNN
F 2 "" H 2200 5700 50  0001 C CNN
F 3 "~" H 2200 5700 50  0001 C CNN
	1    2200 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 5200 2800 5600
$Comp
L Motor:Motor_DC M2
U 1 1 5E82A613
P 7500 1900
F 0 "M2" H 7658 1896 50  0000 L CNN
F 1 "Motor_DC" H 7658 1805 50  0000 L CNN
F 2 "" H 7500 1810 50  0001 C CNN
F 3 "~" H 7500 1810 50  0001 C CNN
	1    7500 1900
	1    0    0    -1  
$EndComp
Text GLabel 8400 2300 0    50   Input ~ 0
VIN
Text GLabel 9150 2300 2    50   Input ~ 0
VIN
Wire Wire Line
	3950 5400 4100 5400
Text GLabel 3950 5400 0    50   Input ~ 0
5V
Text GLabel 8400 1600 0    50   Input ~ 0
5V
Text GLabel 9150 1600 2    50   Input ~ 0
5V
Wire Wire Line
	8400 1800 8050 1800
Wire Wire Line
	8050 1800 8050 1700
Wire Wire Line
	8050 1700 7500 1700
Wire Wire Line
	7500 2200 8050 2200
Wire Wire Line
	8050 2200 8050 2100
Wire Wire Line
	8050 2100 8400 2100
Wire Wire Line
	9150 2100 9500 2100
Wire Wire Line
	9500 2100 9500 2200
Wire Wire Line
	10050 1700 9500 1700
Wire Wire Line
	9500 1700 9500 1800
Wire Wire Line
	9500 1800 9150 1800
Wire Wire Line
	9500 2200 10050 2200
Text GLabel 2800 5200 0    50   Input ~ 0
GND
Text GLabel 8400 2000 0    50   Input ~ 0
GND
Text GLabel 8400 1900 0    50   Input ~ 0
GND
Text GLabel 9150 1900 2    50   Input ~ 0
GND
Text GLabel 9150 2000 2    50   Input ~ 0
GND
$Comp
L Motor:Motor_DC M5
U 1 1 5E8A0F6B
P 10050 3000
F 0 "M5" H 10208 2996 50  0000 L CNN
F 1 "Motor_DC" H 10208 2905 50  0000 L CNN
F 2 "" H 10050 2910 50  0001 C CNN
F 3 "~" H 10050 2910 50  0001 C CNN
	1    10050 3000
	1    0    0    -1  
$EndComp
$Comp
L project_lib:L293 U2
U 1 1 5E8A0F71
P 8700 2600
F 0 "U2" H 8800 2600 50  0000 C CNN
F 1 "L293" H 8750 1700 50  0000 C CNN
F 2 "" H 8800 2750 50  0001 C CNN
F 3 "" H 8800 2750 50  0001 C CNN
	1    8700 2600
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M3
U 1 1 5E8A0F77
P 7500 3000
F 0 "M3" H 7658 2996 50  0000 L CNN
F 1 "Motor_DC" H 7658 2905 50  0000 L CNN
F 2 "" H 7500 2910 50  0001 C CNN
F 3 "~" H 7500 2910 50  0001 C CNN
	1    7500 3000
	1    0    0    -1  
$EndComp
Text GLabel 8400 3400 0    50   Input ~ 0
VIN
Text GLabel 9150 3400 2    50   Input ~ 0
VIN
Text GLabel 8400 2700 0    50   Input ~ 0
5V
Text GLabel 9150 2700 2    50   Input ~ 0
5V
Wire Wire Line
	8400 2900 8050 2900
Wire Wire Line
	8050 2900 8050 2800
Wire Wire Line
	8050 2800 7500 2800
Wire Wire Line
	7500 3300 8050 3300
Wire Wire Line
	8050 3300 8050 3200
Wire Wire Line
	8050 3200 8400 3200
Wire Wire Line
	9150 3200 9500 3200
Wire Wire Line
	9500 3200 9500 3300
Wire Wire Line
	10050 2800 9500 2800
Wire Wire Line
	9500 2800 9500 2900
Wire Wire Line
	9500 2900 9150 2900
Wire Wire Line
	9500 3300 10050 3300
Text GLabel 8400 3100 0    50   Input ~ 0
GND
Text GLabel 8400 3000 0    50   Input ~ 0
GND
Text GLabel 9150 3000 2    50   Input ~ 0
GND
Text GLabel 9150 3100 2    50   Input ~ 0
GND
Wire Wire Line
	6700 1600 8150 1600
Wire Wire Line
	8150 1600 8150 1700
Wire Wire Line
	8150 1700 8400 1700
Wire Wire Line
	6700 1700 7200 1700
Wire Wire Line
	7200 1700 7200 2300
Wire Wire Line
	7200 2300 8150 2300
Wire Wire Line
	8150 2300 8150 2200
Wire Wire Line
	8150 2200 8400 2200
Wire Wire Line
	6700 1800 7100 1800
Wire Wire Line
	7100 1800 7100 2450
Wire Wire Line
	7100 2450 9400 2450
Wire Wire Line
	9400 2450 9400 2200
Wire Wire Line
	9400 2200 9150 2200
Wire Wire Line
	6700 1900 6950 1900
Wire Wire Line
	6950 1900 6950 1450
Wire Wire Line
	6950 1450 9400 1450
Wire Wire Line
	9400 1450 9400 1700
Wire Wire Line
	9400 1700 9150 1700
Wire Wire Line
	6700 2000 6950 2000
Wire Wire Line
	6950 2550 8200 2550
Wire Wire Line
	8200 2550 8200 2800
Wire Wire Line
	8200 2800 8400 2800
Wire Wire Line
	6950 2000 6950 2550
Wire Wire Line
	8400 3300 8150 3300
Wire Wire Line
	8150 3300 8150 3450
Wire Wire Line
	6900 3450 6900 2100
Wire Wire Line
	6900 2100 6700 2100
Wire Wire Line
	6900 3450 8150 3450
Wire Wire Line
	6700 2200 6850 2200
Wire Wire Line
	6850 2200 6850 3600
Wire Wire Line
	6850 3600 9400 3600
Wire Wire Line
	9400 3600 9400 3300
Wire Wire Line
	9400 3300 9150 3300
Wire Wire Line
	6700 2300 6800 2300
Wire Wire Line
	6800 2300 6800 3750
Wire Wire Line
	6800 3750 9450 3750
Wire Wire Line
	9450 3750 9450 2800
Wire Wire Line
	9450 2800 9150 2800
Text GLabel 3200 2800 3    50   Input ~ 0
5V
Text GLabel 3400 2800 3    50   Input ~ 0
GND
Wire Wire Line
	3600 2800 4100 2800
Text GLabel 7000 1000 0    50   Input ~ 0
5V
Text GLabel 7000 1100 0    50   Input ~ 0
GND
Wire Wire Line
	6700 1500 6750 1500
Wire Wire Line
	6750 1500 6750 900 
Wire Wire Line
	6750 900  7000 900 
Wire Wire Line
	2400 5700 3350 5700
Wire Wire Line
	7400 4250 7800 4250
Wire Wire Line
	6700 2500 6750 2500
Wire Wire Line
	6750 2500 6750 4250
Wire Wire Line
	6750 4250 6900 4250
Wire Wire Line
	6900 4250 6900 4400
Wire Wire Line
	6900 4400 6950 4400
Connection ~ 6900 4250
Wire Wire Line
	6900 4250 7000 4250
$Comp
L Device:R R1
U 1 1 5E8FC706
P 7100 4400
F 0 "R1" V 7307 4400 50  0000 C CNN
F 1 "R" V 7216 4400 50  0000 C CNN
F 2 "" V 7030 4400 50  0001 C CNN
F 3 "~" H 7100 4400 50  0001 C CNN
	1    7100 4400
	0    -1   -1   0   
$EndComp
Text GLabel 7250 4400 2    50   Input ~ 0
GND
Text GLabel 7800 4250 1    50   Input ~ 0
5V
Wire Wire Line
	2800 5600 2400 5600
Wire Wire Line
	3750 5700 4100 5700
Wire Wire Line
	4100 5200 2800 5200
Text GLabel 3900 5700 3    50   Input ~ 0
VIN
$EndSCHEMATC
