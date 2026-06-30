# homectrl

Home-automation controller with a Next.js dashboard. 

 ### Status
>- Controller PCB currently being manufactures
>- Firmware and docs development in progress.
>- Mechanical components currently being printed.

<details>
<summary><strong>Table of Contents</strong></summary>

- [homectrl](#homectrl)
    - [Status](#status)
  - [Overview](#overview)
  - [Features](#features)
    - [Controller](#controller)
    - [App](#app)
    - [Mechanical](#mechanical)
  - [Architecture](#architecture)
    - [Systems](#systems)
  - [Electrical](#electrical)
    - [Power System](#power-system)
    - [Microcontroller](#microcontroller)
    - [Pump Interface](#pump-interface)
    - [Stepper Motor Interface](#stepper-motor-interface)
    - [Peripheral Devices](#peripheral-devices)
  - [Mechanical](#mechanical-1)
    - [Container](#container)
    - [Lid](#lid)
  - [Firmware](#firmware)
  - [Web-App](#web-app)
  - [Repository Structure](#repository-structure)
  - [Gallery](#gallery)

</details>

I built homectrl because I wanted to automate my first apartment. 

<table> 
  <tr> 
    <td width="50%"> 
      <img src="/media/images/controller_f_3D.png" width="800"> 
    </td> 
    <td width="50%"> 
      <img src="/media/images/controller_b_3D.png" width="800"> 
    </td> 
  </tr> 
</table>

## Overview
Building practical is a consistent motive when developing. 

As I moved into my first apartment during my first year at Queen's University, I wanted a device capable of smart-control for plants and window blinds, which are main components of my studio. This pushed me to build **homectrl**, a controller that leverages sensor readings, actuators, and WiFi for home automation. 

The first version was manufactured in October of 2025, and this was my first PCB designed. It was a bit elementary, lots of breakout boards soldered on, an MCU devkit, etc. 
Over the year I designed several other PCBs and learned a lot, which pushed me to produce a second version that I can use reliably for my 2nd year in Kingston. 

It's now June and the controller is being manufactured while I write docs and firmware. 

## Features 
### Controller

The controller is powered by a 12V 2A adapter and driven by an ESP32-S3.

Below is a list of features from power circuits to various peripherals. 
- Power-entry circuitry with OC/OV protetction, RPP, and PI-filter
- Regulation circuit featuring buck converter, 5V ORing, and LDO for logic power (3V3) 
- ESP32-S3 breakout circuitry with USB differential routing, S3 boot mode selection and reset toggle. 
- Controlled power delivery via CMOS and PMOS for main pump and moisture sensor power. 
- Low-side switching for pump control. 
- Stepper motor driven by TMC2209 with UART for blind control. 
- Float switches for monitoring irrigation tank. 
- Analog soil moisture sensor connectors with local RC filters. 
- ESD protection with TVS diode arrays on all external connections. 
- Visual and audible indication. 

### App

The controller communicates to a Next.js webapp via Websockets and is also connected to Alexa via SinricPro for voice control, over WiFi/MQTT.

- Next.js dashboard with modern responsive shadCN-tailwindcss UI. 
- Slider and switch control via UI. 
- Voice control with Alexa via SinricPro

### Mechanical 
- Lightweight container with USB and power ports and slots for cable management.
- Vents for airflow and audible indication. 
- Magnetic joints for easy lid removal and secure operation. 

## Architecture 
### Systems 

## Electrical 

This section provides low-level explanations of the significant circuits of each "module" of the controller.

I encourage you to clone the repo or you use [KiCanvas](https://kicanvas.org/) to look at the schematic and board files. 

All electronics were designed with **KiCad**.

### Power System

**Power Entry**
<p align="center">
  <img src="/media/images/circuits/pwr/power_entry.png" width="500">
</p>

The 12V 2A power enters through a barrel jack connector, where it is then met with a 24V 3A fuse for over-current protection. A PTC resettable fuse was selected for durability. 

The positive plug line `VPLUG` is then protected from voltage spikes with a Transient Voltage Supression (TVS) diode placed in paralell for clamping. 
- The diode's standoff @ `14V`
- Breakdown @ `15.3V`
- Clamps @ `23.2V`

The positive line then goes through a Reverse Polarity Protection (RPP) circuit, using a P-Channel MOSFET for lossless efficiency (lower V drop than standard diodes). 

A Zener diode and resistor is placed between the MOSFET's gate and source for gate over-voltage protection. 

A bulk electrolytic (100μF) capacitor, ferrite bead, and high-frequency (0.1μF) capacitor are then placed to create a third-order low pass filter (π-filter). 
- This is used to smooth voltage spikes and reduce EMI.

The ferrite bead was primariy selected for its saturation current and DCR. 

The approximate current draw with safety margin $I_{net}$ is 2A.

$I_{\mathrm{sat}} = 1.5 \times I_{\mathrm{net}} \approx 3 A$

Minimize heat dissipation. 

$DCR$ is 20Ω

$P_{heat} = DCR \times I_{\mathrm{sat}} \approx 0.06 W$

**Voltage Regulation (I)**
<p align="center">
  <img src="/media/images/circuits/pwr/buck.png" width="500">
</p>

The controller uses a cascade regulation system, starting with the `TPS5405DR` buck converter. 

The input voltage is `VPLUG` (12V), after the protection and filtering circuitry, and the output is 5V. 

The $R_{osc}$ value will determine the switching frequency of the converter. 

Switching frequency is governed by the relationship. 
$$R_{\text{OSC}} (\text{k}\Omega) = 21.82 \cdot f_{\text{SW}}^{-1.167}$$

I chose a value of `50kΩ` for a $f_{SW}$ of approximately `525 kHz`

For the soft-start capacitor $C_{ss}$ , I chose a value of `10nF` for a soft-start time of `5ms`

The values below were taken from the [TPS5405DR Datasheet](https://www.ti.com/lit/gpn/tps5405)

$$
C_{SS} = \frac{t_{SS} \cdot I_{SS}}{V_{REF}}
$$

$$
C_{SS} = \frac{(5\,\mathrm{ms})(2\,\mathrm{\mu A})}{0.8\,\mathrm{V}}
= 12.5\,\mathrm{nF}
\approx 10\,\mathrm{nF}
$$

The inductor values were chosen using the equation below. 

$$
L=\frac{V_{out}\left(V_{in}-V_{out}\right)}
{V_{in}f_{sw}\Delta I_L}
$$

Using our calculated $f_{sw}$ from above and our voltage requirements (12V in, 5V out):
$$
L=
\frac{(5\,\mathrm{V})(12\,\mathrm{V}-5\,\mathrm{V})}
{(12\,\mathrm{V})(490\,\mathrm{kHz})(0.6\,\mathrm{A})}

\approx
10\,\mathrm{\mu H}
$$

The Schottky diode is rated for the `2A` output current and `12V`

**5V ORing**
<p align="center">
  <img src="/media/images/circuits/pwr/oring.png" width="500">
</p>

The `5V` rails from both USB and the buck converter are combined using an OR-ing circuit (Dual Ideal Diodes) to prevent backfeeding before feeding the second stage of regulation.

In this configuration, the outputs of both `LM66100` ideal diode controllers are tied together to form the shared `5V` rail. The `CE` pins of each device are also tied to the output rail, ensuring both controllers are only enabled once the rail is present 

This allows for testing over serial with devices that are powered by `VPLUG` (12V). 

**Voltage Regulation (II)**
<p align="center">
  <img src="/media/images/circuits/pwr/ldo.png" width="500">
</p>

The second stage of voltage regulation involes a Low-Dropout Regulator (LDO), the `MCP1826S`

It is fed the combined `5V` rail from the OR-ing circuit to produce the controller's logic-level voltage: `3V3`

**Controlled Pump Power Delivery**
<p align="center">
  <img src="/media/images/circuits/pwr/cmos.png" width="500">
</p>

The power for the pumps is controlled using a complementary-MOSFET (CMOS) setup, driven by a digital `HIGH` from the S3.

- When the control signal is low or floating, the N-channel MOSFET remains off and a pull-up resistor holds the gate of the P-channel MOSFET at the supply voltage, keeping it disabled and disconnecting the load rail.
- When the control signal is driven high, the N-channel MOSFET turns on and pulls the P-channel gate low, creating sufficient gate-source voltage to enable conduction and connect the supply to the load.

**Voltage Sensing**

A resistor divider circuit is used to produce a signal to be read by the S3's internal ADC.

- $R_1 = 100\,\mathrm{k\Omega}$
- $V_{plug} = 12\,\mathrm{V}$
- $V_{out} = 2\,\mathrm{V}$

$$
R_2 = \frac{R_1 \cdot V_{out}}{V_{batt} - V_{out}}
$$

$$
R_2 = \frac{100\,000 \cdot 2}{12 - 2}
= 20\,\mathrm{k\Omega}
$$

### Microcontroller
The controller is driven by an ESP32-S3-WROOM microcontroller.

**Digital IO**
<p align="center">
  <img src="/media/images/circuits/mcu/s3.png" width="500">
</p>

**Mode Select and Reset Toggle**
<p align="center">
  <img src="/media/images/circuits/mcu/s3_toggles.png" width="400">
</p>

The S3 can be put into **BOOT** mode and **RESET** with onboard buttons.

**BOOT** mode determines whether the chip runs existing code from flash memory or waits to download new firmware.
- The ESP32 samples the **BOOT** pin (`GPIO0`) during reset to determine the boot mode.
- It is **active-low**: when pulled to **GND** during reset, the chip enters UART bootloader mode for flashing firmware.
- The circuit uses a momentary push-button to **GND** and a `10kΩ` pull-up resistor to ensure a defined high state during normal operation.

| BOOT0 Level | Boot Mode |
|-------------|-----------|
| HIGH | Programming Mode |
| LOW | Memory Mode |

**RESET** controls the Enable (EN) pin which is the ON/OFF (reset) switch for the ESP32.
- It is **active-low**: when pulled to **GND** it turns off the chip, and when released, it restarts.
- The circuit consists of a momentary push-button, a pull-up resistor to ensure the chip is enabled by default, and a `1µF` capacitor to filter out button noise.

### Pump Interface

<table><tr><td width="50%"><img src="/media/images/circuits/actuators/pump_conns.png"></td><td width="50%"><img src="/media/images/circuits/actuators/pump_drivers.png"></td></tr></table>

The controller interfaces with 12V 300mA rated pumps for irrigation. 

These pumps connect via JST-XH vertical headers and are met with flyback diodes for inductive spike protection, and decoupling to filter out noise. 

Each pump is controlled by a low-side switch using an `A03400A` N-channel MOSFET. 
- The gate of the MOSFET is driven by an S3 GPIO pin and is pulled down to GND for state definition. 
- The drain is connected to the negative terminal of the pump and the source to GND. 

This will bridge the negative pump terminal to GND and effectively turn it `ON` when the gate is `HIGH`. 

### Stepper Motor Interface
<img src="/media/images/circuits/actuators/tmc.png" width="400">

The controller interfaces with a stepper motor through a `TMC2209` driver for blind control. 

The `NEMA 17` stepper motor connects via a vertical 4-position JST-XH header. 

The positive and negative terminals of both stepper coils feed the OBX and OAX pins of the driver. 

The driver is powered by `VPLUG` and is decoupled for bulk and high-frequency noise with electrolytic and ceramic capacitors. 
- The driver is put to sleep by the `ENN` pin to avoid power consumption, which is why I didn't use a CMOS/controlled-power delivery setup.

The main control signals are `STEP` and `DIR`, controlling the speed and direction, respectively. These connect digital pins on the S3. 

The single-wire UART interface was used for advanced chip config, live diagnostics, and features. 

The `BRA` and `BRB` connect to `0.11Ω` sense resistors to monitor and regulate current through the motor coils. 

For addressing, the `MS1_AD01` and `MS2_AD1` pins are pulled low to set the binary address bits to `00` and the UART slave address to `%0`. 

The `CP0` and `CP1` pins are tied together with a 22nF capacitor to generate a boost voltage for the internal charge pump. This boosted voltage switches the internal N-channel MOSFETs fully on. 

### Peripheral Devices

**Sensors**
<img src="/media/images/circuits/periphs/sms.png" width="400">

The controller interfaces with two capactive soil-moisture sensors (SMS) and an Ambient Light Sensor (ALS). 

These connections are made with vertical 4-pin JST-XH headers. 

I designed the ALS breakout board, in the future I'd be interested in designing the moisture sensors. For now I'm using the Adafruit models.

The `3V3` SMS power  is controlled through a simple `A03407A` P-channel mosfet, and the signals are filtered with a resistor-capacitor network at the S3 ADC pins. 

The ALS communicates with the `I2C` protocol and is powered by `3V3`. 

The two analog signals and I2C clock and data signals are ESD-protected by a `TPD43001` TVS diode array.

**Float Switches**
<img src="/media/images/circuits/periphs/fsw.png" width="400">

The controller interfaces with two float switches. 

These connections are made with a vertical 3-pin JST-XH header. 

The signals are pulled up to 3V3 to establish a defined logic stateand filtered with a resistor-capacitor network at the S3 ADC pins. 

**Indicator Components**
- RGB LED
- Passive LEDs for simple indication
- Buzzer for audible indication

## Mechanical 
This section provides insight on the mechanical components of homectrl. 

I used Fusion360 to design everything.   

<img src="/media/images/cad/assembly.png" width="500">

### Container
<img src="/media/images/cad/container.png" width="400">

The container uses a rounded-rectangular exterior to house the board. 

The board is mounted using M2 standoffs designed from the base of the container. 

- It features USB-C and barrel-jack portholes for easy flashing and power connection.
- The backside has slot cutouts for actuator and sensor cables. 
- Vent holes were used throughout the container for airflow and weight management (more lightweight).

### Lid 
<img src="/media/images/cad/lid.png" width="400">

The lid is mounted magnetically on the outer top face of the container using projected holes for small magnets. 
- Its design is honestly quite minimal, I did add a small hole for the controller's RGB LED to shine through. 


## Firmware

## Web-App

## Repository Structure 

## Gallery 

**huge thanks to PCBWay for sponsoring this project's first revision.**<br>
[check out **REV A**](https://github.com/jeevan9s/homectrl-sys/tree/rev-A)

---
Jeevan Sanchez, 2026
