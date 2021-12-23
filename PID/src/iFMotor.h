#ifndef iFMotors_v1_h
#define iFMotors_v1_h
#define iFMOTORS_LIBRARY_VERSION	1.1.1

#include <Arduino.h>

#define MC_LEFT_CH (0)
#define MC_RIGHT_CH (15)
#define FREQUENCY (5000)

#define FORWARD   1
#define BACKWARD  0

#define MIN_ABS_SPEED (1)

#define LEFT_F     7
#define LEFT_R     8  
#define RIGHT_F    27
#define RIGHT_R    26   


#define LEFT_F_CH (0)
#define LEFT_R_CH (1)
#define RIGHT_F_CH (2)
#define RIGHT_R_CH (3)

/* PWM resolution */
#define PWM_RES                 (10)
#define PWM_BASE_FREQ           (5 * 1000) // 5 kHz

class iFMotor{
    private:
        const int _nPWMResBit = 10;
        int _nMaxSpeed;
        int _nType = 1;

    public:
        iFMotor(){}

        void init();

        int  move(int lspeed, int rspeed);

        void motorStop();
        int getMaxSpeed(){ return _nMaxSpeed; }
};

#endif