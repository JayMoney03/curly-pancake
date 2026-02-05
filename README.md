# 🛡️ AEGIS HORIZON - Identity Chip System

A cyberpunk-themed ESP32 project featuring a WiFi hotspot with web interface and I2C device detection.

## 📋 Features

- **AEGIS Web Server**: Creates a WiFi hotspot with a terminal-style status page
  - Displays ESP32 chip ID
  - Shows system uptime
  - Cyberpunk green terminal aesthetic
  - Accessible via mDNS at `http://aegis.local`

- **I2C Scanner**: Detects and identifies I2C devices on the bus
  - Scans addresses 0x01 to 0x7E
  - Automatically identifies common devices
  - Helpful for hardware debugging

## 🔧 Hardware Requirements

- ESP32 Development Board
- Optional: I2C devices (OLED displays, sensors, etc.)

## 📦 Installation

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
2. Install ESP32 board support
3. Clone this repository
4. Open the desired sketch from the `examples/` folder
5. Upload to your ESP32

## 🚀 Usage

### AEGIS Web Server
1. Upload `examples/aegis_webserver/aegis_webserver.ino`
2. Open Serial Monitor (115200 baud)
3. Connect to WiFi network "AEGIS_IDENTITY" (password: "security_handshake")
4. Navigate to `http://aegis.local` or the IP shown in Serial Monitor

### I2C Scanner
1. Connect I2C devices to GPIO 21 (SDA) and GPIO 22 (SCL)
2. Upload `examples/i2c_scanner/i2c_scanner.ino`
3. Open Serial Monitor (115200 baud)
4. View detected devices and their addresses

## 📝 Configuration

### Change WiFi Credentials
Edit in `aegis_webserver.ino`:
```cpp
const char* ssid = "YOUR_HOTSPOT_NAME";
const char* password = "YOUR_PASSWORD";
```

### Change I2C Pins
Edit in `i2c_scanner.ino`:
```cpp
Wire.begin(SDA_PIN, SCL_PIN);
```

## 🎨 Customization

The web interface can be customized by editing the `getHTML()` function in the web server sketch.

## 📄 License

Open source - feel free to modify and use for your projects!

## 🤝 Contributing

Pull requests are welcome! Feel free to improve the code or add new features.