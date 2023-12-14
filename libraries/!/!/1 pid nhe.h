#ifndef _pid_h_
#define _pid_h_
#include <!/! LDN.h>
#define pid_gioi_han_nho_nhat 0
#define pid_gioi_han 2000
float kd,ki,kp;
#define AUTOMATIC	1
  #define MANUAL	0
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
    //PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
    //    double, double, double, int, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

   // PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
   //     double, double, double, int);     //   Setpoint.  Initial tuning parameters are also set here
	
    void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool Compute();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively
  //available but not commonly used functions ********************************************************
    void SetTunings(double, double,       // * While most users will set the tunings once in the 
                    double);         	    //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings_p(double, double,       // * overload for specifying proportional mode
                    double, int);         	  

	void SetControllerDirection(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
										  
										  
										  
  //Display functions ****************************************************************
	double GetKp();						  // These functions query the pid for interal values.
	double GetKi();						  //  they were created mainly for the pid front-end,
	double GetKd();						  // where it's important to know what is actually 
	int GetMode();						  //  inside the PID.
	int GetDirection();					  //
	
	//---------------------------------------- 
	void Initialize();
	
	double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	double dispKi;				//   format for display purposes
	double dispKd;				//
    
	float kp;                  // * (P)roportional Tuning Parameter
    float ki;                  // * (I)ntegral Tuning Parameter
    float kd;                  // * (D)erivative Tuning Parameter
	int pOn;

    double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
	double outputSum, lastInput;

	unsigned long SampleTime;
	bool inAuto, pOnE;
	u16 pid_dem_thoi_gian_lay_mau=0; // don vi la 1ms
/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
void PID_(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int POn)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    inAuto = false;
    SampleTime = 100;							//default Controller Sample Time is 0.1 seconds
    SetTunings_p(Kp, Ki, Kd, POn);
	pid_dem_thoi_gian_lay_mau=0;
    //lastTime = millis()-SampleTime;
}

/*Constructor (...)*********************************************************
 *    To allow backwards compatability for v1.1, or for people that just want
 *    to use Proportional on Error without explicitly saying so
 ***************************************************************************/

void PID_1(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd)
		{
		}
  //  :PID(Input, Output, Setpoint, Kp, Ki, Kd, P_ON_E, ControllerDirection)
//{

//}
 

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
bool Compute()
{
   if(!inAuto) return false;
   pid_dem_thoi_gian_lay_mau++;
   if(pid_dem_thoi_gian_lay_mau>=SampleTime)
   {
      /*Compute all the working error variables*/
      double input = *myInput;
      double error = *mySetpoint - input;
      double dInput = (input - lastInput);
      outputSum+= (ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if(!pOnE) outputSum-= kp * dInput;

      if(outputSum > pid_gioi_han) outputSum= pid_gioi_han;
      else if(outputSum < pid_gioi_han_nho_nhat) outputSum= pid_gioi_han_nho_nhat;

      /*Add Proportional on Error, if P_ON_E is specified*/
	   double output;
      if(pOnE) output = kp * error;
      else output = 0;

      /*Compute Rest of PID Output*/
      output += outputSum - kd * dInput;

	    if(output > pid_gioi_han) output = pid_gioi_han;
      else if(output < pid_gioi_han_nho_nhat) output = pid_gioi_han_nho_nhat;
	    *myOutput = output;

      /*Remember some variables for next time*/
      lastInput = input;
	  pid_dem_thoi_gian_lay_mau=0; // don vi la 1ms
	    return true;
   }
   else return false;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void SetTunings_p(double Kp, double Ki, double Kd, int POn)
{
   if (Kp<0 || Ki<0 || Kd<0) return;

   pOn = POn;
   pOnE = POn == P_ON_E;

   dispKp = Kp; dispKi = Ki; dispKd = Kd;

   double SampleTimeInSec = ((double)SampleTime)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;
}

/* SetTunings(...)*************************************************************
 * Set Tunings using the last-rembered POn setting
 ******************************************************************************/
void SetTunings(double Kp, double Ki, double Kd)
{
    SetTunings_p(Kp, Ki, Kd, pOn); 
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
                      / (double)SampleTime;
      ki *= ratio;
      kd /= ratio;
      SampleTime = (unsigned long)NewSampleTime;
   }
}
/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void SetMode(int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if(newAuto && !inAuto)
    {  /*we just went from manual to auto*/
        Initialize();
    }
    inAuto = newAuto;
}

/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void Initialize()
{
   outputSum = *myOutput;
   lastInput = *myInput;
   if(outputSum > pid_gioi_han) outputSum = pid_gioi_han;
   else if(outputSum < pid_gioi_han_nho_nhat) outputSum = pid_gioi_han_nho_nhat;
}


#endif
