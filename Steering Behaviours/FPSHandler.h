
/**----------------------------------------------------------------------
// @Class: FPS handler
//
// @Autor: LE BAS DE BOUCLANS Olivier
// @Date: 5/11/13
//
// @Description: Calculate the frame rate and the rest time needed in the
// main loop to obtain the target Frame Rate.
//----------------------------------------------------------------------**/

#ifndef FPSHANDLER_H
#define FPSHANDLER_H

class FPSHandler
{
    public:
        //Constructor
        FPSHandler(int AimedFrameRate): m_iAimedFrameRate(AimedFrameRate),m_iTick(0),m_iTime(clock()),m_iRestTime(0), m_iFrameRate(0) {}

        //Destructor
        ~FPSHandler() {}

        //Get
        int GetFrameRate() { return m_iFrameRate; }
        int GetRestTime()  { return m_iRestTime; }

        //Set
        void SetAimedFrameRate(int val) { m_iAimedFrameRate = val; }

        //Update the fps
        void Update()
        {
            m_iTick++;

            if( clock()- m_iTime > 100)
            {
                m_iTime = clock();
                m_iFrameRate = m_iTick*10;
                m_iTick = 0;

                if(m_iFrameRate > m_iAimedFrameRate)
                {
                    m_iRestTime++;
                }
                else if( m_iFrameRate < m_iAimedFrameRate && m_iRestTime>0)
                {
                    m_iRestTime--;
                }
            }
        }

    private:
        int m_iTick;
        int m_iFrameRate;
        int m_iAimedFrameRate;
        int m_iRestTime;
        int m_iTime;
};

#endif // FPSHANDLER_H
