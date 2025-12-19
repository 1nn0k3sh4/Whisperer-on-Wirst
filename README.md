# Whisperer on the Wirst 🤖💬

Your private AI companion that lives on your wrist.
No Public? No problem. Complete local AI assistant with emotional intelligence.

## ✨ Why WoW?
- 🔒 Truly Private - Your conversations never leave your devices.
- 🎭 Emotionally Aware - AI with feelings displayed through animations.
- ⚡ Instant Response - No latency, works without public AI agent, only youre locally AI - assistent.
- 🎮 Hackable - Open-source, customizable, extensible

Отличное видение проекта! Вот обновлённый `README.md`, который отражает пройденный путь и текущее направление разработки:

## 🧭 Our Development Journey

Finding the right foundation took exploration. We tested several pre-built OS/firmware options for the M5StickC (**Bruce OS, M5Launcher, CatHack, NEMO, CircuitPython**) but found their ecosystems restrictive for deep customization. Our breakthrough came with **PlatformIO**, which provided the perfect balance of powerful library management and low-level control needed to bring the "emotionally aware" vision to life.

**Milestone Achieved:** We now have a stable, compiled firmware for the M5StickC Plus2 that displays dynamic, sensor-reactive eye animations—the core of our assistant's personality. The hardware foundation is ready.

## 🚀 Current Phase & Quick Start

We are now building the **AI Bridge**. The goal is to connect the animated M5StickC to a local LLM (via Ollama) over WiFi.

### Prerequisites
1.  **M5StickC Plus2** with the latest custom firmware (see setup below).
2.  A **computer** on the same local WiFi network.
3.  **Ollama** installed and running on your computer with at least one model (e.g., `llama3.2`, `mistral`).

### Setup
1.  **Prepare Your M5StickC:**
    *   Set up PlatformIO in VSCode.
    *   Clone this repository.
    *   Open the project, connect your device, and run `pio run --target upload`. This installs the core animation firmware.

2.  **Prepare Your AI Server:**
    *   Install [Ollama](https://ollama.com/) on your computer.
    *   Pull a model: `ollama pull llama3.2`
    *   Ensure Ollama's API is running (default: `http://IP:11434, not localhost (sudo systemctl edit ollama: Environment="OLLAMA_HOST=0.0.0.0:11434"`).

3.  **Configure the Connection:**
    *   In the project's `src/secrets.h` file (create from `secrets.example.h`), enter your WiFi SSID, password, and your computer's local IP address.

4.  **Experience Local AI:** The next stage of firmware (in development) will allow you to interact!

## 🧩 Project Architecture (In Progress)

```
[M5StickC Plus2] <--WiFi--> [Local Computer / Home Server]
       |                            |
(Display & Sensors)          (Ollama + LLM)
       |                            |
[Emotional UI]           [AI Processing & Response]
       |                            |
[Voice Input*] <-------> [Text/JSON API Communication]
```
**\*Voice input is a planned future feature.*

## 🔧 For Developers

The project is structured for clarity and growth:
*   `/firmware` - The PlatformIO project for the M5StickC.
*   `/docs` - Setup guides, hardware references, and API documentation.
*   `/prototypes` - Experimental code and previous iterations (e.g., Arduino IDE sketches).

### Building & Contributing
1.  Familiarize yourself with PlatformIO and the M5Unified library.
2.  The core emotional engine is in `src/main.cpp`. Start here to understand the animation logic.
3.  The WiFi/Ollama client integration is the current focus in the `feature/ai-bridge` branch.

## 📋 Roadmap

*   **✅ Phase 1: Foundation** - Establish a stable, compiled development environment with basic graphics. **(COMPLETE)**
*   **🟡 Phase 2: Emotional Core** - Implement the animated, sensor-reactive personality display. **(COMPLETE)**
*   **🔵 Phase 3: AI Bridge** - Develop WiFi connectivity and a simple text-based interface with the local Ollama instance. **(COMPLETE)**
*   **⚪ Phase 4: Voice Interface** - Integrate voice-to-text and text-to-speech for natural interaction.**(IN PROGRESS)**
*   **⚪ Phase 5: Polishing & Expansion** - Refine UI/UX, add more emotions/animations, and explore multimodal inputs.

## 🙏 Acknowledgments

*   **M5Stack** for the versatile M5StickC Plus2 hardware.
*   The **PlatformIO** team for an indispensable development environment.
*   The **Ollama** team for making local LLMs accessible.
*   The open-source community whose libraries and guides made this project possible.

---

*Whisperer on the Wrist is an open-source passion project. It's a testament to the idea that private, personal, and expressive AI should be within everyone's reach.*
