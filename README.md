# homectrl
> system for general home automation. (custom PCBs in KiCad, firmware in C/C++, web-app in Next.js)

**huge thanks to PCBWay for sponsoring this project's first revision.**<br>
[check out **REV A**](https://github.com/jeevan9s/homectrl-sys/tree/rev-A)

<hr>

**REV B Updates**: 
* board is currently out for fab. 
* main controller features a much more compact layout, 4L mixed-signal design, SMD-first component selection. 
* onboard ADC, stepper motor driver, power management. 
* all IC breakout circuitry was custom desgined, no breakout-boards were used. 
* designed a standalone [ALS](https://github.com/jeevan9s/homectrl-sys/tree/rev-B/hardware/lux-module) (ambient-light-sensor) breakout module for further automation capability.


<details>
<summary>Contents</summary>

- [overview](#overview)
- [architecture](#architecture)
- [prerequisites / installation](#prerequisites--installation)
- [acknowledgements](#acknowledgements)
- [contact](#contact)

</details>

# Overview
<table width="100%" cellspacing="0" cellpadding="5">
  <tr>
    <td align="center" width="50%">
      <img src="./media/homectrlREVB-frontview.png" style="width: 100%; height: auto;">
    </td>
    <td align="center" width="50%">
      <img src="./media/homectrlREVB-backview.png" style="width: 100%; height: auto;">
    </td>
  </tr>
</table>

<table width="100%" cellspacing="0" cellpadding="5">
    <tr>
    <td align="center" width="100%">
      <img src="./media/homectrl-webapp-dash.png" style="width: 100%; height: auto;">
    </td>
  </tr>
</table>






I built **homectrl** to modularize and automate my first apartment.



## Built With
- **KiCad**
- ![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
- ![Espressif](https://img.shields.io/badge/espressif-E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white)
- ![Next.js](https://img.shields.io/badge/Next-black?style=for-the-badge&logo=next.js&logoColor=white)
- ![TailwindCSS](https://img.shields.io/badge/tailwindcss-%2338B2AC.svg?style=for-the-badge&logo=tailwind-css&logoColor=white)


# Architecture
## System
> More info coming soon, after midterm season :)

### Prerequisites
- <b>Software:</b> Arduino IDE (with Espressif ESP32 board support)
- <b>Libraries:</b> PubSubClient, SinricPro, WebSockets, and any other dependencies listed in firmware
- <b>Node.js:</b> v18+ (for Next.js dashboard)
- <b>Package Manager:</b> npm or yarn

### Installation
1. Clone the repository:
```bash
git clone https://github.com/jeevan9s/homectrl.git
cd homectrl
```

## Acknowledgements
Thanks again to **[PCBWay]([url](https://www.pcbway.com/))** for supporting this project.  
Their workflow and quality made prototyping straightforward and reliable, and I’ll definitely be using their service for future PCB projects.

<!-- 
<table width="100%" cellspacing="0" cellpadding="5">
  <tr>
    <td align="center" width="50%">
      <img src="./media/homectrl-f2.jpg" style="width: 100%; height: auto;">
    </td>
    <td align="center" width="50%">
      <img src="./media/homectrl-fs.png" style="width: 100%; height: auto;">
    </td>
  </tr>
</table> -->

## Contact 
[`email`](mailto:jeevansanchez42@gmail.com)&nbsp;&nbsp;&nbsp; [``LinkedIn``](https://linkedin.com/in/jeevansanchez)


