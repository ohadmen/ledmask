#ifndef VIS_CONTROL
#define VIS_CONTROL
#include <FastLED.h>
class VisControl
{
    static constexpr unsigned int NUM_LEDS = 16;
    static constexpr unsigned int LED_PIN = 9;
    static constexpr unsigned int MAX_VOLUME = 256;
    static constexpr unsigned int MIN_VOLUME = 1;

    CRGB m_leds[NUM_LEDS];
    unsigned int m_counter;

    void rollingLight()
    {
        
        ++m_counter;
        for(unsigned int i=0;i!=NUM_LEDS;++i)
            m_leds[i].green=0;
        int bin = int((pow(sin(M_PI*0.002*m_counter),2))*NUM_LEDS);
        
        m_leds[bin].green=255;

    }
public:
    VisControl()
    {
        
        FastLED.addLeds<WS2812, LED_PIN, GRB>(m_leds, NUM_LEDS);
        m_counter=0;
    }
    void loop()
    {
        rollingLight();
        FastLED.show();
    }
    void setVolume(unsigned int v)
    {
        constexpr unsigned int MID_BID = NUM_LEDS>>1;
        constexpr unsigned int VOL_RANGE = MAX_VOLUME-MIN_VOLUME;
        unsigned int maxBin = (max(MIN_VOLUME,v)-MIN_VOLUME)*MID_BID/VOL_RANGE;
        for(unsigned int i=0;i!=NUM_LEDS;++i)
            m_leds[i].r=0;
        for(unsigned int i=0;i!=maxBin;++i)
        {
            m_leds[MID_BID+i].r=255;
            m_leds[MID_BID-i].r=255;
        }
            
    }
};
#endif