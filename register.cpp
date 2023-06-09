//Description: Simulator::registerNewAtomics()

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico

#include "AlarmAdmin.h" 			// class AlarmAdmin
#include "Authentication.h"	//class Authentication
#include "Display.h"  		//class Display

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AlarmAdmin>() , "AlarmAdmin" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Authentication>(), "Authentication" );
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Display>(), "Display" );
}
