# IoT Fridge Guardian with MSP432-P401R

<details>
<summary><b>Table of contents</b></summary>

1. [About](#about)
2. [Project layout](#project-layout)
3. [Functionalities](#functionalities-description)
4. [Demonstration](#demonstration)
5. [Requirements](#requirements)
6. [Programming language](#programming-language)
7. [Team members & contributions](#team-members--contributions)

</details>
<br>



# About

Welcome to **`IoT Fridge Guardian`**, an embedded software solution designed for Internet of Things (IoT)-enabled refrigerators.  
This project aims to enhance your food storage experience by providing real-time monitoring and expiry reminders & alerts with intuitive controls for your smart fridge.
Stay in control of your fridge, minimize waste, and ensure your food stays fresh effortlessly.

<div align="center">
  <a> <img src="/Images/fridgeLogo.jpg" width="300" height="300"> </a>
</div>

<div align="right">
    
[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>


# Project layout

### Code organization tree

```bash
MSP432-Fridge-Guardian-Project
├───Debug                         # compiled files
├───Drivers
│   └───Lcd                       # LCD screen related files
├───Logic
│   ├───Graphics                  # files to manage views
│   └───Interrupts                # interrupts handlers
├───targetConfigs                 # target configuration
├───Images
├─── README.md                    # project overview file
└─── main.c                       # main source code file
```

<div align="right">

[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>



# Functionalities

:meat_on_bone: **`Intuitive food management menu`**  
Access a user-friendly menu to seamlessly add food items. Input the food item's name and expiration date for efficient tracking.
<br><br>

:red_circle: **`Visual expiry indication`**  
View a list of food items on the menu. A red LED indicator will turn on if an item has expired, offering a clear visual cue.
<br><br>

:clock6: **`Timely expiry alerts`**  
Receive a notification one day before a food item is set to expire. Alerts are designed to keep you informed and prevent unnecessary waste.

<div align="right">
    
[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>



# Demonstration

#### :movie_camera: Video:  
[![ ](http://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](http://www.youtube.com/watch?v=YOUTUBE_VIDEO_ID_HERE "Video Title")
<br>

#### :paperclip: Presentation:  
[slides](...link)

<div align="right">
    
[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>



# Requirements

### **Hardware**

  :heavy_check_mark: MSP432-P401R microcontroller.  
  <pre style="margin-left: 20px;">
    <img src="/Images/MSP432.jpg" width="200" height="300">
  </pre>
  :heavy_check_mark: Booster board with a screen, analog inputs, and buttons.  
  <pre style="margin-left: 20px;">
    <img src="/Images/BoosterPack.jpeg" width="350" height="175">
  </pre>
  :heavy_check_mark: Red LED for visual indicators.  
  :heavy_check_mark: Real-time clock (RTC) module for time-based alerts.  
  :heavy_check_mark: Wireless Network Internet Controller (WNIC) module.  
<br>

### **Software**

  :heavy_check_mark: MSP432-P401R programming environment, IDE (e.g., Code Composer Studio).  
  :heavy_check_mark: Real-time clock (RTC) library for time tracking.  
  :heavy_check_mark: Internet connectivity library or API.  
  :heavy_check_mark: Online database service.  

<div align="right">
    
[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>



# Programming language

<a><img src="/Images/C-logo.jpg" width="60" height="60"></a>

<div align="right">
    
[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>



# Team members & contributions

- Gabriele Benetti  
- Giovanni Benetti  
- Julia Bernon  
- Lorenzo Negut  

<br>
Since we didn't have experience using this (or any other) board, we developted basically all the software logic and code in a collaborative way.

<div align="right">

[Return to Top](#iot-fridge-guardian-with-msp432-p401r)

</div>
