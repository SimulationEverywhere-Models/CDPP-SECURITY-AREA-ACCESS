[top]
components : auth@Authentication

in : Pin_In Alarm_Req Alarm_Status2
out : AlarmPin_Ok Error DoorPin_Ok

Link : Pin_In Pin_In@auth
Link : Alarm_Req Alarm_Req@auth
Link : Alarm_Status2 Alarm_Status2@auth
Link : AlarmPin_Ok@auth AlarmPin_Ok
Link : Error@auth Error
Link : DoorPin_Ok@auth DoorPin_Ok

