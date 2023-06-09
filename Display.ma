[top]
components : disp@Display

in : PinPrompt_In AlarmStatus_In Error_In DoorOk_In 
out : Msg_Out

Link : PinPrompt_In PinPrompt_In@disp
Link : AlarmStatus_In AlarmStatus_In@disp
Link : Error_In Error_In@disp
Link : DoorOk_In DoorOk_In@disp
Link : Msg_Out@disp Msg_Out