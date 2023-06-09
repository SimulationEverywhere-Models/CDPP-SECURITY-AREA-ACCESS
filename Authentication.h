//Description: Atomic model Authentication

#ifndef __AUTHENTICATION_H
#define __AUTHENTICATION_H

#include "time.h"
#include "atomic.h"

class Distribution;

class Authentication : public Atomic
{
	public:
		Authentication(const string &name = "Authentication" ); //Constructor.
		~Authentication();										// Destructor
		virtual string className() const {return "Authentication";}
		
	protected:
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//Input ports.
		const Port &Pin_In;
		const Port &Alarm_Req;
		const Port &Alarm_Status2;
		//Output ports.
		Port &AlarmPin_Ok;
		Port &Error;
		Port &DoorPin_Ok;
	
		Time processingTime;
		
		enum Request {disarm, arm, nada};
		Request request;
		enum PinCheck {disarm_valid, arm_valid, invalid, door_valid, door_invalid, none};
		PinCheck pinchk;
		enum Errors {invalid_action, invalid_pin, no};
		Errors err;
		enum Status {disarmed, armed};
		Status status;
		
		Distribution *dist ;
		double randnumber;
		
		Distribution &distribution()
			{return *dist;}

};  //class Authentication

#endif   //__AUTHENTICATION_H