# DriveX 1.0 Pinout

This table reflects the uploaded DriveX 1.0 firmware.

| Arduino Nano | Device | Function |
|---|---|---|
| D0 (RX) | HC-05 TX | Bluetooth serial input |
| D1 (TX) | HC-05 RX | Bluetooth serial output |
| D2 | HC-SR04 ECHO | Distance measurement |
| D3 | HC-SR04 TRIG | Ultrasonic trigger |
| D5 | SG90 signal | Sensor scanning |
| D6 | L298N ENA | Left motor PWM |
| D7 | L298N IN1 | Left motor direction |
| D8 | L298N IN2 | Left motor direction |
| D9 | L298N IN3 | Right motor direction |
| D10 | L298N IN4 | Right motor direction |
| D11 | L298N ENB | Right motor PWM |
| A4 (SDA) | I2C LCD SDA | LCD data |
| A5 (SCL) | I2C LCD SCL | LCD clock |

LCD address in firmware: `0x27`.

> **Known v1.0 limitation:** the firmware assigns `SoftwareSerial BT(0, 1)` while also using `Serial` on the Nano's D0/D1 hardware UART. This can cause serial/debug conflicts. A future revision should move Bluetooth to other digital pins.
