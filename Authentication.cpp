//Description: Atomic model Authentication

#include "Authentication.h" //header file for Alarm_Admin
#include <stdlib.h>		// for rand function.
#include "message.h"    // header file of ExternalMessage, InternalMessage
#include "distri.h"        // class Distribution
#include "mainsimu.h"   // header file of the main simulator

//Constructor.
Authentication::Authentication( const string &name )
: Atomic(name)
, Pin_In (addInputPort ("Pin_In"))
, Alarm_Req (addInputPort ("Alarm_Req"))
, Alarm_Status2 (addInputPort ("Alarm_Status2"))
, AlarmPin_Ok (addOutputPort ("AlarmPin_Ok"))
, Error (addOutputPort ("Error"))
, DoorPin_Ok (addOutputPort ("DoorPin_Ok"))
, processingTime (0,0,0,30)
, status (disarmed)
, request (nada)
, pinchk (none)
, err (no)
{
}

//Initialization function.
Model &Authentication::initFunction()
{	
	request = nada;
	status = disarmed;
	pinchk = none;
	err = no;
	
	//Stay in passive state until an external event comes.
	holdIn( passive, Time::Inf );

	return *this ;
}

//External transition function.
Model &Authentication::externalFunction( const ExternalMessage &msg )
{
	
	if( msg.port() == Alarm_Status2 )		//Receive alarm status from Alarm_Admin.
	{
	   if( msg.value() == 0 && request == nada )  	//Status of alarm is disarmed.
		{
			status = disarmed;
			pinchk = none;
			request = nada;  
			holdIn( passive, Time::Inf );
		}
	   if ( msg.value() == 1 && request == nada)	//Status of alarm is armed.
	   {
			status = armed;
			pinchk = none;
			request = nada;  
			holdIn( passive, Time::Inf );
		}
	}

	else if( msg.port() == Pin_In)
	{
		//Generate random number to simulate entering of PIN correctly or incorrectly.
		randnumber = (double)rand()/(double)RAND_MAX;
		
		if( msg.value() == 1 && request == arm ) //PIN entered to arm the alarm.
		{
			if ( randnumber <= 0.9)
			{
				pinchk = arm_valid;
			}
			else
			{
				pinchk = invalid;	
			}
			holdIn( active, processingTime );
		}

		if( msg.value() == 1 && request == disarm ) //PIN entered to disarm the alarm.  
		{
			if ( randnumber <= 0.9)
			{
				pinchk = disarm_valid;
			}
			else
			{
				pinchk = invalid;	
			}
			holdIn( active, processingTime );  
		}
		
		if( msg.value() == 1 && request == nada ) //PIN entered to temporarily unlock the door.
		{
			if ( randnumber <= 0.9)
			{
				pinchk = door_valid;
			}
			else
			{
				pinchk = door_invalid;	
				err = invalid_pin;
			}
			holdIn( active, processingTime );  
		}
	}
 
 	else if( msg.port() == Alarm_Req)
	{
	    //Valid disarm request.
	    if( msg.value() == 0 )
		{
			request = disarm;			
			holdIn( active, Time::Inf );	//Need to wait for PIN.
		}
 		
 		//Valid arm request.
 		if ( msg.value() == 1 )
 		{
 			request = arm;	
 			holdIn(active, Time::Inf );		//Need to wait for PIN.
 		}
	}
	return *this;
}

//Internal transition function.
Model &Authentication::internalFunction( const InternalMessage & )
{
 	pinchk = none;
 	err = no;
 	request = nada;
 	passivate();	
 	randnumber = 0;
	return *this;
}

//Output function.
Model &Authentication::outputFunction( const InternalMessage &msg )
{
	//Valid PIN entered to arm the alarm.
	if(pinchk == arm_valid)
	{
		sendOutput(msg.time(), AlarmPin_Ok, pinchk);	//pinchk = 1.
	}
	//Valid PIN entered to disarm the alarm.
	if (pinchk == disarm_valid)
	{
		sendOutput(msg.time(), AlarmPin_Ok, pinchk);  	//pinchk = 0.
	}
	//Invalid PIN entered to arm or disarm the alarm.
	if (pinchk == invalid)
	{
		sendOutput(msg.time(), AlarmPin_Ok, pinchk); 	//pinchk = 2.
	}
	//Valid PIN entered to temporarily unlock the door.
	if (pinchk == door_valid)
	{
		sendOutput(msg.time(), DoorPin_Ok, 1);	
	}
	//Invalid PIN entered to temporarily unlock the door.
	if (pinchk == door_invalid)
	{
		sendOutput(msg.time(), Error, err);				//err = 1 = invalid_pin.
	}
	
	return *this ;
}

Authentication::~Authentication()
{
	delete dist;
}
