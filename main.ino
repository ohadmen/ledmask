
#include "mic_sampler.h"
#include "vis_control.h"


MicSampler ms;
VisControl vc;
void setup() 
{
   
}
void loop() 
{
   
   ms.loop();
   unsigned int v = ms.getP2P();
   vc.setVolume(v);
   vc.loop();
}