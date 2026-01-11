#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "ollama_client.h"
#include "ui.h"

OllamaClient ollama;
ChatUI ui;
bool wifiConnected = false;
String currentModel = "rnj-1:latest";

String prompts[] = {
  "Hi, whats up?",
  "Write a short poem about artificial intelligence",
  "What is M5Stack and what can it do?",
  "How does Ollama work with local LLMs?"
};

void setup() {
  
  M5.begin();
  M5.Power.begin();
  
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n==================================");
  Serial.println("M5Stack AI Chat Client");
  Serial.println("==================================");
  
  ui.init();
  ui.showSplashScreen();
  
  connectToWiFi();
  
  if (wifiConnected) {
    checkOllamaConnection();
  }
  
  ui.setWifiStatus(wifiConnected);
 
  ui.showMainScreen();
}

void connectToWiFi() {
  ui.showMessage("Connecting to WiFi...", TFT_YELLOW);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
    
    if (attempts % 3 == 0) {
      ui.drawProgress(attempts * 3);
    }
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    ui.showMessage("WiFi Connected!", TFT_GREEN);
    Serial.println("\n✓ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
  } else {
    ui.showMessage("WiFi Failed!", TFT_RED);
    Serial.println("\n✗ WiFi Connection Failed!");
    delay(2000);
  }
}

void checkOllamaConnection() {
  ui.showMessage("Checking Ollama...", TFT_YELLOW);
  
  if (ollama.checkConnection()) {
    ui.showMessage("Ollama Ready!", TFT_GREEN);
    delay(1000);
  } else {
    ui.showMessage("Ollama Not Found!", TFT_RED);
    ui.showMessage("Check server address", TFT_YELLOW);
    delay(2000);
  }
}

void loop() {
  M5.update();
  
  if (M5.BtnA.wasPressed()) {
   
    Serial.println("Button A: New session");
    ui.showNewSessionScreen();
    delay(300);
    ui.showMainScreen();
  }
  
  if (M5.BtnB.wasPressed() && wifiConnected) {
    
    Serial.println("Button B: Send query");
    sendRandomQuery();
  }
  
  if (M5.BtnC.wasPressed()) {
  
    Serial.println("Button C: System info");
    showSystemInfo();
  }
  
  delay(50);
}

void sendRandomQuery() {
  
  static int lastPrompt = -1;
  int promptIndex;
  
  do {
    promptIndex = random(0, 4);
  } while (promptIndex == lastPrompt && sizeof(prompts) > 1);
  
  lastPrompt = promptIndex;
  String prompt = prompts[promptIndex];
  
  ui.showMessage("Thinking...", TFT_CYAN);
  
  Serial.println("Asking: " + prompt);
  String response = ollama.generateResponse(prompt, currentModel);
  
  if (response.length() > 0) {
    
    ui.showResponse(response);
    
    Serial.println("\n=== Response ===");
    Serial.println(response.substring(0, 150) + "...");
    Serial.println("=== End ===");
   
    waitForButtonA();
    
    ui.showMainScreen();
  } else {
    ui.showMessage("Error getting response", TFT_RED);
    delay(2000);
    ui.showMainScreen();
  }
}

void waitForButtonA() {
  M5.Lcd.fillRect(0, 180, 320, 60, TFT_BLACK);
  M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(80, 195);
  M5.Lcd.print("Press A to continue");
  
  while (true) {
    M5.update();
    if (M5.BtnA.wasPressed()) {
      break;
    }
    delay(50);
  }
}

void showSystemInfo() {
  ui.showSystemInfoScreen();
  
  String info = "";
  info += "WiFi: ";
  info += wifiConnected ? "Connected\n" : "Disconnected\n";
  
  if (wifiConnected) {
    info += "IP: ";
    info += WiFi.localIP().toString();
    info += "\n";
  }
  
  info += "Ollama: ";
  info += OLLAMA_SERVER;
  info += "\n";
  
  info += "Model: ";
  info += currentModel;
  info += "\n";
  
  info += "Free RAM: ";
  info += String(ESP.getFreeHeap() / 1024);
  info += " KB\n";
  
  info += "Chip ID: 0x";
  info += String(ESP.getEfuseMac(), HEX);
  info += "\n";
  
  info += "SDK: ";
  info += String(ESP.getSdkVersion());
  
  ui.displayText(info, TFT_WHITE, 1);
  
  M5.Lcd.fillRect(0, 180, 320, 60, TFT_BLACK);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(100, 195);
  M5.Lcd.print("Press any button to return");
  
  while (true) {
    M5.update();
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
      break;
    }
    delay(50);
  }
  
  ui.showMainScreen();
}
