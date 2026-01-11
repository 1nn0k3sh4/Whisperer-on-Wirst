#ifndef CONFIG_H
#define CONFIG_H

#include "secrets.h"

#define OLLAMA_SERVER "http://192.168.1.7:11434"  

#define WIFI_TIMEOUT 15000
#define HTTP_TIMEOUT 45000  

#define DEFAULT_MODEL "rnj-1:latest"  
#define FALLBACK_MODEL "llama2"      

#define TEMPERATURE 0.8      
#define TOP_P 0.9            
#define NUM_PREDICT 150      
#define REPEAT_PENALTY 1.1   

#define MAX_RESPONSE_LENGTH 400
#define TEXT_SIZE 1
#define LINE_HEIGHT 16

#endif