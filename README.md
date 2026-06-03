# 🎮 MSP430 TFT Arcade Game

An embedded real-time arcade game developed in C for the MSP430 microcontroller using a 128x128 TFT LCD display.

The project features a small interactive game where the player controls a moving rectangle using hardware buttons to collect targets, avoid traps, and increase score over time.

---

## 🚀 Features

- 🎯 Real-time rectangle movement (UP / DOWN / LEFT / RIGHT)
- 🟢 Collect green circles to increase score
- 🔴 Avoid red circles (instant GAME OVER)
- ⏱️ Timed red circle (disappears after 2 seconds if not collected)
- 📈 Dynamic difficulty (speed increases every 10 points)
- 📊 Score display on screen
- 🧠 Random object generation using pseudo-random algorithm
- 🖥️ 128x128 TFT LCD graphical interface

---

## 🎮 Controls

| Button | Function |
|--------|----------|
| P1.1   | Move Up |
| P2.1   | Move Down |
| P3.7   | Move Left |
| P4.0   | Move Right |

---

## 🧠 Game Rules

- The player controls a 10x10 rectangle.
- Green circles increase the score by 1.
- Red circles end the game if touched.
- Red circles disappear after 2 seconds if not collected.
- Every 10 points, the game speed increases.
- The game ends when a red circle is hit.

---

## ⚙️ Hardware

- MSP430 microcontroller
- 128x128 TFT LCD display
- 4 push buttons for control

---

## 💻 Software

- C language (embedded programming)
- Code Composer Studio (Eclipse-based IDE)
- Custom display library (`display.h`)
- MSP430 drivers and system configuration

---

## 📂 Project Structure

