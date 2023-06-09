//Description: Atomic model Display

#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "time.h"
#include "atomic.h"

class Display : public Atomic
{
	public:
		Display(const string &name = "Display" ); //Constructor.
		virtual string className() const {return "Display";}
		
	protected:
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );

	private:
		//Input ports.
		const Port &PinPrompt_In;
		const Port &AlarmStatus_In;
		const Port &Error_In;
		const Port &DoorOk_In;
		//Output port.
		Port &Msg_Out;
	
		Time displayTime;
		Time processingTime;
		
		enum Status {disarmed, armed};
		Status status;
		enum Displayer {disarmedMsg, armedMsg, pinPrompt, invalidAction, invalidPin, doorUnlock};
		Displayer display;

};  //class Display

#endif