# Fridge Guardian with MSP432-P401R

<details>
<summary><b>Table of contents</b></summary>

1. [About](#about)
2. [Demonstration](#demonstration)
3. [Requirements](#requirements)
4. [Project layout](#project-code-structure)
5. [Programming language](#programming-language)
6. [How to build and run](#how-to-build-and-run)
7. [User guide](#user-guide)
8. [Team members & contributions](#team-members)

</details>
<br>



# About

Welcome to **`IoT Fridge Guardian`**, an embedded software solution designed for Internet of Things (IoT)-enabled refrigerators.  
This project aims to enhance your food storage experience by providing real-time monitoring with intuitive controls for your smart fridge.
Stay in control of your fridge, minimize waste, and ensure your food stays fresh effortlessly.

<div align="center">
  <a> <img src="/Images/fridgeLogo.jpg" width="300" height="300"> </a>
</div>

<div align="right">

[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# Demonstration

#### :movie_camera: Video:

<a href="http://www.youtube.com/watch?v=1fKpxXr2Xhc">
    <img src="https://img.youtube.com/vi/1fKpxXr2Xhc/0.jpg" alt="Image" width="150" height="90">
</a>
<br>

#### :paperclip: Presentation:  
[slides](https://docs.google.com/presentation/d/1rZ9iQfn5k4NT6AfTBC7GB6xYHdCAeOiXRgEEJqAVlfA/edit?usp=sharing)
<br>

<div align="right">
    
[Go to top](#fridge-guardian-with-msp432-p401r)

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

<br>

### Hardware components

  :heavy_check_mark: Red LED for visual indicators.  
  :heavy_check_mark: Real-time clock (RTC) module.  
  :heavy_check_mark: Analog to Digital Converter (ADC14).  
  :heavy_check_mark: Buttons.  
  :heavy_check_mark: Display.  
  :heavy_check_mark: Joystick.  

<br>

### **Software**

  :heavy_check_mark: MSP432-P401R programming environment, IDE (e.g., [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO)).  
  :heavy_check_mark: Software development kit for MSP432: [SimpleLink-SDK](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)  

<div align="right">
    
[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# Project code structure

```bash
MSP432-Fridge-Guardian
├───Debug                     # compiled files
├───Drivers
│   └───Lcd                   # LCD screen related files
├───Logic
│   ├───Graphics              # files to manage views
│   └───Interrupts            # interrupts handlers
├───targetConfigs             # target configuration
├───Images
├─── README.md                # project overview file
└─── main.c                   # main source code file
```

<div align="right">

[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# Programming language

<a><img src="/Images/C-logo.jpg" width="60" height="60"></a>

<div align="right">
    
[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# How to build and run

1. Open the project in Code Composer Studio.
2. Go to: *Project → Properties → Build → Arm Compiler → Include Options* and add the *source directory* located in *simplelink_msp432p4_sdk_3_40_01_02/*
3. Go to: *Project → Properties → Build → Arm Linker → File Search Path* and add:
   + *msp432p4xx_dreivelib.lib* directory located in *[..]/source/ti/devices/msp432p4xx/driverlib/ccs/*
   + *grlib.a* located in *[..]/source/ti/grlib/lib/ccs/m4f/*
6. Build and run the project. The Launchpad should now be displaying the graphics.

You can find more examples inside the ***SimpleLink-SDK*** folder.
<br>

<div align="right">
    
[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# User guide

### Functionalities description

:meat_on_bone: **`Intuitive food management menu`**  
Access a user-friendly menu to seamlessly add food items. Input the food item's name, quantity and expiration date for efficient tracking.
<br><br>

:red_circle: **`Visual expiry indication`**  
View a list of food items on the menu. A red LED indicator will turn on if an item has expired and it will be highlighted in red in the food list view, offering a clear visual cue.
<br>

<div align="right">
    
[Go to top](#fridge-guardian-with-msp432-p401r)

</div>



# Team members

- Gabriele Benetti  
- Giovanni Benetti  
- Julia Bernon  
- Lorenzo Negut  

*Since we didn't have experience using this (or any other) board, we developted basically all the software logic and code in a collaborative way.*  

<div align="right">

[Go to top](#fridge-guardian-with-msp432-p401r)

</div>
