#define inputPin A0
#define outputPin A1
#define sample_rate 10 //sample rate, in Hz

int yn = 0;
int un = 0;
int rn = 0;
int xhat[2] = {0,0};
int yhat = 0;

int Ad[2][2] = { {0,0}, {0,0} };
int Bd[2]    =   {0,0};
int C[2]     =   {0,0};
int L[2]     =   {0,0};
int Kr       =    0;
int K[2]     =   {0,0};

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
    rn = 512;
  }
  
  //read the current value from the input
  yn = analogRead(inputPin);
  
  //compute the control input and output it to the system
  un = controller(xhat, yhat, yn, un, rn);
  analogWrite(outputPin,un);
  
  //print the control input and system output
  Serial.print(un);
  Serial.print('\t');
  Serial.println(yn);
  
  //wait so that we sample at 10Hz
  while(micros() - loop_start_time < loop_time);
}


//This function implements the controller 
//Observer, full-state feedback gains, and reference gains;
int controller(int* xhat, int& yhat, int yn, int un, int rn) {
  yhat = C[0]*xhat[0]+C[1]*xhat[1];
  int new_xhat0 = Ad[0][0]*xhat[0] + Ad[0][1]*xhat[1] + Bd[0]*un + L[0]*(yn-yhat);
  int new_xhat1 = Ad[1][0]*xhat[1] + Ad[1][1]*xhat[1] + Bd[1]*un + L[0]*(yn-yhat);
  xhat[0] = new_xhat0;
  xhat[1] = new_xhat1;
  
  return saturate(-K[0]*xhat[0] - K[1]*xhat[1] + Kr*rn);
}

//This function ensures that the output is in a valid range for analogWrite
int saturate(int un) {
  if (un > 1023) {
    un = 1023;
  }
  if (un < 0) {
    un = 0;
  }
  return un;
}
