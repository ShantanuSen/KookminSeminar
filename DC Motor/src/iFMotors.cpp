#include "iFMotors.h"

void iFMotors::init(){
    
    // configure LED PWM functionalitites
    ledcSetup(LEFT_F_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(LEFT_R_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(RIGHT_F_CH, FREQUENCY, _nPWMResBit);                
    ledcSetup(RIGHT_R_CH, FREQUENCY, _nPWMResBit);

    // attach pin to pwm channel (16 channels available)
    ledcAttachPin(LEFT_F, LEFT_F_CH);                  
    ledcAttachPin(LEFT_R, LEFT_R_CH);
    ledcAttachPin(RIGHT_F, RIGHT_F_CH);   
    ledcAttachPin(RIGHT_R, RIGHT_R_CH);   

    ledcWrite(LEFT_F_CH, 0 );
    ledcWrite(LEFT_R_CH, 0 );  
    ledcWrite(RIGHT_F_CH, 0 );
    ledcWrite(RIGHT_R_CH, 0 );                 

    _nMaxSpeed = (int) pow(2, _nPWMResBit) ;

    motorStop ();  
}

void  iFMotors :: motorStop ()
{
    ledcWrite(LEFT_F_CH, 0 );
    ledcWrite(LEFT_R_CH, 0 ); 
    ledcWrite(RIGHT_F_CH, 0 );
    ledcWrite(RIGHT_R_CH, 0 );                   
}

int  iFMotors::move(int lspeed, int rspeed)
{

#if 1
    int ldirection = 1, rdirection = 1;
    if (lspeed < 0 ){
        ldirection = -1;
    } 
    else{
        ldirection = 1;
    }
    if (rspeed < 0 ){
        rdirection = -1;
    }
    else{
        rdirection = 1;
    }

    lspeed = map( abs(lspeed) , 0, _nMaxSpeed, MIN_ABS_SPEED*_nPWMResBit, _nMaxSpeed);    
    rspeed = map( abs(rspeed) , 0, _nMaxSpeed, MIN_ABS_SPEED*_nPWMResBit, _nMaxSpeed);    

   // lspeed = map( abs(lspeed) , 0, _nMaxSpeed, 400, _nMaxSpeed);    
   // rspeed = map( abs(rspeed) , 0, _nMaxSpeed, 400, _nMaxSpeed);      
    if( lspeed > _nMaxSpeed ) lspeed =_nMaxSpeed;
    if( rspeed > _nMaxSpeed ) rspeed =_nMaxSpeed;

       // printf("lo : %d, ro = %d, t = %d\n",  lspeed, rspeed, ldirection);

    if( ldirection == 1 ){
        ledcWrite(LEFT_F_CH, abs(lspeed)-1 );
        ledcWrite(LEFT_R_CH, 0);       

    }
    else{
        ledcWrite(LEFT_F_CH, 0);
        ledcWrite(LEFT_R_CH, abs(lspeed)-1 );                                     
    }

    if( rdirection == 1 ){
        ledcWrite(RIGHT_F_CH, 0 );
        ledcWrite(RIGHT_R_CH, abs(rspeed)-1 );                     

    }else{
        ledcWrite(RIGHT_F_CH, abs(rspeed)-1);
        ledcWrite(RIGHT_R_CH, 0 ); 

    }                              
#endif

    return 0;
}