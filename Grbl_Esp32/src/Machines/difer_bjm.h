#pragma once
// clang-format off

/*
    4axis_external_driver.h
    Part of Grbl_ESP32

    Pin assignments for the buildlog.net 4-axis external driver board
    https://github.com/bdring/4_Axis_SPI_CNC

    2018    - Bart Dring
    2020    - Mitch Bradley

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/


#define MACHINE_NAME            "Difer A25, Bjm Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 5

#define X_STEP_PIN              GPIO_NUM_17
#define X_DIRECTION_PIN         GPIO_NUM_27
#define B_STEP_PIN              GPIO_NUM_16
#define B_DIRECTION_PIN         GPIO_NUM_2
#define Z_STEP_PIN              GPIO_NUM_15
#define Z_DIRECTION_PIN         GPIO_NUM_4


#define SPINDLE_TYPE            SpindleType::PWM // only one spindle at a time
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_13
#define SPINDLE_ENABLE_PIN      GPIO_NUM_22


#define X_LIMIT_PIN             GPIO_NUM_34
#define Z_LIMIT_PIN             GPIO_NUM_35
#define B_LIMIT_PIN             GPIO_NUM_35


#define RAPID_FEED_DEPENDENT

#define CONTROL_RESET_PIN       GPIO_NUM_33  // labeled Reset, needs external pullup
#define CONTROL_FEED_HOLD_PIN   GPIO_NUM_36  // labeled Hold,  needs external pullup
#define CONTROL_CYCLE_START_PIN GPIO_NUM_39  // labeled Start, needs external pullup


//#define PROBE_PIN               GPIO_NUM_39
#define COOLANT_MIST_PIN        GPIO_NUM_25

#define USER_DIGITAL_PIN_0 GPIO_NUM_26


#ifdef DEFAULT_HOMING_CYCLE_0
	#undef DEFAULT_HOMING_CYCLE_0
#endif
#ifdef DEFAULT_HOMING_CYCLE_1
	#undef DEFAULT_HOMING_CYCLE_1
#endif
#ifdef DEFAULT_HOMING_CYCLE_2
	#undef DEFAULT_HOMING_CYCLE_2
#endif

#define DEFAULT_HOMING_CYCLE_0 bit(Z_AXIS)
#define DEFAULT_HOMING_CYCLE_1 bit(X_AXIS)
#define DEFAULT_HOMING_CYCLE_2 bit(B_AXIS)


/*
[MSG:Grbl_ESP32 Ver 1.3a Date 20210424]
[MSG:Compiled with ESP32 SDK:v3.2.3-14-gd3e562907]
[MSG:Using machine:Difer A25, Bjm Machine]
[MSG:Axis count 5]
[MSG:RMT Steps]
[MSG:Reset switch on pin GPIO(33)]
[MSG:Hold switch on pin GPIO(36)]
[MSG:Start switch on pin GPIO(39)]
[MSG:User Digital Output:0 on Pin:GPIO(26)]
[MSG:Init Motors]
[MSG:X  Axis Standard Stepper Step:GPIO(17) Dir:GPIO(27) Disable:None Limits(-281.500,0.000)]
[MSG:Z  Axis Standard Stepper Step:GPIO(15) Dir:GPIO(4) Disable:None Limits(-127.000,0.000)]
[MSG:B  Axis Standard Stepper Step:GPIO(16) Dir:GPIO(2) Disable:None Limits(-79.000,0.000)]
[MSG:PWM spindle Output:GPIO(13), Enbl:GPIO(22), Dir:None, Freq:800Hz, Res:16bits]
[MSG:BT Started with btgrblesp]
[MSG:Mist coolant on pin GPIO(25)]
[MSG:X  Axis limit switch on pin GPIO(34)]
[MSG:Z  Axis limit switch on pin GPIO(35)]
[MSG:B  Axis limit switch on pin GPIO(35)]
$Sta/SSID=GRBL_ESP
$Sta/Password=******
$Sta/IPMode=DHCP
$Sta/IP=0.0.0.0
$Sta/Gateway=0.0.0.0
$Sta/Netmask=0.0.0.0
$AP/SSID=GRBL_ESP
$AP/Password=******
$AP/IP=192.168.0.1
$AP/Channel=1
$System/Hostname=grblesp
$Http/Enable=ON
$Http/Port=80
$Telnet/Enable=ON
$Telnet/Port=23
$Radio/Mode=BT
$Bluetooth/Name=btgrblesp
$Notification/Type=NONE
$Notification/T1=
$Notification/T2=
$Notification/TS=
$Message/Level=Info
$User/Macro0=
$User/Macro1=
$User/Macro2=
$User/Macro3=
$Homing/Cycle0=Z
$Homing/Cycle1=X
$Homing/Cycle2=B
$Homing/Cycle3=
$Homing/Cycle4=
$Homing/Cycle5=
$Report/StallGuard=
$Stepper/Enable/Delay=0
$Stepper/Direction/Delay=0
$Stepper/Pulse=5
$Stepper/IdleTime=250
$Stepper/StepInvert=
$Stepper/DirInvert=XZB
$Stepper/EnableInvert=Off
$Limits/Invert=Off
$Probe/Invert=Off
$Report/Status=1
$GCode/JunctionDeviation=0.010
$GCode/ArcTolerance=0.002
$Report/Inches=Off
$Firmware/Build=
$Limits/Soft=On
$Limits/Hard=Off
$Homing/Enable=On
$Homing/DirInvert=
$Homing/Squared=
$Homing/Feed=200.000
$Homing/Seek=1000.000
$Homing/Debounce=250.000
$Homing/Pulloff=1.000
$GCode/MaxS=2000.000
$GCode/MinS=0.000
$Laser/FullPower=1000
$GCode/LaserMode=Off
$GCode/Line1=
$GCode/Line0=
$Spindle/Enable/Invert=Off
$Spindle/Enable/OffWithSpeed=Off
$Coolant/Delay/TurnOn=1.000
$Spindle/Delay/SpinDown=0.000
$Spindle/Delay/SpinUp=0.000
$Spindle/PWM/Invert=On
$Spindle/PWM/Frequency=800.000
$Spindle/PWM/Off=0.000
$Spindle/PWM/Min=0.000
$Spindle/PWM/Max=100.000
$Spindle/Type=PWM
$X/StepsPerMm=100.000
$Y/StepsPerMm=400.000
$Z/StepsPerMm=200.000
$A/StepsPerMm=400.000
$B/StepsPerMm=100.000
$C/StepsPerMm=400.000
$X/MaxRate=10000.000
$Y/MaxRate=3500.000
$Z/MaxRate=10000.000
$A/MaxRate=3500.000
$B/MaxRate=5000.000
$C/MaxRate=3500.000
$X/Acceleration=2000.000
$Y/Acceleration=400.000
$Z/Acceleration=2000.000
$A/Acceleration=400.000
$B/Acceleration=400.000
$C/Acceleration=400.000
$X/Home/Mpos=0.000
$Y/Home/Mpos=0.000
$Z/Home/Mpos=0.000
$A/Home/Mpos=0.000
$B/Home/Mpos=0.000
$C/Home/Mpos=0.000
$X/MaxTravel=281.500
$Y/MaxTravel=300.000
$Z/MaxTravel=127.000
$A/MaxTravel=300.000
$B/MaxTravel=79.000
$C/MaxTravel=300.000
$X/Current/Run=0.250
$Y/Current/Run=0.250
$Z/Current/Run=0.250
$A/Current/Run=0.250
$B/Current/Run=0.250
$C/Current/Run=0.250
$X/Current/Hold=0.125
$Y/Current/Hold=0.125
$Z/Current/Hold=0.125
$A/Current/Hold=0.125
$B/Current/Hold=0.125
$C/Current/Hold=0.125
$X/Microsteps=16
$Y/Microsteps=16
$Z/Microsteps=16
$A/Microsteps=16
$B/Microsteps=16
$C/Microsteps=16
$X/StallGuard=16
$Y/StallGuard=16
$Z/StallGuard=16
$A/StallGuard=16
$B/StallGuard=16
$C/StallGuard=16
$Errors/Verbose=Off
 */
