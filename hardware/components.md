# Hardware Components

| Component | Role |
|---|---|
| Arduino Nano | Main microcontroller |
| HC-05 Bluetooth module | Wireless manual control |
| L298N motor driver | Drives the two DC gear motors |
| N20 DC gear motors | Differential-drive motion |
| HC-SR04 ultrasonic sensor | Front obstacle detection |
| SG90 servo motor | Sweeps the ultrasonic sensor left/right |
| 16×2 I2C LCD | Displays mode, direction and distance |
| Battery pack | Portable power source |
| Chassis + wheels | Mechanical platform |

## Control flow

```text
Smartphone -> HC-05 -> Arduino Nano -> L298N -> Motors
                         |              |
                         |              +-> HC-SR04 + SG90
                         +-> I2C LCD
```
