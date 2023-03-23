/******************************************************************************
 * Project: Dual Axis Solar Tracker
 *
 * Written By: Hany Elesawy
 *
 * Version: v6.0
 *
 * Version History:
 * v1.0 Added Quad LDR                                      - 2022.12.14
 * v1.1 Added Dual Axis Control                             - 2022.12.15
 * v1.2 Fixed a bug in rotation direction                   - 2023.01.14
 * 
 * v2.0 changed the tracking algorithm (removed average)    - 2023.01.15
 *      surprisingly this improved tracking drastically
 * 
 * v3.0 Added RainDrop Sensor Support                       - 2023.01.19
 * V3.1 Enabled a simple rain buzzer alarm (with delay)     - 2023.01.19
 * v4.0 Sharp tracker angle on heavy rain (for cleaning)    - 2023.01.19
 * 
 * v5.0 Added LCD Logic + Integration                       - 2023.01.26
 * v6.0 Removed most delays in favour of using Millis()     - 2023.01.27
 * v6.2 Added tracking_response_time                        - 2023.01.27
 ******************************************************************************/

/*----------------------------------------------------------------------------*/
/*------------------ Project Specific Behaviour Description ------------------*/
/*----------------------------------------------------------------------------*/
/*

    VERTICAL SERVO  : is the servo responsible for equalizing "avgLdrTop" and "avgLdrBot" readings
    HORIZONTAl SERVO: is the servo responsible for equalizing "avgLdrLeft" and "avgLdrRight" readings

    When the tracker is flat (looking up)            ---> Vertical Servo is with angle = 0
    When the tracker is looking down (to the ground) ---> Vertical Servo is with angle = 180

    When the tracker is looking to the left          ---> Horizontal Servo is with angle = 0
    When the tracker is looking to the Right         ---> Horizontal Servo is with angle = 180


    Ideally, we don't want the solar tracker looking down as there is nothing to be done there.
    If we don't limit it, sometimes it will take the easy path to equalize the avgLdrTop, avgLdrBot readings.
    When it looks down. the reading will be equalized.


*/

/*----------------------------------------------------------------------------*/
/*------------------------------- Header Files -------------------------------*/
/*----------------------------------------------------------------------------*/

#include <Servo.h>
#include <LiquidCrystal.h>

/*----------------------------------------------------------------------------*/
/*------------------------------- Global -------------------------------------*/
/*----------------------------------------------------------------------------*/

Servo servo_horizontal;
Servo servo_vertical;

//Parameters:    (rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(0 , 2     , 3 , 4 , 5 , 6 );

/*----- Calibration and Angle Tweaks -----*/

int servoV_angle       = 0;              // Starting Vertical Angle (Flat)
int servoV_UpperLimit  = 105;            // Looking Down Limit 
int servoV_LowerLimit  = 0;              // Looking Up Limit
int servoV_SharpAngle  = 80;            // Some Sharp Angle to wash solar panels by rain

int servoH_angle       = 0;              // Starting Horizontal Angle
int servoH_UpperLimit  = 180;            // Looking to the Right Limit
int servoH_LowerLimit  = 0;              // Looking to the Left Limit
int servoH_SharpAngle  = 115;            // Some Sharp Angle to wash solar panels by rain

/*------ Dual Axis Response Time ------*/
int tracking_response_time = 30;         // How fast should the whole project React to light changes.

/*--------------- Flags ---------------*/
bool isItRaining = false;
bool isItRainingHard = false;

/*----- Time Intervals of Events (ms) -----*/
#define interval_LCDPrint    200                // Time interval to print on LCD
#define interval_BuzzerBeep  500                // Time to buzzer High


unsigned long currentTime               =0;

unsigned long previousTime_LCDPrint     =0;     // When was the last time LCD printed something?
unsigned long previousTime_BuzzerHigh   =0;     // When was the last time Buzzer High?
unsigned long previousTime_BuzzerLow    =0;     // When was the last time Buzzer low?

/*---- Other Variables ----*/
float temperatureC_LM35;
float temperatureC = 19.68;

/*----------------------------------------------------------------------------*/
/*------------------------------- Setup --------------------------------------*/
/*----------------------------------------------------------------------------*/
void setup()
{
    lcd.   begin(16,2);
    //Serial.begin(9600);

    /*----- Pin Configuration ----------------*/
    
    #define servBot 10
    #define servTop 11

    #define ldrTopL A1
    #define ldrTopR A2
    #define ldrBotL A3
    #define ldrBotR A4

    #define LM35     A0 
    #define rainDrop A6
    
    #define buzzer 8

    

    /*----- Pin Modes (Input / Output) ----------------*/
    
    pinMode(ldrTopL , INPUT);
    pinMode(ldrTopR , INPUT);
    pinMode(ldrBotL , INPUT);
    pinMode(ldrBotR , INPUT);

    pinMode(rainDrop, INPUT);
    pinMode(LM35    , INPUT);

    pinMode(buzzer  , OUTPUT);

    servo_horizontal.attach(servBot);
    servo_vertical.attach(servTop);


    /* --- Default Orientation ---*/
    servo_horizontal.write(servoH_angle);
    servo_vertical.write(servoV_angle);
}

/*----------------------------------------------------------------------------*/
/*------------------------------- Main Logic ---------------------------------*/
/*----------------------------------------------------------------------------*/

void loop()
{
    
    delay(tracking_response_time);


    currentTime = millis();

    /*------------- Analog Readings -------------*/

    int ADC_ldrTopL  = analogRead(ldrTopL);
    int ADC_ldrTopR  = analogRead(ldrTopR);
    int ADC_ldrBotL  = analogRead(ldrBotL);
    int ADC_ldrBotR  = analogRead(ldrBotR);

    int ADC_LM35 = analogRead(LM35);
    int ADC_RainDrop   = analogRead(rainDrop);

    servoH_angle = servo_horizontal.read();
    servoV_angle = servo_vertical.read();

    float voltage =  ADC_LM35 * (5.0/1024.0);
    temperatureC_LM35 = voltage * 100;
    /*------------------------------------------*/

    if( RainStatus() == true)
    {
        AlarmBeepBeep();

        servoAllSharpAngle();
    }
    else
    {
        /*--- Vertical Servo Positioning ---*/
        if (ADC_ldrTopL > ADC_ldrBotL)
        {
            servoRotateUp();
        }
        else if (ADC_ldrBotL > ADC_ldrTopL)
        {
            servoRotateDown();
        }

        if (ADC_ldrTopR > ADC_ldrBotR)
        {
            servoRotateUp();
        }
        else if (ADC_ldrBotR > ADC_ldrTopR)
        {
            servoRotateDown();
        }

        /*--- Horizontal Servo Positioning ---*/
        if (ADC_ldrTopL > ADC_ldrTopR)
        {
            servoRotateLeft();
        }
        else if (ADC_ldrTopR > ADC_ldrTopL)
        {
            servoRotateRight();
        }

        if (ADC_ldrBotL > ADC_ldrBotR)
        {
            servoRotateLeft();
        }
        else if (ADC_ldrBotR > ADC_ldrBotL)
        {
            servoRotateRight();
        }

    }
}


/*----------------------------------------------------------------------------*/
/*----------------------- User Defined Functions -----------------------------*/
/*----------------------------------------------------------------------------*/

bool RainStatus()
{
    int ADC_RainDrop = analogRead(rainDrop);

    if(ADC_RainDrop < 200)
    {
        if(currentTime - previousTime_LCDPrint > interval_LCDPrint )
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Heavy Rain !!");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(temperatureC);
            lcd.print("C");

            //Serial.println("Heavy Rain !!");

            previousTime_LCDPrint = currentTime;  
        }

        isItRaining = true;
        isItRainingHard = true;
    }
    else if(ADC_RainDrop < 300)
    {
        if(currentTime - previousTime_LCDPrint > interval_LCDPrint )
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Moderate Rain !!");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(temperatureC);
            lcd.print("C");
            
            //Serial.println("Moderate Rain !!");

            previousTime_LCDPrint = currentTime;
        }

        isItRaining = true;
        isItRainingHard = true;
    }
    else if(ADC_RainDrop < 600)
    {
        if(currentTime - previousTime_LCDPrint > interval_LCDPrint )
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Light Rain !!");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(temperatureC);
            lcd.print("C");
            
            //Serial.println("Light Rain !!");

            previousTime_LCDPrint = currentTime;
        }

        isItRaining = true;
        isItRainingHard = false;
    }
    else
    {
        if(currentTime - previousTime_LCDPrint > interval_LCDPrint )
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Weather is Clear");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(temperatureC);
            lcd.print("C");
            
            //Serial.println("Weather is Clear");

            previousTime_LCDPrint = currentTime;
        }

        isItRaining = false;
        isItRainingHard = false;
    }

    return isItRainingHard;

}

void AlarmBeepBeep()
{
    for(int i=0; i<3; i++)
    {
        digitalWrite(buzzer, HIGH);
        delay (500);
        digitalWrite(buzzer, LOW);
        delay (500);
    }

}
void servoAllSharpAngle()
{
    while(servoV_angle > servoV_SharpAngle)
    {
        servo_vertical.write(--servoV_angle);
        delay(10);
    }
    while(servoV_angle < servoV_SharpAngle)
    {
        servo_vertical.write(++servoV_angle);
        delay(10);
    }
    
    while(servoH_angle > servoH_SharpAngle)
    {
        servo_horizontal.write(--servoH_angle);
        delay(10);
    }
    while(servoH_angle < servoH_SharpAngle)
    {
        servo_horizontal.write(++servoH_angle);
        delay(10);

    }

}

void servoRotateUp()
{
    //Serial.println("servoRotateUp");

    if (servoV_angle < servoV_LowerLimit)
        servoV_angle = servoV_LowerLimit;

    servo_vertical.write(--servoV_angle);
}

void servoRotateDown()
{
    //Serial.println("servoRotateDown");

    if (servoV_angle > servoV_UpperLimit)
        servoV_angle = servoV_UpperLimit;

    servo_vertical.write(++servoV_angle);
}

void servoLockVertical()
{
    //Serial.println("servoLockVertical");

    servo_vertical.write(servoV_angle);
}

void servoRotateLeft()
{
    //Serial.println("servoRotateLeft");

    if (servoH_angle < servoH_LowerLimit)
        servoH_angle = servoH_LowerLimit;

    servo_horizontal.write(--servoH_angle);
}
void servoRotateRight()
{
    //Serial.println("servoRotateRight");
    if (servoH_angle > servoH_UpperLimit)
        servoH_angle = servoH_UpperLimit;

    servo_horizontal.write(++servoH_angle);
}
void servoLockHorizontal()
{
    //Serial.println("servoLockHorizontal");
    servo_horizontal.write(servoH_angle);
}
