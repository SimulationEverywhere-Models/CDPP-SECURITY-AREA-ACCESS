[top]
components : adm@AlarmAdmin

in : ArmReq_In DisarmReq_In AlarmPin_Ok
out : Admin_Out Alarm_Status1 Alarm_Status2 Error Alarm_Req

Link : ArmReq_In ArmReq_In@adm
Link : DisarmReq_In DisarmReq_In@adm
Link : AlarmPin_Ok AlarmPin_Ok@adm
Link : Admin_Out@adm Admin_Out
Link : Alarm_Status1@adm Alarm_Status1
Link : Alarm_Status2@adm Alarm_Status2
Link : Error@adm Error
Link : Alarm_Req@adm Alarm_Req
