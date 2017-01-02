# alarm_clock
c++ command line alarm clock for ubuntu
This clock plays the specified wav file of your choice at alarm time.  Alarm times are set independantly for each day of the week.


Installation:
Go to root directory of the project and type

make
./clock


Edit the text configuration file alarm_clock_config.txt to set the alarm times for certian days:

0 09:30:00
1 07:00:00
2 07:00:00
3 07:00:00
4 07:00:00
5 07:00:00
6 10:30:00

The first line means on day 0 (Sunday) the alarm goes off at 17:00 (5PM)
Second line (day 1 - Monday) alarm sounds at 7 am
and so on...



 


