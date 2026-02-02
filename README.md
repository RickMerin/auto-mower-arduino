# 🤖 Arduino Obstacle Avoidance Robot (Servo-Based Scan)

An autonomous obstacle-avoidance robot built with Arduino, DC motors, an ultrasonic sensor, and a servo-mounted scanner.

The robot **moves forward normally**, **stops only when necessary**, and performs a **single left/right scan using a servo-mounted ultrasonic sensor** to decide the safest direction before continuing.

This project focuses on **clean logic**, **predictable behavior**, and **real-world hardware constraints**.

---

## ✨ Features

* 🚗 Forward movement with speed control
* 🛑 Automatic stop when obstacle is detected
* 🔍 **Single scan only when stopped** (no constant servo movement)
* 🧭 Intelligent left/right decision based on free space
* 🔁 Avoids repeated scanning while stationary
* ⚡ Power-safe logic (servo isolated from motors)
* 🧠 Deterministic, easy-to-debug control flow

---

## 🧠 How the Logic Works (High Level)

1. Robot continuously measures **front distance**
2. If the path is clear → move forward
3. If an obstacle is close:

   * Stop motors
   * **Scan left once**
   * **Scan right once**
   * Decide direction
   * Turn or reverse
4. Resume movement
5. **No scanning while moving**
6. **No repeated scanning while stopped**

This mirrors how real autonomous robots handle obstacle avoidance.

---

## 🧩 Hardware Components

<img width="1694" height="1317" alt="image" src="https://github.com/user-attachments/assets/b3aef7ae-d4d0-4135-9700-cd8da2adc6b4" />
<img width="2739" height="747" alt="image" src="https://github.com/user-attachments/assets/2030885f-ca66-4d58-80fc-0e6d8e627f5e" />


| Component                          | Quantity  |
| ---------------------------------- | --------- |
| Arduino Uno / Nano                 | 1         |
| DC Motors + Wheels                 | 2         |
| Motor Driver (L293D / L298N)       | 1         |
| HC-SR04 Ultrasonic Sensor          | 1         |
| SG90 / MG90 Servo Motor            | 1         |
| External 5–6V Power Supply (servo) | 1         |
| Battery Pack (motors)              | 1         |
| Jumper Wires                       | As needed |
| Chassis                            | 1         |

---

## 🔌 Wiring Overview

### 🔹 Motor Driver → Arduino

| Signal | Arduino Pin |
| ------ | ----------- |
| ENA    | 5           |
| IN1    | 2           |
| IN2    | 3           |
| ENB    | 6           |
| IN3    | 4           |
| IN4    | 7           |

---

### 🔹 Ultrasonic Sensor (HC-SR04)

| Sensor Pin | Arduino Pin |
| ---------- | ----------- |
| TRIG       | 9           |
| ECHO       | 10          |

---

### 🔹 Servo Motor

| Servo Wire             | Connection              |
| ---------------------- | ----------------------- |
| Signal (Yellow/Orange) | Pin 11                  |
| VCC (Red)              | **External 5–6V ONLY**  |
| GND (Brown/Black)      | Common GND with Arduino |

⚠️ **Important:**
Do **NOT** power the servo from the Arduino 5V pin.
Use an external supply and **share ground**.

---

## ⚙️ Software Setup

### 1️⃣ Install Arduino IDE

Download from:
[https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

---

### 2️⃣ Install Required Library

The project uses the built-in Arduino Servo library:

```cpp
#include <Servo.h>
```

(No extra installation needed.)

---

### 3️⃣ Clone the Repository

```bash
git clone https://github.com/your-username/arduino-obstacle-avoidance-servo.git
cd arduino-obstacle-avoidance-servo
```

---

### 4️⃣ Upload the Code

1. Open the `.ino` file in Arduino IDE
2. Select:

   * **Board** → Arduino Uno (or your board)
   * **Port** → correct COM port
3. Click **Upload**

---

## ▶️ How to Use

1. Power the Arduino
2. Power motors and servo (external supply)
3. Place robot on the floor
4. Robot will:

   * Move forward
   * Slow near obstacles
   * Stop, scan, decide, and turn
   * Continue moving

---

## 🧪 Expected Behavior

| Situation          | Robot Action        |
| ------------------ | ------------------- |
| Path clear         | Move forward fast   |
| Object approaching | Slow down           |
| Object too close   | Stop + scan         |
| Left clear         | Turn left           |
| Right clear        | Turn right          |
| Both blocked       | Reverse             |
| Still stopped      | ❌ No repeated scans |

---

## 🧠 Design Decisions (Why This Works)

* **Servo scans only when stopped** → stable readings
* **Single scan per stop** → no jitter, no oscillation
* **Flag-based logic** → prevents re-entry bugs
* **Simple thresholds** → predictable tuning

This is intentionally **not** a constantly scanning robot.

---

## ⚠️ Known Limitations

* Uses blocking `delay()` (good for learning, not optimal)
* No memory of previous turns
* No diagonal scanning
* No PID steering

These are deliberate trade-offs for clarity and stability.

---

## 🚀 Possible Improvements

* Convert to **non-blocking finite-state machine**
* Add turn memory to avoid left/right oscillation
* Smooth arc turns instead of tank turns
* 3-point scan (left / center / right)
* Speed ramping with acceleration

---

## 📄 License

MIT License
Free to use, modify, and learn from.

---

## 🤝 Contributions

Pull requests are welcome.
Keep changes **clean, documented, and modular**.

---

## 🧠 Final Note

This project prioritizes **correct behavior over fancy tricks**.
If you understand *why* this works, you’re already ahead of most Arduino builds.

Happy hacking 🤖💡
