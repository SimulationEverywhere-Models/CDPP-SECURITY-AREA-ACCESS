[top]
components : ADMIN disp@Display

in : Arm Disarm PIN
out : Msg

Link : Arm Arm_In@ADMIN
Link : Disarm Disarm_In@ADMIN
Link : PIN PIN_In@ADMIN
Link : Msg_Out@disp Msg
Link : Pin_Prompt@ADMIN PinPrompt_In@disp
Link : AlarmStatus_Out@ADMIN AlarmStatus_In@disp
Link : Error_Out@ADMIN Error_In@disp
Link : DoorOk_Out@ADMIN DoorOk_In@disp

[ADMIN]
components : adm@AlarmAdmin auth@Authentication

in : Arm_In Disarm_In PIN_In
out : Pin_Prompt AlarmStatus_Out Error_Out DoorOk_Out

Link : Arm_In ArmReq_In@adm
Link : Disarm_In DisarmReq_In@adm
Link : PIN_In Pin_In@auth
Link : Admin_Out@adm Pin_Prompt
Link : Alarm_Status1@adm AlarmStatus_Out
Link : Error@adm Error_Out
Link : Error@auth Error_Out
Link : DoorPin_Ok@auth DoorOk_Out
Link : Alarm_Status2@adm Alarm_Status2@auth
Link : Alarm_Req@adm Alarm_Req@auth
Link : AlarmPin_Ok@auth AlarmPin_Ok@adm