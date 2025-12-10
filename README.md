## 🚗 Driver Drowsiness and Accident Alert System

## 🧠 Project Overview

The Driver Drowsiness and Accident Alert System is an intelligent safety project that combines Computer Vision (CV) and IoT-based hardware to detect driver fatigue and prevent road accidents. Using a shape predictor model powered by OpenCV and Dlib, the system continuously monitors the driver’s eyes and facial landmarks in real time to identify signs of drowsiness such as prolonged eye closure or head tilt.

Once drowsiness is detected, the system immediately triggers audio and vibration alerts to wake the driver. Additionally, through the integration of GSM and GPS modules, it can send an SMS alert containing the driver’s location to emergency contacts if the driver fails to respond or if an accident occurs. This project provides a low-cost yet efficient solution for improving road safety through a blend of AI-driven vision detection and embedded hardware control.

⚙️ Features

AI-Based Drowsiness Detection: Uses OpenCV and Dlib’s shape predictor model to analyze facial landmarks in real time.

Instant Driver Alerts: Buzzer and vibration motor activate immediately when drowsiness is detected.

Accident Detection & Alert: Sends automatic SMS with live GPS location through the GSM module.

Real-Time Monitoring: Continuously processes facial data for accuracy and quick response.

Cost-Effective & Scalable: Combines affordable components with efficient AI processing.

🧩 Hardware Components

Arduino Nano

Eye Blink / IR Sensor

GPS Module

GSM Module

Buzzer Module

Vibration Motor

Power Supply (Battery)

💻 Software Components

Programming Language: Python & Embedded C

Libraries Used:

OpenCV – for image processing

Dlib – for facial landmark detection

NumPy – for numerical operations

imutils – for frame handling

Tools: Arduino IDE, Visual Studio Code

## 🧠 Working Principle

The camera captures live video of the driver’s face.

Using the Dlib shape predictor model, the system tracks the eye aspect ratio (EAR) and head movement to determine alertness.

If the EAR drops below a threshold (indicating closed eyes), the system recognizes the driver as drowsy.

The buzzer and vibration motor are activated to alert the driver.

If no movement or response is detected after several alerts, the GSM module sends an emergency SMS with the GPS location to predefined contacts.

---

## 📈 Applications

Personal and commercial vehicle safety systems.

Transportation and logistics fleet monitoring.

Smart car integration systems.

---

## 💡 Future Enhancements

Integration with deep learning models for improved accuracy.

Use of Raspberry Pi for faster on-device processing.

Integration with cloud dashboards to analyze driver behavior over time.

Voice alerts and auto-brake systems for critical fatigue detection.

---

## 🧰 Tech Stack
| Category      | Technologies                          |
| ------------- | ------------------------------------- |
| Programming   | Python, Embedded C                    |
| AI / ML       | OpenCV, Dlib (shape predictor)        |
| Hardware      | Arduino Nano, GSM, GPS, IR Sensor     |
| Tools         | Arduino IDE, VS Code                  |
| Communication | Serial Communication, GSM SMS Service |

---

## 👨‍💻 Contributors

Developed by: Aryan Ambre

---

## 📝 License

This project is open-source and available under the MIT License.
