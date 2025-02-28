# nickkushner-bmssystem-fw
To develop firmware for bms system.
## Completed Objectives
1. Pack Voltage
2. Individual Cell Voltages
3. NTC temperature value
4. Charge Current
5. Discharge Current

## Libraries
1. [Library Folder](https://github.com/eSpark-Consultants/nickkushner-bmssystem/tree/Development-v1.0/Firmware/Libraries)  
**NOTE:** To install the libraries, Open IDE, Go to Sketch>Include Library>Add .ZIP Library. Then, install libraries one by one except jtag2updi-maaster.zip.

## Hardware Connections
**For UPDI:** (UPDI COM) Pin 3(PCB)->Pin 6(Digital I/O of Uno), Pin 2(PCB)->GND (Uno)

**For NTC**: Connect NTC on the given placement provided in the PCB(if not using, connect a 10k resistor on it).

**For Battery:** Connect to Battery +ve & -ve.

**For Charging:** Connect 12V on CHG+ & CHG-(keeping polarity in mind).

**For Discharging:** Connect Load on OUT+ & OUT-(keeping polarity in mind).

**For 3 cells:** Short SB5, SB6 & SB7.

**For Booting:** Connect a push button in the following configuration.
             C1 to One point of the push button.
             Second point of the push button followed by a 10k resistor to the +ve of NTC connection. 
![pwr_bms](https://github.com/eSpark-Consultants/nickkushner-bmssystem/assets/144008938/19948f70-3fa5-4381-904e-cc1d627530ea)
![i2c_bms](https://github.com/eSpark-Consultants/nickkushner-bmssystem/assets/144008938/f21d36bc-7236-46ae-a3a6-04f1fc0c940f)
![ntc_boot_bms](https://github.com/eSpark-Consultants/nickkushner-bmssystem/assets/144008938/2dc5e726-fc2c-47f8-a6db-c247251b30b2)

## STEPS FOR COMPILING AND UPLOADING
### Required Softwares
1. Arduino IDE (For Programming)
2. Coolterm (For Monitoring)

### Compiling & Uploading Procedure
1. Connect the Arduino Uno to the PC via USB 2.0 A/B cable.
2. Extract .zip from the libraries folder named "jtag2updi-master". Go to source and open the .ino file. Compile and upload that .ino to Arduino Uno by selecting the board and COM Port on which Uno is connected.
3. Open the IDE, Go to Preferences and copy paste below link in the Additional Boards manager URL:
(http://drazzy.com/package_drazzy.com_index.json)
4. Go to Boards manager by pressing Ctrl+Shift+B. Search megaTinyCore and install.
5. Then Go to Tools & Select the following:
    * Boards:     "Attiny3226/3216/1626/1616/1606/826/816/806/426/416/406"
    * Port:       COMxx (on which Uno is connected)
    * Chip:       "ATtiny1616"
    * Programmer: "jtag2updi"       
(Do not change any other setting except the above mentioned ones for programming)
6. Once all of the above are done, connect the batteries or cells, press the push button only once at the start, compile and upload your code.
7. Then, open coolterm and select baudrate:9600, COM port on which your serial is connected to monitor the microcontroller.       
**Note:** Whenever the source voltages are disconnected, you have to press the push button for boot pulse to the BMS IC after connecting the source voltages again at the start.

## STEPS FOR TROUBLESHOOTING
1. Remove the cells & make SB5 open.
2. Provide 3v3 to the board through UPDI Programming Port.
   ![image](https://github.com/user-attachments/assets/4d10f7c4-505e-4df8-b460-8ae1ee646d05)

4. Now follow the steps of compiling and uploading, ATtiny should be successfully programmed.
