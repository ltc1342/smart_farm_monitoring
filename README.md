# PROJECT: Smart Farm Monitoring

- Programming Software:
  |----STM32CubeIDE for STM32
  |----PlatformIO on Visual Studio Code for ESP32

- Hardware:
  |----STM32F411CEU6 (Black Pill) --> Main Microcontroller (Task processing)
  |----ESP32 WROOM DevKit (Xtensa) --> Sub-microcontroller (Connect Wifi send data to MQTT)

- Peripherals for STM32
  |----Oled Screen (SH1106) communication I2C
  |----Temperature and humidity sensor (DHT11) communication OneWire
  |----Light sensor (GY-302 BH1750) communication I2C
  |----Soil moisture sensor (SMS-V1 LM393) communication ADC
  |----ESP32 WROOM DevKit communication UART
  |----Module 2 5V Low Level Triggered Relays communication GPIO (Output)
