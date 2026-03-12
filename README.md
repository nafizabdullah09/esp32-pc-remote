# ESP32 PC Remote (Wake-on-LAN via Blynk)

A highly reliable Internet of Things (IoT) project that allows you to turn on your desktop PC from anywhere in the world using your smartphone. 

This project uses an ESP32 microcontroller as a network bridge. It listens for a command from the Blynk IoT app and broadcasts a "Magic Packet" (Wake-on-LAN) to your PC over your local network. 

## ✨ Features
* **Global Access:** Wake your PC over the internet without exposing your home network to security risks (no router port-forwarding required).
* **24/7 Stability:** Features a built-in 24-hour scheduled memory wipe and reboot (`ESP.restart()`) to prevent memory leaks and ensure the ESP32 never freezes while you are away.
* **Low Power:** Uses minimal electricity (~100mA) and runs perfectly off a standard 5V phone charger.

## 🛠️ Hardware Requirements
* **ESP32 Development Board** * **Reliable 5V USB Power Supply** (A name-brand phone charger is recommended for 24/7 safety).
* **Desktop PC** connected to your router via an **Ethernet cable** (Wake-on-LAN over Wi-Fi is generally unsupported/unreliable).

## 💻 Software Prerequisites
1. **Arduino IDE** installed on your computer.
2. In the Arduino IDE, go to **Sketch > Include Library > Manage Libraries** and install the **`Blynk`** library (by Volodymyr Shymanskyy).

## 🚀 Setup Guide

### Step 1: Prepare Your PC
For the ESP32 to successfully wake your computer, your motherboard must support Wake-on-LAN.
1. Boot into your PC's **BIOS/UEFI** and enable Wake-on-LAN (Often called "Resume by PCI-E Device" or "Power On By MAC"). Disable "ErP Ready" if your BIOS has it.
2. In **Windows**, open the **Control Panel > Power Options** and turn **OFF** "Fast Startup".
3. Open **Device Manager**, find your Ethernet Network Adapter, open its Properties, and go to the **Power Management** tab. Check the box that says "Allow a magic packet to wake the computer."
4. Open Command Prompt, type `ipconfig /all`, and write down your PC's **Physical Address (MAC Address)**.

### Step 2: Configure the Blynk Web Dashboard
1. Go to [blynk.cloud](https://blynk.cloud/) and create a free account.
2. Go to **Templates > New Template**. Name it "PC Remote" and set the hardware to ESP32.
3. In your template, go to the **Datastreams** tab and create a **New Virtual Pin**:
   * Name: Power Button
   * Pin: **V0**
   * Data Type: Integer
   * Min: 0 | Max: 1
4. Go to the Search icon, click **New Device > From Template**, and select your new template.
5. Copy the block of code containing your `Template ID`, `Template Name`, and `Auth Token`. 

### Step 3: Flash the ESP32
1. Open the `.ino` file in the Arduino IDE.
2. Paste your specific **Blynk credentials** at the very top of the code.
3. Enter your home **Wi-Fi SSID and Password**.
4. **Important:** Enter your PC's MAC address in the `mac[]` array. You must replace the colons/dashes with `0x`. 
   * *Example: `D8:43:AE` becomes `{ 0xD8, 0x43, 0xAE... }`*
5. Connect your ESP32, select the correct COM port, and click **Upload**.

### Step 4: The Mobile App
1. Download the **Blynk IoT** app on your iOS or Android device and log in.
2. Open your new "PC Remote" device.
3. Add a **Button Widget** to the dashboard.
4. Configure the button to use **Datastream V0** and set its Mode to **Push**.

## 🎮 Usage
Leave the ESP32 plugged into power near your router. When you want to turn on your PC, open the Blynk app and tap the button. 

**Note on Shutting Down:** This project only *wakes* the PC. To turn the PC off remotely, log into your computer using a remote desktop application (like Chrome Remote Desktop or AnyDesk) and use the standard Windows shutdown menu to prevent data corruption.
