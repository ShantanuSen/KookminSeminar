#ifndef iFLineEncoder_h
#define iFLineEncoder_h

#include <Arduino.h> 

class iFEncoder
{
    private:
        static int8_t m_nLeA, m_nLeB, m_nReA, m_nReB;

        static  volatile  bool lastLeftA; static volatile bool lastLeftB; static volatile bool lastRightA; static volatile bool lastRightB;
          
          
          

        static volatile bool errorLeft;
        static volatile bool errorRight;

        static volatile int32_t countRight, lastCountR;
        static volatile int32_t countLeft, lastCountL;

        static int32_t prevSpeed;

    private:
        static void IRAM_ATTR leftISR();
        static void IRAM_ATTR rightISR();

    public:  
        static portMUX_TYPE muxl;
        static portMUX_TYPE muxr;

    public:  
        iFEncoder(){};
        void init(int8_t leA, int8_t leB, int8_t reA, int8_t reB);
        int32_t getCountLeft();
        int32_t getCountRight();

        static  int32_t getCountLeftReset();
        static  int32_t getCountRightReset();
        
        void resetCountLeft();
        void resetCountRight();
        void resetCounts();
    
        static void taskSpeedNotification(void *pvParameters);

};
#endif