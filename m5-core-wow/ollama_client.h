#ifndef OLLAMA_CLIENT_H
#define OLLAMA_CLIENT_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

class OllamaClient {
private:
  String serverAddress;
  
  using JsonDoc = JsonDocument;
  
public:
  OllamaClient() : serverAddress(OLLAMA_SERVER) {}
  
  bool checkConnection() {
    HTTPClient http;
    String url = serverAddress + "/api/tags";
    
    http.begin(url);
    http.setTimeout(5000);
    
    int httpCode = http.GET();
    bool connected = (httpCode == 200);
    
    if (connected) {
      Serial.println("✓ Ollama connection successful");
    } else {
      Serial.printf("✗ Ollama connection failed. HTTP code: %d\n", httpCode);
    }
    
    http.end();
    return connected;
  }
 
  bool checkModelExists(String modelName) {
    HTTPClient http;
    String url = serverAddress + "/api/tags";
    
    http.begin(url);
    http.setTimeout(5000);
    
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      
      JsonDoc doc;
      DeserializationError error = deserializeJson(doc, payload);
      
      if (!error) {
        JsonArray models = doc["models"].as<JsonArray>();
        for (JsonObject model : models) {
          String name = model["name"].as<String>();
          if (name == modelName) {
            Serial.println("✓ Model found: " + modelName);
            http.end();
            return true;
          }
        }
      }
    }
    
    Serial.println("✗ Model not found: " + modelName);
    http.end();
    return false;
  }
  
  String generateResponse(String prompt, String model = DEFAULT_MODEL) {
    HTTPClient http;
    String url = serverAddress + "/api/generate";
    
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(HTTP_TIMEOUT);
    
    JsonDoc requestDoc;
    requestDoc["model"] = model;
    requestDoc["prompt"] = prompt;
    requestDoc["stream"] = false;
    
    JsonObject options = requestDoc["options"].to<JsonObject>();
    options["temperature"] = TEMPERATURE;
    options["top_p"] = TOP_P;
    options["num_predict"] = NUM_PREDICT;
    options["repeat_penalty"] = REPEAT_PENALTY;
    options["seed"] = random(10000);
   
    JsonArray context = requestDoc["context"].to<JsonArray>();
    
    String requestBody;
    serializeJson(requestDoc, requestBody);
    
    Serial.println("Sending request to " + model + "...");
    Serial.println("Prompt: " + prompt.substring(0, 50) + "...");
    
    unsigned long startTime = millis();
    int httpCode = http.POST(requestBody);
    unsigned long responseTime = millis() - startTime;
    
    Serial.printf("Response time: %lu ms\n", responseTime);
    
    if (httpCode == 200) {
      String response = http.getString();
      
      JsonDoc responseDoc;
      DeserializationError error = deserializeJson(responseDoc, response);
      
      if (!error) {
        String generatedText = responseDoc["response"].as<String>();
        
        generatedText.trim();
        generatedText.replace("\n\n", "\n");
        
        if (responseDoc.containsKey("total_duration")) {
          int totalDuration = responseDoc["total_duration"];
          int loadDuration = responseDoc["load_duration"];
          int promptEvalCount = responseDoc["prompt_eval_count"];
          int evalCount = responseDoc["eval_count"];
          
          Serial.printf("Stats: Total %dms, Load %dms, Tokens %d/%d\n",
                       totalDuration / 1000000, loadDuration / 1000000,
                       promptEvalCount, evalCount);
        }
        
        if (generatedText.length() > MAX_RESPONSE_LENGTH) {
          int lastPeriod = generatedText.lastIndexOf('.', MAX_RESPONSE_LENGTH);
          if (lastPeriod > 0) {
            generatedText = generatedText.substring(0, lastPeriod + 1);
          } else {
            generatedText = generatedText.substring(0, MAX_RESPONSE_LENGTH) + "...";
          }
        }
        
        return generatedText;
      } else {
        Serial.println("JSON parsing error: " + String(error.c_str()));
        return "Error: Could not parse response";
      }
    } else {
      Serial.printf("HTTP error: %d\n", httpCode);
      if (httpCode == 404) {
        return "Error: Model not found. Try: ollama pull " + model;
      }
      return "Error: HTTP " + String(httpCode);
    }
    
    http.end();
  }
  
  String getModelInfo(String modelName) {
    HTTPClient http;
    String url = serverAddress + "/api/show";
    
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    
    String json = "{\"name\":\"" + modelName + "\"}";
    int httpCode = http.POST(json);
    
    if (httpCode == 200) {
      String response = http.getString();
      
      JsonDoc doc;
      deserializeJson(doc, response);
      
      String info = "Model: " + modelName + "\n";
      
      if (doc["details"].containsKey("family")) {
        info += "Family: " + doc["details"]["family"].as<String>() + "\n";
      }
      
      if (doc["details"].containsKey("parameter_size")) {
        info += "Parameters: " + doc["details"]["parameter_size"].as<String>() + "\n";
      }
      
      if (doc["details"].containsKey("quantization_level")) {
        info += "Quantization: " + doc["details"]["quantization_level"].as<String>() + "\n";
      }
      
      return info;
    }
    
    http.end();
    return "Could not get model info";
  }
};

#endif