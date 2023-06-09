//Description: Atomic model AlarmAdmin

#ifndef __ALARMADMIN_H
#define __ALARMADMIN_H

#include "time.h"
#include "atomic.h"

class AlarmAdmin : public Atomic
{
	public:
		AlarmAdmin(const string &name = "AlarmAdmin" ); //Constructor.
		virtual string className() const {return "AlarmAdmin";}
		
	protected:
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//Input ports.
		const Port &ArmReq_In;
		const Port &DisarmReq_In;
		const Port &AlarmPin_Ok;
		//Output ports.
		Port &Admin_Out;
		Port &Alarm_Status1;
		Port &Alarm_Status2;
		Port &Error;
		Port &Alarm_Req;
	
		Time processingTime;
		
		enum Status {disarmed, armed};
		Status status;
		enum Request {disarm, arm, invalid, none};
		Request request;
		enum Errors {invalid_action, invalid_pin, no};
		Errors err;

};  //class AlarmAdmin

#endif