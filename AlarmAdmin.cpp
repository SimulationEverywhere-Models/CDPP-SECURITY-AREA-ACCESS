#include "AlarmAdmin.h" //header file for AlarmAdmin
#include "message.h"    // header file of ExternalMessage, InternalMessage
#include "mainsimu.h"   // header file of the main simulator

//Constructor.
AlarmAdmin::AlarmAdmin( const string &name )
: Atomic(name)
, ArmReq_In (addInputPort ("ArmReq_In"))
, DisarmReq_In (addInputPort ("DisarmReq_In"))
, AlarmPin_Ok (addInputPort ("AlarmPin_Ok"))
, Admin_Out (addOutputPort ("Admin_Out"))
, Alarm_Status1 (addOutputPort ("Alarm_Status1"))
, Alarm_Status2 (addOutputPort ("Alarm_Status2"))
, Error (addOutputPort ("Error"))
, Alarm_Req (addOutputPort ("Alarm_Req"))
, processingTime (0,0,0,30)
, status (disarmed)
, request (none)
, err (no)
{
}

//Initialization function.
Model &AlarmAdmin::initFunction()
{	
	request = none;
	status = disarmed;
	err = no;
	
	//Invoke the output function so that the current alarm status is displayed immediately.
	holdIn( passive, Time::Zero );

	return *this ;
}

//External transition function.
Model &AlarmAdmin::externalFunction( const ExternalMessage &msg )
{
	//Arm button was pressed.
	if( msg.port() == ArmReq_In )
	{
	   if( msg.value() == 1 && status == disarmed )  //Alarm is not armed.
		{
			// Change to active state. 
			// Remain active until valid PIN is entered.
			 request = arm;  //Valid arm request, arming process begins.
			 holdIn( active, processingTime ); //need to now prompt for PIN.
		}
	   else 
	   {
			// Alarm was already armed.  Cannot process request.
			request = invalid;
			err = invalid_action;
			holdIn( active, processingTime );  //need to now generate an error message.
		}
	}
	//Disarm button was pressed.
	else if( msg.port() == DisarmReq_In)
	{
		if( msg.value() == 1 && status == armed ) //Alarm is armed.
		{
			// Disarm button was pressed.  Change to active state. 
			// Remain active until valid PIN is entered. 
			 request = disarm;		//Valid disarm request, disarming process begins.
			 holdIn( active, processingTime ); //need to now prompt for PIN.
		}
	   else 
	   {
			// Alarm was already disarmed.  Cannot process request.
			request = invalid;
			err = invalid_action;
			holdIn( active, processingTime );  //need to now generate an error message.
		}
	}
 	//Valid PIN was entered to either arm or disarm the alarm.
 	else if( msg.port() == AlarmPin_Ok)
	{
	    //Valid PIN entered to arm the alarm.
	    if( msg.value() == 1 && status == disarmed)
		{
			request = none;			//Reset request, no valid requests pending.			
			status = armed;			//Arm the alarm.
			holdIn( active, processingTime );
		}
 		
 		//Valid PIN entered to disarm the alarm.
 		if ( msg.value() == 0 && status == armed)
 		{
 			request = none;			//Reset request, no valid requests pending.
 			status = disarmed;			//Disarm the alarm.
 			holdIn(active, processingTime);
 		}
 		//Invalid PIN entered to either arm or disarm the alarm.
 		if (msg.value() == 2)
 		{
 			request = invalid;
 			err = invalid_pin;
 			holdIn(active, processingTime);
 		}
	}
	return *this;
}

//Internal transition function.
Model &AlarmAdmin::internalFunction( const InternalMessage & )
{
 	//Valid arm or disarm request is pending.  Stay active until valid PIN received.
 	if (request == arm || request == disarm)
	{
		holdIn(active, Time::Inf); 
	}
	
	//No valid arm or disarm requests are pending.  Passivate.
	if (request == none)
	{
		passivate();
	}
	
	if (request == invalid)
	{
		request = none;
		err = no;
		passivate();
	}
	
	return *this;
}

//Output function.
Model &AlarmAdmin::outputFunction( const InternalMessage &msg )
{
	if(request == arm)
	{
		sendOutput(msg.time(), Admin_Out, 1);  			//prompt for PIN.
		sendOutput(msg.time(), Alarm_Req, request);  	//request = arm = 1.
	}
	if (request == disarm)
	{
		sendOutput(msg.time(), Admin_Out, 1);  			//prompt for PIN.
		sendOutput(msg.time(), Alarm_Req, request);		//request = disarm = 0.
	}
	if (request == invalid)
	{
		sendOutput(msg.time(), Error, err); 			//0 = invalid action error, 1 = invalid PIN entered, 2 = none.
	}
	if (request == none)
	{
		sendOutput(msg.time(), Alarm_Status1, status);	//0=disarmed, 1=armed.
		sendOutput(msg.time(), Alarm_Status2, status);	//0=disarmed, 1=armed.
	}
	
	return *this ;
}


