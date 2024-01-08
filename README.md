# food expiration project
`Embedded software for the Internet of Things`

### *General todo:*
- *Set expiration date of food products.*
- *Receive alert notification on our phone using Google home API.*

---

### IDEAS
- **Notifications before food expiring** (**any kind of signal from MSP** or Google Home).
- **Food tracking**: what’s inside your fridge, we could use a file.
- Fridge temperature, temperature and a humidity sensor.

---

### USER INTERFACE
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

### REQUIREMENTS
- Bar scanner
- Camera (text recognition)
- Temperature sensor
- Humidity sensor
- **MSP (led, speaker)**
- **Booster board (screen, analogue, buttons)**
- Wireless Network Internet Controller (WNIC)

---

### *How do we store the data of the products?*  
Database:
- Online (we must buy a wireless adaptor for the MSP)
- Via serial connection (see lecture 13's slides of the course)
- Use an SD card (not very expensive)
