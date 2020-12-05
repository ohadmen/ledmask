#include "mic_sampler.h"
constexpr int SAMPLE_WINDOW = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

MicSampler ms;
void setup() 
{
   Serial.begin(115200);
}


void loop() 
{
   
   ms.loop();
   Serial.println(ms.getP2P());
}