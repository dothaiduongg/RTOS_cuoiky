#ifndef _pid_h_
#define _pid_h_
#include <!/! LDN.h>

double kd,ki,kp;
#define pwm_chu_ky 6000
//signed int toc_do_cu=0;
signed int toc_do_lek=0;
signed int toc_do_lek_tog=0;
signed int toc_do_lek_cu=0;
u16 pid_toc_do(signed int td_dat,signed int td_doc)
{
	signed int pwm_chu_ci_tih;
	u16 pwm_out;
	toc_do_lek = td_dat - td_doc;
	pwm_chu_ci_tih = toc_do_lek*kp + toc_do_lek_tog*ki + (toc_do_lek - toc_do_lek_cu)*kd;
	toc_do_lek_cu = toc_do_lek;  //save last (previous) error
	toc_do_lek_tog += toc_do_lek; //sum of error
	if (toc_do_lek_tog >pwm_chu_ky) toc_do_lek_tog = pwm_chu_ky;
	if (toc_do_lek_tog <-pwm_chu_ky) toc_do_lek_tog = -pwm_chu_ky;
	//update new speed
	if (pwm_chu_ci_tih <pwm_chu_ky & pwm_chu_ci_tih >0)
	{
		pwm_out=pwm_chu_ci_tih;  //set motor speed  
	}
	else
	{
		if (pwm_chu_ci_tih>pwm_chu_ky)
		{
			pwm_out=pwm_chu_ky;
		}
		else
		{
			pwm_out=0;
		}
	}
	return pwm_out;
}



float eT,eT_1,eT_2,uT,rT,uT_1; 
float Kp,Ti,Td,q0,q1,q2,p0,p00;     // Variables para control PID
u16 pid2(signed int dat,signed int doc)
{
	float dat_tam,doc_tam;  
	u16 pwm_out;
	doc_tam=doc;
	dat_tam=dat;
	//TempReal=(TempReal*500)/1024;   // Se aplica la escala adecuada para obtener
	// el valor en ºC.-
	eT=dat_tam-doc_tam;                     //Cálculo error
	//if(SistControl==1)
	{                      // Control PID?
		uT=q0*eT - q1*eT_1 + q2*eT_2 + uT_1;  //Cálculo de la salida PID (uT=[Volt])
		rT=(uT*pwm_chu_ky)/5;                       //duty cycle maximo 1000 -> 5V.-
		/* <<<<< AntiWindup  >>>>>*/
		if (rT>pwm_chu_ky){                         //Salida PID si es mayor que el 1000.-
			uT=(uT + 5*p0)*p00;
			rT=pwm_chu_ky;
		}
		if (rT<1){                            //Salida PID si es menor que el 0
			uT=uT*p00;
			rT=1;
		}
		/* <<<<< Transferencia de salida PID a señal PWM >>>>>*/
		pwm_out=rT;
		//set_pwm1_duty(ControlPWM);
		/*  <<<<< Guardar variables para proximo estado >>>>>*/
		eT_2=eT_1;
		eT_1=eT;
		uT_1=uT;
	}
	return pwm_out;
}












#define AUTOMATIC	1
  #define MANUAL	0
  #define DIRECT  0
  #define REVERSE  1
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

    void pid_dat_gioi_han(double Min, double Max);

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
    
	double kp;                  // * (P)roportional Tuning Parameter
    double ki;                  // * (I)ntegral Tuning Parameter
    double kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;
	int pOn;

    double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
	double outputSum, lastInput;

	unsigned long SampleTime;
	double outMin, outMax;
	bool inAuto, pOnE;
	u16 pid_dem_thoi_gian_lay_mau=0; // don vi la 1ms
/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
void PID_(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int POn, int ControllerDirection)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    inAuto = false;

    pid_dat_gioi_han(0, 255);				//default output limit corresponds to
												//the arduino pwm limits

    SampleTime = 100;							//default Controller Sample Time is 0.1 seconds

    SetControllerDirection(ControllerDirection);
    SetTunings_p(Kp, Ki, Kd, POn);
	pid_dem_thoi_gian_lay_mau=0;
    //lastTime = millis()-SampleTime;
}

/*Constructor (...)*********************************************************
 *    To allow backwards compatability for v1.1, or for people that just want
 *    to use Proportional on Error without explicitly saying so
 ***************************************************************************/

void PID_1(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int ControllerDirection)
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

      if(outputSum > outMax) outputSum= outMax;
      else if(outputSum < outMin) outputSum= outMin;

      /*Add Proportional on Error, if P_ON_E is specified*/
	   double output;
      if(pOnE) output = kp * error;
      else output = 0;

      /*Compute Rest of PID Output*/
      output += outputSum - kd * dInput;

	    if(output > outMax) output = outMax;
      else if(output < outMin) output = outMin;
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

  if(controllerDirection ==REVERSE)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
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

/* pid_dat_gioi_han(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void pid_dat_gioi_han(double Min, double Max)
{
   if(Min >= Max) return;
   outMin = Min;
   outMax = Max;

   if(inAuto)
   {
	   if(*myOutput > outMax) *myOutput = outMax;
	   else if(*myOutput < outMin) *myOutput = outMin;

	   if(outputSum > outMax) outputSum= outMax;
	   else if(outputSum < outMin) outputSum= outMin;
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
   if(outputSum > outMax) outputSum = outMax;
   else if(outputSum < outMin) outputSum = outMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void SetControllerDirection(int Direction)
{
   if(inAuto && Direction !=controllerDirection)
   {
	    kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
   controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
double GetKp(){ return  dispKp; }
double GetKi(){ return  dispKi;}
double GetKd(){ return  dispKd;}
int GetMode(){ return  inAuto ? AUTOMATIC : MANUAL;}
int GetDirection(){ return controllerDirection;}



#endif
