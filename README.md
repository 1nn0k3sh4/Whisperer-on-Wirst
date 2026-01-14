# Whisperer on the Wrist 🤖💬

Your private AI companion that lives on your wrist.  
No cloud? No problem. A complete local AI assistant with emotional intelligence, now available for **M5StickC Plus2** and **M5 Core** devices.

![Demonstration](demo1.gif)


## ✨ Why WoW?

- 🔒 **Truly Private** – Your conversations never leave your devices.
- 🎭 **Emotionally Aware** – AI with feelings displayed through expressive animations.
- ⚡ **Instant Response** – No latency, works without public AI services.
- 📱 **Multi-Device Support** – Compatible with M5StickC Plus2 and M5 Core.
- 🎮 **Hackable & Open** – Fully open-source, customizable, and extensible.

---

## 🧭 Our Development Journey

Finding the right foundation took exploration. We tested several pre-built OS/firmware options for the M5StickC (**Bruce OS, M5Launcher, CatHack, NEMO, CircuitPython**) but found their ecosystems restrictive for deep customization. Our breakthrough came with **PlatformIO**, which provided the perfect balance of powerful library management and low-level control needed to bring the "emotionally aware" vision to life.

**Milestone Achieved:** We now have stable, compiled firmware for both **M5StickC Plus2** and **M5 Core** that displays dynamic, sensor-reactive eye animations—the core of our assistant's personality. The hardware foundation is ready.

---

## 🚀 Current Phase & Quick Start

We are now building the **AI Bridge**. The goal is to connect the animated M5 device to a local LLM (via Ollama) over WiFi.

### 📱 Supported Devices
- **M5StickC Plus2** – Compact, wearable form factor with built-in microphone
- **M5 Core** – Larger display and more GPIO for expanded functionality

### Prerequisites
1.  **M5 Device** (StickC Plus2 or Core) with the latest custom firmware.
2.  A **computer** on the same local WiFi network.
3.  **Ollama** installed and running on your computer with at least one model (e.g., `llama3.2`, `mistral`).

### Setup
1.  **Prepare Your M5 Device:**
    *   Set up PlatformIO in VSCode.
    *   Clone this repository.
    *   Select the appropriate environment in PlatformIO:
        - `m5stickc-plus2` for M5StickC Plus2
        - `m5stack-core` for M5 Core
    *   Connect your device and run `pio run --target upload`.

2.  **Prepare Your AI Server:**
    *   Install [Ollama](https://ollama.com/) on your computer.
    *   Pull a model: `ollama pull llama3.2`
    *   Ensure Ollama's API is running (default: `http://IP:11434`, configure with `Environment="OLLAMA_HOST=0.0.0.0:11434"`).

3.  **Configure the Connection:**
    *   In the project's `src/secrets.h` file (create from `secrets.example.h`), enter your WiFi SSID, password, and your computer's local IP address.

4.  **Experience Local AI:** The firmware now supports basic text interaction with your local LLM!

---

## 🧩 Project Architecture

```
[M5 Device] <--WiFi--> [Local Computer / Home Server]
       |                            |
(Display & Sensors)          (Ollama + LLM)
       |                            |
[Emotional UI]           [AI Processing & Response]
       |                            |
[Voice Input*] <-------> [Text/JSON API Communication]
```
**\*Voice input is currently in development for M5StickC Plus2.*

---

## 🔧 For Developers

The project is structured for clarity and growth:

*   `/firmware` – PlatformIO project with separate environments for each device
*   `/firmware/src` – Shared core logic with device-specific adaptations
*   `/docs` – Setup guides, hardware references, and API documentation
*   `/prototypes` – Experimental code and previous iterations

### Building for Different Devices
1.  Open the PlatformIO project in VSCode
2.  Select the target device from the environment selector:
    - `m5stickc-plus2` – For M5StickC Plus2
    - `m5stack-core` – For M5 Core
3.  Build and upload as usual

### Key Implementation Differences
- **M5StickC Plus2**: Uses M5Unified library, smaller display (135x240), built-in microphone for future voice features
- **M5 Core**: Uses M5Stack library, larger display (320x240), more GPIO pins for expansion

---

## 📋 Roadmap

*   **✅ Phase 1: Foundation** – Stable development environment for M5StickC Plus2
*   **✅ Phase 2: Emotional Core** – Animated personality display on both devices
*   **✅ Phase 3: Multi-Device Support** – M5 Core compatibility added
*   **✅ Phase 4: AI Bridge** – WiFi connectivity and text-based Ollama interface
*   **🔵 Phase 5: Voice Interface** – Voice-to-text for M5StickC Plus2 **(IN PROGRESS)**
*   **⚪ Phase 6: Advanced Features** – Sensor integration, expanded emotions, plugin system
*   **⚪ Phase 7: Polishing** – Refined UI/UX, power optimization, documentation

---

## 🙏 Acknowledgments

*   **M5Stack** for the versatile hardware ecosystem
*   The **PlatformIO** team for an indispensable development environment
*   The **Ollama** team for making local LLMs accessible
*   The open-source community whose libraries and guides made this project possible

---

*Whisperer on the Wrist is an open-source passion project. It's a testament to the idea that private, personal, and expressive AI should be within everyone's reach—whether on your wrist or on your desk.*
