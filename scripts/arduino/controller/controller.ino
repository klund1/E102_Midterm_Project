#define inputPin A0
#define outputPin A1
#define sample_rate 10 //sample rate, in Hz

float yn = 0;
float un = 0;
float rn = 0;
float xhat[2] = {0,0};
float yhat = 0;

float Ad[2][2] = { {0.9512, 0.0442}, {0.0, 0.8187} };
float Bd[2]    =   {0.0046, 0.1813};
float C[2]     =   {1.0, 0};
float L[2]     =   {1.429, 9.514};
float Kr       =    2.414;
float K[2]     =   {1.082, 0.332};

unsigned long loop_start_time;
unsigned long loop_time;
unsigned long start_time;

void setup(){
  Serial.begin(9600);
  loop_time = 1000000/sample_rate;
  start_time = micros();
}

void loop(){
  loop_start_time = micros();
  
  //input step
  if (rn == 0 && micros() > start_time+1000000) {
    rn = 2.5;
  }
  
  //read the current value from the input
  yn = voltage(analogRead(inputPin));
  
  //compute the control input and output it to the system
  un = controller(xhat, yhat, yn, un, rn);
  analogWrite(outputPin, digitalValue(un));
  
  //print the control input and system output
  Serial.print(un);
  Serial.print('\t');
  Serial.println(yn);
  
  //wait so that we sample at 10Hz
  while(micros() - loop_start_time < loop_time);
}


//This function implements the controller 
//Observer, full-state feedback gains, and reference gains;
float controller(float* xhat, float& yhat, float yn, float un, float rn) {
  yhat = C[0]*xhat[0]+C[1]*xhat[1];
  float new_xhat0 = Ad[0][0]*xhat[0] + Ad[0][1]*xhat[1] + Bd[0]*un + L[0]*(yn-yhat);
  float new_xhat1 = Ad[1][0]*xhat[1] + Ad[1][1]*xhat[1] + Bd[1]*un + L[0]*(yn-yhat);
  xhat[0] = new_xhat0;
  xhat[1] = new_xhat1;
  
  return -K[0]*xhat[0] - K[1]*xhat[1] + Kr*rn;
}

//This function ensures that the output is in a valid range for analogWrite
float voltage(int digital_value) {
 return 5.0*digital_value/1023;
}

int digitalValue(float voltage) {
  if(voltage > 5.0) {
    return 1023;
  }
  else if (voltage < 0.0) {
    return 0;
  }
  else {
    return 1023* (voltage/5.0);
  }
}


