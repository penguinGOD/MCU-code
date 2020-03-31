#include "comlib.h"
//#include "system_config.h"

#define COM_FRAME_MAX_LENGTH 0XE0

#define COM_FRAME_MARK 0XEE
#define COM_FRAME_ESCAPE 0XFF

#define HEAD_DETECT       0
#define LENGTH_ACQUIRE    1
#define PROP_ACQUIRE      2
#define DATA_ACQUIRE      3
#define TAIL_CONFIRM      4


COM_Frame MY_USART1_Com_Receive = {0};
FrameRecStatusTypedef MY_USART1_ComRecStatus = {0};



COM_Frame MY_USART2_Com_Receive = {0};
FrameRecStatusTypedef MY_USART2_ComRecStatus = {0};


void FRAME_ReceiveCall(uint8_t data,FrameRecStatusTypedef *pRecInfo,COM_Frame *pFrame)
{
    uint8_t RecStatus = pRecInfo->RecStatus;
    uint8_t preData = pRecInfo->preData;
    if(COM_FRAME_MARK == data && TAIL_CONFIRM != RecStatus)
    {
        if(COM_FRAME_ESCAPE != preData)
        {
            pRecInfo->RecStatus = HEAD_DETECT;
            RecStatus = HEAD_DETECT;
        }
        else                   
        {
            if(pFrame->Length > 0)
            {
                pFrame->Length--;
            }
        }
    }

    switch(RecStatus)
    {
        case HEAD_DETECT:
                pRecInfo->RecStatus = LENGTH_ACQUIRE;
            break;

        case LENGTH_ACQUIRE:
					      if(data < 4)
                {
                   pRecInfo->RecStatus = HEAD_DETECT;
                }
                else
                {
                    pRecInfo->RecLength = data;
                    pFrame->Length = 0;
                    pRecInfo->RecStatus = PROP_ACQUIRE;
                }
            break;

        case PROP_ACQUIRE:
                pFrame->Prop = data;
								if(pRecInfo->RecLength == 4)//command only don't contain data
								{
									pRecInfo->RecStatus = TAIL_CONFIRM;
								}
								else
								{
									pRecInfo->RecStatus = DATA_ACQUIRE;
								}
            break;

        case DATA_ACQUIRE:
                pRecInfo->RecLength--;
                pFrame->Data.uint8_ts[pFrame->Length++] = data;
                if(pRecInfo->RecLength == 4)
                {
                    pRecInfo->RecStatus = TAIL_CONFIRM;
                }
            break;
        case TAIL_CONFIRM:
								if(COM_FRAME_MARK == data)
								{
										ProcessData(pFrame);
								}
								pRecInfo->RecStatus = HEAD_DETECT;
            break;
        default:break;
    }
    pRecInfo->preData = data;
}


void FRAME_Send(COM_Frame* SendFrame)
{
    uint16_t i = 0;
    uint8_t* SendBufTemp;
    uint8_t SendBuf[COM_FRAME_MAX_LENGTH];
    uint8_t length = SendFrame->Length;
    uint8_t lengthTemp = length;
    SendBufTemp = &SendBuf[0];

    *SendBufTemp++ = COM_FRAME_MARK;
    *SendBufTemp++ = length;
    *SendBufTemp++ = SendFrame->Prop;


    for(i = 0;i < length ;i++)
    {
        uint8_t temp = SendFrame->Data.uint8_ts[i];
        if(temp == COM_FRAME_MARK)
        {
         *SendBufTemp++ = COM_FRAME_ESCAPE;
         lengthTemp ++;
        }
        *SendBufTemp++ = temp;
    }
    *SendBufTemp++ = COM_FRAME_MARK;
		lengthTemp += 4;
		SendBuf[1] = lengthTemp;
		
			ComWrite(SendBuf,lengthTemp);			

}




