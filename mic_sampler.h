#ifndef MIC_CONTROLLER
#define MIC_CONTROLLER

class MicSampler
{
    static constexpr int PORT = 0;
    static constexpr int SAMPLE_WIN_MSEC = 50;

    unsigned long m_startMillis;
    unsigned int m_signalMax;
    unsigned int m_signalMin;

public:
    MicSampler() { resetSampleWindow(); }

    void resetSampleWindow()
    {
        m_signalMax = 0;
        m_signalMin = 1024;
        m_startMillis = millis(); // Start of sample window
    }
    void loop()
    {
        if (millis() - m_startMillis > SAMPLE_WIN_MSEC)
        {
            resetSampleWindow();
        }
        unsigned int sample = analogRead(0);
        m_signalMax = max(m_signalMax, sample);
        m_signalMin = min(m_signalMin, sample);
    }
    unsigned int getP2P() const { return m_signalMax - m_signalMin; }
};
#endif