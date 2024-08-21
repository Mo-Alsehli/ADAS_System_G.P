/*
Made by ADAS G.P Team
2023 - 2024
*/


#include <Arduino.h>
#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo_stm.h>


#define WARNING_REAR_PIN    PC15
#define WARNING_RIGHT_PIN   PC14
#define WARNING_LEFT_PIN    PC13

TFLI2C tflI2C;

int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address 

const byte PulsesPerRevolution = 1;  // Set how many pulses there are on each revolution. Default: 2.

const unsigned long ZeroTimeout = 1300000;  // For high response time, a good value would be 100000.
                                           // For reading very low RPM, a good value would be 300000.

// Calibration for smoothing RPM:
const byte numReadings = 2;  // Number of samples for smoothing. The higher, the more smoothing, but it's going to
                             // react slower to changes. 1 = no smoothing. Default: 2.

/////////////
// Variables For Car Speed Calculations:
/////////////

volatile unsigned long LastTimeWeMeasured;  // Stores the last time we measured a pulse so we can calculate the period.
volatile unsigned long PeriodBetweenPulses = ZeroTimeout+1000;  // Stores the period between pulses in microseconds.
                       // It has a big number so it doesn't start with 0 which would be interpreted as a high frequency.
volatile unsigned long PeriodAverage = ZeroTimeout+1000;  // Stores the period between pulses in microseconds in total, if we are taking multiple pulses.
                       // It has a big number so it doesn't start with 0 which would be interpreted as a high frequency.
unsigned long FrequencyRaw;  // Calculated frequency, based on the period. This has a lot of extra decimals without the decimal point.
unsigned long FrequencyReal;  // Frequency without decimals.
unsigned long RPM;  // Raw RPM without any processing.
unsigned int PulseCounter = 1;  // Counts the amount of pulse readings we took so we can average multiple pulses before calculating the period.

unsigned long PeriodSum; // Stores the summation of all the periods to do the average.

unsigned long LastTimeCycleMeasure = LastTimeWeMeasured;  // Stores the last time we measure a pulse in that cycle.
                                    // We need a variable with a value that is not going to be affected by the interrupt
                                    // because we are going to do math and functions that are going to mess up if the values
                                    // changes in the middle of the cycle.
unsigned long CurrentMicros = micros();  // Stores the micros in that cycle.
                                         // We need a variable with a value that is not going to be affected by the interrupt
                                         // because we are going to do math and functions that are going to mess up if the values
                                         // changes in the middle of the cycle.

// We get the RPM by measuring the time between 2 or more pulses so the following will set how many pulses to
// take before calculating the RPM. 1 would be the minimum giving a result every pulse, which would feel very responsive
// even at very low speeds but also is going to be less accurate at higher speeds.
// With a value around 10 you will get a very accurate result at high speeds, but readings at lower speeds are going to be
// farther from eachother making it less "real time" at those speeds.
// There's a function that will set the value depending on the speed so this is done automatically.
unsigned int AmountOfReadings = 1;

unsigned int ZeroDebouncingExtra;  // Stores the extra value added to the ZeroTimeout to debounce it.
                                   // The ZeroTimeout needs debouncing so when the value is close to the threshold it
                                   // doesn't jump from 0 to the value. This extra value changes the threshold a little
                                   // when we show a 0.

// Variables for smoothing tachometer:
unsigned long readings[numReadings];  // The input.
unsigned long readIndex;  // The index of the current reading.
unsigned long total;  // The running total.
unsigned long average;  // The RPM value after applying the smoothing.


// Generic Variables
float speed_prev = 0;
int prev =0, now= 0 ;
float acceleration = 0;
int breakVal = 0;
int warningVal = 0;
int throttle = 0;
float pid_p=0;
float pid_i=0;
float pid_d=0;
double dt = 0, last_time = 0;
double integral = 0, previous = 0, output = 0;
double kp, ki, kd;
double setpoint = 8;
float pwm = 0;
int speed = 0;
float elapsedTime, time1, timePrev,previous_error;
int cruise= 0;
float potVal = 15000;
boolean buttonState = 0;
#define led PC13 
float relative_speed = 0.0;
int16_t threeshold = 0;
int following_speed_now = 0;
int following_speed_prev = 0;
int following_acceleration = 0;
int prev_distance = 0;
int time_now_relative = 0;
int time_prev_relative = 0;
int32_t channel_1_start,channel_1 ;


// Two NRFs For Sending And Recieveing Data From the Dashboard
RF24 radio(PB0, PB1); // CE, CSN
RF24 radioRx(PB12, PA8); // CE, CSN


// const byte address[6] = "00001";
const byte addresses[][6] = {"00001", "00002"};
struct Data_Package {
  int32_t throttle = 0;
    float speed     = 0;
  float relative_speed = 0;
  int16_t   distance  = 0;
  int16_t threshold = 0;
  boolean  warnning  = 0;
  boolean  warnningBrake = 0;
};

Servo esc;
Data_Package data;


int test = 100;

// HardwareSerial SerialX(USART1);
  SPIClass SPI_2(PB15, PB14, PB13);
// HardwareSerial SerialY(USART2);

void setup()  // Start of setup:
{

  pinMode(WARNING_LEFT_PIN, INPUT_PULLUP);
  pinMode(WARNING_REAR_PIN, INPUT_PULLUP);
  pinMode(WARNING_RIGHT_PIN, INPUT_PULLUP);

  // SerialX.begin(115200);
  // SerialY.begin(115200);

  radio.begin();
  radio.openReadingPipe(1,addresses[1]); // 00002
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

  SPI_2.begin();
  radioRx.begin(&SPI_2); 
  radioRx.openWritingPipe(addresses[0]); // 00001 
  radioRx.setPALevel(RF24_PA_HIGH);
  radioRx.setDataRate(RF24_1MBPS);
  radioRx.stopListening();

  pinMode(led,OUTPUT);
  //Serial.begin(115200);  // Begin serial communication.
  attachInterrupt(digitalPinToInterrupt(PA10), Pulse_Event, RISING);  // Enable interruption pin 2 when going from LOW to HIGH.
  attachInterrupt(digitalPinToInterrupt(PA1), Radio_Read, CHANGE);
  kp = 2.25;
  ki = 0.097;
  kd = 1;
  last_time = 0;
  Wire.begin();           // Initalize Wire library
  esc.attach(PA0);
  esc.writeMicroseconds(1500);

  delay(2000); 

}  // End of setup.


void loop()  // Start of loop:
{
  timePrev = time1;  // the previous time is stored before the actual time read
  time1 = millis();  // actual time read
  elapsedTime = (time1 - timePrev) / 1000;

  LastTimeCycleMeasure = LastTimeWeMeasured;  // Store the LastTimeWeMeasured in a variable.
  CurrentMicros = micros();  // Store the micros() in a variable.
  throttle = channel_1;
  data.throttle = channel_1;



  if(tflI2C.getData(tfDist, tfAddr))
  {     
        data.threshold = 1; 
  }
  else 
  {
    tfDist = 900;
    data.threshold = 0; 
  }
  
  data.distance = tfDist;
  
  time_now_relative = millis();
        if((time_now_relative - time_prev_relative) >= 50)
        {
          relative_speed = ((prev_distance - tfDist)*1000) / (time_now_relative - time_prev_relative);
          following_speed_now = (speed/36) - relative_speed;
          prev_distance = tfDist;
          following_acceleration = ((following_speed_now - following_speed_prev) * 1000) / (time_now_relative - time_prev_relative);
          following_speed_prev = following_speed_now;

          data.relative_speed = relative_speed;
          time_prev_relative = time_now_relative;
        }

// FCW Implementation        
  if(throttle < 1490)
  {
    cruise = 0;
  }
  
  if(cruise == 1 && throttle > 1480)
  {
    double error = potVal - speed;
    pid_p = kp*error;
    pid_i = pid_i+(ki*error);  

    pid_d = kd*((error - previous_error)/elapsedTime);
    output = pid_p + pid_i + pid_d;
    
    if(output < -400000)
      {
        output=-400000;
      }
    if(output > 400000)
      {
        output=400000;
      }
    pwm = output/1000 + 1500;
    if(pwm < 1550)
      {
        pwm= 1550;
      }
  if(pwm > 2000)
      {
        pwm=2000;
      }
      
      previous_error = error; //Remember to store the previous error.
      previous_error = error; //Remember to store the previous error.//
      throttle = pwm;
    }
    
    if(((speed > 3000) && (throttle > 1480)) && (relative_speed > 25))
    {
      threeshold_calc();
      if(throttle < 1520)
        {
          data.warnning = 0;
          data.warnningBrake = 0;

        }
      else if((tfDist < (threeshold /2)))
        {
          if((speed <= 12000) && (tfDist<150))
          {
            data.warnningBrake = 1;
            for(int i = 0; i < 700000; i++)
              {
                esc.writeMicroseconds(1050);
              }
            previous_error = 0;
            pid_i = 0;  
          }
          else if((speed <= 16000) && (tfDist < 250))
          {
            data.warnningBrake = 1;
            for(int i = 0; i < 700000; i++)
            {
              esc.writeMicroseconds(1000);
              
            }
            previous_error = 0;
            pid_i = 0;  
          }
          else if((speed > 16000))
          {
            data.warnningBrake = 1;
            for(int i = 0; i < 700000; i++)
            {
              esc.writeMicroseconds(850);
            }
            
            previous_error = 0;
            pid_i = 0;  
          }
        }
      else if((tfDist <= 2*threeshold/3) && (speed > 4000))
      {
        data.warnning = 1;
      }
      else
      {
        data.warnning = 0;
        data.warnningBrake = 0;
      }
    }
    else
    {
        data.warnning = 0;
        data.warnningBrake = 0;
    }
    esc.writeMicroseconds(throttle);
    
        

  if(CurrentMicros < LastTimeCycleMeasure)
  {
    LastTimeCycleMeasure = CurrentMicros;
  }

  // Calculate the frequency:
  FrequencyRaw = 10000000000 / PeriodAverage;  // Calculate the frequency using the period between pulses.

  // Detect if pulses stopped or frequency is too low, so we can show 0 Frequency:
  if(PeriodBetweenPulses > ZeroTimeout - ZeroDebouncingExtra || CurrentMicros - LastTimeCycleMeasure > ZeroTimeout - ZeroDebouncingExtra)
  {  // If the pulses are too far apart that we reached the timeout for zero:
    FrequencyRaw = 0;  // Set frequency as 0.
    ZeroDebouncingExtra = 2000;  // Change the threshold a little so it doesn't bounce.
  }
  else
  {
    ZeroDebouncingExtra = 0;  // Reset the threshold to the normal value so it doesn't bounce.
  }

  FrequencyReal = FrequencyRaw / 10000;  // Get frequency without decimals.
                                          // This is not used to calculate RPM but we remove the decimals just in case
                                          // you want to print it
  // Calculate the RPM:
  RPM = FrequencyRaw / PulsesPerRevolution * 60;  // Frequency divided by amount of pulses per revolution multiply by
                                                  // 60 seconds to get minutes.
  RPM = RPM / 10000;  // Remove the decimals.
  speed = (RPM*0.38)*60/4.150;
  data.speed = speed;

  now = millis();
if(now - prev >= 50)
  {
    acceleration = (speed - speed_prev)/36 ;
    speed_prev = speed;
    // data.acc = acceleration;
    prev = now;
  }
  
  // Smoothing RPM:
  total = total - readings[readIndex];  // Advance to the next position in the array.
  readings[readIndex] = RPM;  // Takes the value that we are going to smooth.
  total = total + readings[readIndex];  // Add the reading to the total.
  readIndex = readIndex + 1;  // Advance to the next position in the array.

  if (readIndex >= numReadings)  // If we're at the end of the array:
  {
    readIndex = 0;  // Reset array index.
  }
  
  // Calculate the average:
  average = total / numReadings;  // The average value it's the smoothed result.

  radioRx.write(&data, sizeof(data));
  if(radio.available())
  {
    radio.read(&buttonState,sizeof(buttonState));
    digitalWrite(led, buttonState);
  }


}  // End of loop.







 
void Pulse_Event()  // The interrupt runs this to calculate the period between pulses:
{

  PeriodBetweenPulses = micros() - LastTimeWeMeasured;  // Current "micros" minus the old "micros" when the last pulse happens.
                                                        // This will result with the period (microseconds) between both pulses.
                                                        // The way is made, the overflow of the "micros" is not going to cause any issue.

  LastTimeWeMeasured = micros();  // Stores the current micros so the next time we have a pulse we would have something to compare with.





  if(PulseCounter >= AmountOfReadings)  // If counter for amount of readings reach the set limit:
  {
    PeriodAverage = PeriodSum / AmountOfReadings;  // Calculate the final period dividing the sum of all readings by the
                                                   // amount of readings to get the average.
    PulseCounter = 1;  // Reset the counter to start over. The reset value is 1 because its the minimum setting allowed (1 reading).
    PeriodSum = PeriodBetweenPulses;  // Reset PeriodSum to start a new averaging operation.
    
    int RemapedAmountOfReadings = map(PeriodBetweenPulses, 40000, 5000, 1, 10);  // Remap the period range to the reading range.
    
    RemapedAmountOfReadings = constrain(RemapedAmountOfReadings, 1, 10);  // Constrain the value so it doesn't go below or above the limits.
    AmountOfReadings = RemapedAmountOfReadings;  // Set amount of readings as the remaped value.
  }
  else
  {
    PulseCounter++;  // Increase the counter for amount of readings by 1.
    PeriodSum = PeriodSum + PeriodBetweenPulses;  // Add the periods so later we can average.
  }

}  // End of Pulse_Event.
void Radio_Read()
{
  if (0b1 & GPIOA->IDR >> 1) 
    {
      channel_1_start = micros();
    }
  else
  {
    channel_1 = micros() - channel_1_start;
  }
}
void threeshold_calc()
{

  if(acceleration < 1)
  acceleration = 1;
  // relative_speed = abs(relative_speed);
  if(following_speed_now >= following_speed_prev)
  {
    threeshold = ((relative_speed*(150+225+1200))/1000) + ((((speed*speed)/1296)-(following_speed_now*following_speed_now))/(2*acceleration)) - ((following_speed_now*relative_speed)/acceleration) + 50;
  }
  else if(following_speed_now < following_speed_prev)
  {
    threeshold = (((speed*speed)/1296)/(2*acceleration)) - ((following_speed_now*following_speed_now)/(following_acceleration)) + (((150+1200)*speed/36)/1000) + ((relative_speed*225)/1000) + 50;
  }
  else if(following_speed_now == 0)
  {
    threeshold = (((speed*speed)/1296)/(2*600)) - ((following_speed_now*following_speed_now)/(600)) + (((150+1200)*speed/36)/1000) + ((relative_speed*225)/1000) + 50;
  }
  if(threeshold > 1000)
  {
    threeshold = 1000;
  }
}


// NOT used
void changeWarnings() {
  
  // LEFT Sensor Warning
  if(0b1 & GPIOC->IDR >> 15){
    //data.blindSpotWarnings |= (1 << 0);
  }else{
    //data.blindSpotWarnings &= ~(1 << 0);

  }

  // Right Sensor Warning
  if(0b1 & GPIOC->IDR >> 14){
    //data.blindSpotWarnings |= (1 << 1);
  }else{
    //data.blindSpotWarnings &= ~(1 << 1);
  }

  // Rear Sensor Warning
  if(0b1 & GPIOC->IDR >> 13){
    //data.blindSpotWarnings |= (1 << 2);
  }else{
    //data.blindSpotWarnings &= ~(1 << 2);
  }
}