# Working Principle

DriveX 1.0 is a two-mode Arduino-based robotic car.

## Bluetooth Mode

The smartphone sends single-character commands through HC-05:

| Command | Action |
|---|---|
| `F` | Forward |
| `B` | Backward |
| `L` | Left |
| `R` | Right |
| `S` | Stop |
| `X` | Enter obstacle mode |

## Obstacle Avoidance Mode

The HC-SR04 measures the distance ahead. The sensor is mounted on an SG90 servo so the controller can scan both sides when an obstacle is encountered.

The actual firmware uses a **10 cm decision threshold**: `distance > 10` commands forward motion; otherwise it reverses briefly, scans left/right and turns toward the side with the larger measured distance. The NewPing object is configured with a maximum distance of 200 cm.

The character `x` returns to Bluetooth mode.

## System architecture

```text
Smartphone
    |
 Bluetooth
    v
  HC-05
    |
    v
Arduino Nano ----> I2C LCD
    |
    +----> L298N ----> DC Motors
    |
    +----> HC-SR04 <---- SG90 servo
```
