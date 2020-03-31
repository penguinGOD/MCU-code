#include "com_prop.h"
//#include "MyGlobe.h"
extern float Time_output;


void TestSend()
{ 
		float measure[16];
		measure[0]=Time_output;
	  COM_Frame SendFrame;
    SendFrame.Length = 6;
    SendFrame.Prop = 0;
    SendFrame.Data.floats_ts[0]=measure[0];
		FRAME_Send(&SendFrame);
}
