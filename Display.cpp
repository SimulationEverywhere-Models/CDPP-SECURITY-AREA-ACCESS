#include "Display.h" //header file for Display
#include "message.h"    // header file of ExternalMessage, InternalMessage
#include "mainsimu.h"   // header file of the main simulator

//Constructor.
Display::Display( const string &name )
: Atomic(name)
, PinPrompt_In (addInputPort ("PinPrompt_In"))
, AlarmStatus_In (addInputPort ("AlarmStatus_In"))
, Error_In (addInputPort ("Error_In"))
, DoorOk_In (addInputPort ("DoorOk_In"))
, Msg_Out (addOutputPort ("Msg_Out"))
, processingTime (0,0,0,30)
, displayTime (0,0,10,0)
, status (disarmed)
, display (disarmedMsg)
{
}

//Initialization function.
Model &Display::initFunction()
{	
	status = disarmed;
	display = disarmedMsg;
	
	//Invoke the output function so that the current alarm status is displayed immediately.
	holdIn( passive, Time::Zero );

	return *this ;
}

//External transition function.
Model &Display::externalFunction( const ExternalMessage &msg )
{
	//Need to prompt user for their PIN.
	if( msg.port() == PinPrompt_In && msg.value() == 1 )
	{
		display = pinPrompt;
		holdIn( active, processingTime );
	}
	//Alarm has been armed or disarmed.
	else if( msg.port() == AlarmStatus_In)
	{
		if( msg.value() == 1) //Alarm was armed.
		{
			display = armedMsg;
			status = armed;
			holdIn( active, processingTime );
		}
		if( msg.value() == 0) //Alarm was disarmed.
	   {
			display = disarmedMsg;
			status = disarmed;
			holdIn( active, processingTime );
		}
	}
 	//Invalid action or invalid PIN entered.
 	else if( msg.port() == Error_In)
	{
	    //Invalid PIN entered.
	    if( msg.value() == 1)
		{
			display = invalidPin;
			holdIn( active, processingTime );
		}
 		
 		//Invalid action taken.
 		if ( msg.value() == 0)
 		{
			display = invalidAction;
			holdIn( active, processingTime );
 		}
	}
	else if( msg.port() == DoorOk_In && msg.value() == 1 )
	{
		display = doorUnlock;
		holdIn( active, processingTime );		
	}
	return *this;
}

//Internal transition function.
Model &Display::internalFunction( const InternalMessage & )
{
 	if (display == armedMsg || display == disarmedMsg)
 	{
 		holdIn( active, Time::Inf );
 	}
 	if (display == pinPrompt)
 	{
 		holdIn( active, Time::Inf );
 	}
 	if (display == invalidAction || display == doorUnlock || display == invalidPin)
 	{
 		if (status == armed)
 		{
 			display = armedMsg;
 			holdIn( active, displayTime);
 		}
 		if (status == disarmed)
 		{
 			display = disarmedMsg;
 			holdIn( active, displayTime);
 		}
 	}
	return *this;
}

//Output function.
Model &Display::outputFunction( const InternalMessage &msg )
{
	if(display == pinPrompt)
	{
		sendOutput(msg.time(), Msg_Out, pinPrompt);
	}
	if(display == armedMsg)
	{
		sendOutput(msg.time(), Msg_Out, armedMsg);
	}
	if(display == disarmedMsg)
	{
		sendOutput(msg.time(), Msg_Out, disarmedMsg);
	}
	if(display == invalidPin)
	{
		sendOutput(msg.time(), Msg_Out, invalidPin);
	}
	if(display == invalidAction)
	{
		sendOutput(msg.time(), Msg_Out, invalidAction);
	}
	if(display == doorUnlock)
	{
		sendOutput(msg.time(), Msg_Out, doorUnlock);
	}
	return *this ;
}



