#define inputPin A0
#define outputPin 9
#define sample_rate 10 //sample rate, in Hz

float yn = 0;
float un = 0;
float rn = 0;
float xhat[2] = {0,0};
float yhat = 0;

// These values are determined from the simulation
float Ad[2][2] = { {0.9512, 0.0442}, {0.0, 0.8187} };
float Bd[2]    =   {0.0046, 0.1813};
float C[2]     =   {1.0, 0};
float L[2]     =   {1.4362, 9.6214};
float Kr       =    3.2086;
float K[2]     =   {1.6938, 0.5148};

unsigned long loop_start_time;
unsigned long loop_time;
unsigned long start_time;
unsigned int loopNum = 0; 

void setup(){
  Serial.begin(9600);
  loop_time = 1000000/sample_rate;
  start_time = micros();
  Serial.println("beginning");
  delay(5000);
  rn = 2.5;
}

void loop(){
  loop_start_time = micros();
  
  //read the current value from the input
  yn = voltage(analogRead(inputPin));
  
  //compute the control input and output it to the system
  un = controller(xhat, yhat, yn, un, rn);
  analogWrite(outputPin, digitalValue(un));
  
  //print the control input and system output
  Serial.print(loopNum * 1.0/sample_rate);
  Serial.print(' ');
  Serial.print(un);
  Serial.print(' ');
  Serial.println(yn);
  
  //wait so that we sample at 10Hz
  while(micros() - loop_start_time < loop_time);
  ++loopNum;
}


//This function implements the controller 
//Observer, full-state feedback gains, and reference gains;
float controller(float* xhat, float& yhat, float yn, float un, float rn) {
  // yhat[n] = C*xhat[n];
  yhat = C[0]*xhat[0]+C[1]*xhat[1];
  // xhat[n+1] = Ad*xhat[n] + Bd*u[n] + L*(y[n] - yhat[n])
  float new_xhat0 = Ad[0][0]*xhat[0] + Ad[0][1]*xhat[1] + Bd[0]*un + L[0]*(yn-yhat);
  float new_xhat1 = Ad[1][0]*xhat[0] + Ad[1][1]*xhat[1] + Bd[1]*un + L[1]*(yn-yhat);
  xhat[0] = new_xhat0;
  xhat[1] = new_xhat1;
  
  // control law: u[n] = -K*xhat[n] + Kr*r[n]
  return -K[0]*xhat[0] - K[1]*xhat[1] + Kr*rn;
}

//This function converts the 10-bit value from the ADC to a voltage value
float voltage(int digital_value) {
 return 5.0*digital_value/1023;
}

//This function ensures that the output is in a valid range for analogWrite
int digitalValue(float voltage) {
  if(voltage > 5.0) {
    return 255;
  }
  else if (voltage < 0.0) {
    return 0;
  }
  else {
    return 255* (voltage/5.0);
  }
}


