# IoT Fridge Guardian with MSP432-P401R


## Table of contents
1. [About project](#about)
2. [Presentation](#presentation)
3. [Functionalities description](#functionalities-description)
4. [Requirements](#requirements)
5. [Build with](#programming-languages)


## About

<div align="center">
  <a> <img src="/Images/fridgeLogo.jpg" width="350" height="350"> </a>
</div>

Welcome to ***IoT Fridge Guardian***, an embedded software solution designed for Internet of Things (IoT)-enabled refrigerators.  
This project aims to enhance your food storage experience by providing real-time monitoring and expiry reminders & alerts with intuitive controls for your smart fridge.


## Functionalities description

description


## Presentation

- Youtube: [video](...link)
- Presentation: [slides](...link)


## Requirements

### Hardare

...

### Software

...


## Programming language(s)

C, ...


---
`Embedded software for the Internet of Things`

## *General todo:*
- *Set expiration date of food products.*
- *Receive alert notification on our phone using Google home API.*

---

## IDEAS
- **Notifications before food expiring** (**any kind of signal from MSP** or Google Home).
- **Food tracking**: what’s inside your fridge, we could use a file.
- Fridge temperature, temperature and a humidity sensor.

---

## USER INTERFACE
- **We could add the food by hand**:
    + From terminal (remote).
    + From the screen and controller.
- We could add food by scanning the products:
    + Like "Juka" (app) using the barcodes.
    + Text recognition for expiration date.
- Temperature management:
    + On screen controls.
    + Bluetooth (concept).

---

## REQUIREMENTS
- Bar scanner
- Camera (text recognition)
- Temperature sensor
- Humidity sensor
- **MSP (led, speaker)**
- **Booster board (screen, analogue, buttons)**
- Wireless Network Internet Controller (WNIC)

---

## *How do we store the data of the products?*  
Database:
- Online (we must buy a wireless adaptor for the MSP)
- Via serial connection (see lecture 13's slides of the course)
- Use an SD card (not very expensive)
