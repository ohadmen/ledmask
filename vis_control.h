#ifndef VIS_CONTROL
#define VIS_CONTROL
#include <FastLED.h>
class VisControl
{
    static constexpr unsigned int NUM_LEDS = 16;
    static constexpr unsigned int LED_PIN = 9;
    static constexpr unsigned int MAX_VOLUME = 256;
    static constexpr unsigned int MIN_VOLUME = 1;

    static constexpr unsigned long ROLLING_SPEED_MSEC=100;

    CRGB m_leds[NUM_LEDS];
    unsigned int m_counter;
    int m_counterDir;
    unsigned long m_startMillis;


    void rollingLight()
    {
        if(millis()-m_startMillis<ROLLING_SPEED_MSEC)
            return;
        m_startMillis=millis();    
        m_leds[m_counter].g=0;
        m_leds[NUM_LEDS-1-m_counter].b=0;
        if(m_counter==0)
        {
            m_counterDir=1;
        }
        if(m_counter==NUM_LEDS-1)
        {
            m_counterDir=-1;
        }
        m_counter +=m_counterDir;
        m_leds[m_counter].g=100;        
        m_leds[NUM_LEDS-1-m_counter].b=100;
        

    }
public:
    VisControl()
    {
        
        FastLED.addLeds<WS2812, LED_PIN, GRB>(m_leds, NUM_LEDS);
        m_counter=0;
        m_counterDir = 1;
        m_startMillis=0;

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
        unsigned int maxBin = (max(MIN_VOLUME,min(v,MAX_VOLUME))-MIN_VOLUME)*MID_BID/VOL_RANGE;
        for(unsigned int i=0;i!=NUM_LEDS;++i)
            m_leds[i].r=0;
        for(unsigned int i=0;i!=maxBin;++i)
        {
            m_leds[MID_BID+i].r=255;
            m_leds[MID_BID-i-1].r=255;
        }
            
    }
};
#endif