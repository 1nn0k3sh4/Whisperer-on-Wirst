#ifndef UI_H
#define UI_H

#include <M5Unified.h>
#include "config.h"

class ChatUI {
private:
  int currentLine = 0;
  
  void clearScreen(uint16_t color = TFT_BLACK) {
    M5.Lcd.fillScreen(color);
    currentLine = 0;
  }
  
  int minInt(int a, int b) {
    return (a < b) ? a : b;
  }
  
  int minInt(int a, unsigned int b) {
    return (a < (int)b) ? a : (int)b;
  } 
  
public:
  void init() {
    M5.Lcd.setTextSize(TEXT_SIZE);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setRotation(1);
  }
  
  void showSplashScreen() {
    clearScreen(TFT_BLACK);
    
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(80, 50);
    M5.Lcd.print("WoW AI");
    
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    M5.Lcd.setCursor(100, 120);
    M5.Lcd.print("M5Stack Client");
    
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    M5.Lcd.setCursor(120, 180);
    M5.Lcd.print("Powered by Ollama");
    
    delay(2000);
  }
  
  void showMainScreen() {
    clearScreen(TFT_BLACK);
    
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLACK);
    M5.Lcd.setTextColor(TFT_RED, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(100, 5);
    M5.Lcd.print("WoW AI Agent");
    
    M5.Lcd.fillCircle(310, 15, 8, wifiConnected ? TFT_GREEN : TFT_RED);
    
    M5.Lcd.drawRect(5, 35, 310, 140, TFT_BLACK);
    
   
    drawButtonPanel();
    
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.println("Welcome to WoW AI Chat Client");
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.println("Press B to start chatting");
    M5.Lcd.setCursor(10, 80);
    M5.Lcd.println("A: New session  C: System info");
  }
  
  void drawButtonPanel() {
   
    M5.Lcd.fillRect(0, 180, 320, 60, TFT_BLACK);
    
    M5.Lcd.drawFastVLine(106, 180, 60, TFT_WHITE);
    M5.Lcd.drawFastVLine(213, 180, 60, TFT_WHITE);
    
    M5.Lcd.fillCircle(53, 210, 25, TFT_BLUE);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLUE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(45, 205);
    M5.Lcd.print("NEW");
    
    M5.Lcd.fillCircle(160, 210, 25, TFT_GREEN);
    M5.Lcd.setTextColor(TFT_BLACK, TFT_GREEN);
    M5.Lcd.setCursor(152, 205);
    M5.Lcd.print("CHAT");
    
    M5.Lcd.fillCircle(267, 210, 25, TFT_YELLOW);
    M5.Lcd.setTextColor(TFT_BLACK, TFT_YELLOW);
    M5.Lcd.setCursor(259, 205);
    M5.Lcd.print("INFO");
    
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setCursor(35, 235);
    M5.Lcd.setCursor(140, 235);
    M5.Lcd.setCursor(250, 235);
  }
  
  void showPromptSelectionScreen() {
    clearScreen(TFT_BLACK);
    
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(80, 10);
    M5.Lcd.print("Select Prompt");
    
    M5.Lcd.drawLine(0, 40, 320, 40, TFT_WHITE);
  }
  
  void showPromptSelection(String prompts[], int selected) {
    M5.Lcd.fillRect(0, 45, 320, 130, TFT_BLACK);
    
    M5.Lcd.setTextSize(1);
    for (int i = 0; i < 4; i++) {
      int yPos = 60 + i * 30;  
      
      if (i == selected) {
        M5.Lcd.fillRect(10, yPos - 5, 300, 25, TFT_CYAN);
        M5.Lcd.setTextColor(TFT_BLACK, TFT_CYAN);
      } else {
        M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
      }
      
      
      String displayText = prompts[i];
      if (displayText.length() > 35) {
        displayText = displayText.substring(0, 35) + "...";
      }
      
      M5.Lcd.setCursor(20, yPos);
      M5.Lcd.println(displayText);
    }
    
    M5.Lcd.fillRect(0, 180, 320, 60, TFT_BLACK);
    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    M5.Lcd.setCursor(50, 190);
    M5.Lcd.print("A: Up  B: Select  C: Cancel");
  }
  
  void showResponse(String response) {
    clearScreen(TFT_BLACK);
   
    M5.Lcd.fillRect(0, 0, 320, 25, TFT_DARKGREEN);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_DARKGREEN);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(100, 3);
    M5.Lcd.print("WoW AI Response");
    
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(1);
    
    int y = 30;
    int lineHeight = 15;
    int maxWidth = 310;  
    int charsPerLine = maxWidth / 6;  
    
    
    String remainingText = response;
    while (remainingText.length() > 0 && y < 170) {
      
      int breakPoint = minInt(charsPerLine, remainingText.length());
      
      if (breakPoint < remainingText.length()) {
        int lastSpace = remainingText.lastIndexOf(' ', breakPoint);
        if (lastSpace > 0) {
          breakPoint = lastSpace;
        }
      }
      
      String line = remainingText.substring(0, breakPoint);
      M5.Lcd.setCursor(5, y);
      M5.Lcd.print(line);
      
      y += lineHeight;
      remainingText = remainingText.substring(breakPoint);
      
      while (remainingText.length() > 0 && remainingText.charAt(0) == ' ') {
        remainingText = remainingText.substring(1);
      }
    }
    
    if (remainingText.length() > 0) {
      M5.Lcd.setCursor(5, y);
      M5.Lcd.print("... (more)");
    }
    
  
    M5.Lcd.fillRect(0, 180, 320, 60, TFT_BLACK);
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(80, 195);
    M5.Lcd.print("Press A to continue");
  }
  
  void displayText(String text, uint16_t color, int textSize = 1) {
    M5.Lcd.setTextColor(color, TFT_BLACK);
    M5.Lcd.setTextSize(textSize);
    
    int y = 50;
    int maxWidth = 310;
    int charsPerLine = maxWidth / (6 * textSize);
    
    int start = 0;
    while (start < text.length()) {
      int end = minInt(start + charsPerLine, text.length());
      String line = text.substring(start, end);
      
      M5.Lcd.setCursor(5, y);
      M5.Lcd.print(line);
      
      y += 16 * textSize;
      if (y > 170) break;
      
      start = end;
    }
  }
  
  void drawProgress(int percentage) {
    int barWidth = 200;
    int barHeight = 20;
    int x = 60;
    int y = 140;
    
    M5.Lcd.fillRect(x, y, barWidth, barHeight, TFT_BLACK);
    
    int progressWidth = (barWidth * percentage) / 100;
    if (progressWidth > 0) {
      M5.Lcd.fillRect(x, y, progressWidth, barHeight, TFT_BLUE);
    }
    
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(x + barWidth/2 - 20, y + 25);
    M5.Lcd.print(String(percentage) + "%");
  }
  
  void showGeneratingAnimation() {
    static int frame = 0;
    static unsigned long lastUpdate = 0;
    
    if (millis() - lastUpdate > 300) {
      lastUpdate = millis();
      
      
      M5.Lcd.fillRect(140, 100, 40, 30, TFT_BLACK);
      M5.Lcd.setTextColor(TFT_MAGENTA, TFT_BLACK);
      M5.Lcd.setTextSize(2);
      
      String dots = "";
      for (int i = 0; i < (frame % 4); i++) {
        dots += ".";
      }
      
      M5.Lcd.setCursor(140, 100);
      M5.Lcd.print("AI" + dots);
      
      frame++;
    }
  }
  
  void showMessage(String message, uint16_t color) {
    clearScreen(TFT_BLACK);
    M5.Lcd.setTextColor(color, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    
    int textWidth = message.length() * 12; 
    int x = (320 - textWidth) / 2;
    if (x < 0) x = 0;
    
    M5.Lcd.setCursor(x, 110);
    M5.Lcd.print(message);
  }
  
  void showNewSessionScreen() {
    clearScreen(TFT_DARKGREEN);
    
    for (int i = 0; i < 5; i++) {
      M5.Lcd.fillRect(0, 0, 64 * i, 240, TFT_DARKGREEN);
      delay(30);
    }
    
    M5.Lcd.setTextColor(TFT_WHITE, TFT_DARKGREEN);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(90, 100);
    M5.Lcd.print("Session Cleared");
    
    for (int i = 0; i < 3; i++) {
      M5.Lcd.setTextColor(TFT_YELLOW, TFT_DARKGREEN);
      M5.Lcd.setCursor(70, 130);
      M5.Lcd.print("Ready for new chat");
      delay(300);
      
      M5.Lcd.fillRect(70, 130, 180, 20, TFT_DARKGREEN);
      delay(300);
    }
    
    delay(300);
  }
  
  void showSystemInfoScreen() {
    clearScreen(TFT_BLACK);
    
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLACK);
    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(100, 5);
    M5.Lcd.print("System Info");
    
    M5.Lcd.drawLine(0, 35, 320, 35, TFT_WHITE);
  }
 
  void setWifiStatus(bool connected) {
    wifiConnected = connected;
  }
  
private:
  bool wifiConnected = false;
};

#endif