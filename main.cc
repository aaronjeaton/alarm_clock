#include <iostream>
#include <ctime>
#include <thread>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

int main()
{


class alarm_clock
	{

	public:

		//Declare a variable (timer) of type time_t (which is seconds since epoch)
		time_t timer;

		//create a pointer to variable of type tm which is a structure of type tm which holds time stuff 
		struct tm * now;

		int alarm_hour, alarm_min, alarm_sec;
		int i;
		std::fstream config_file;
	


		tm daily_alarm[7][3]; // 7 days, 3 alarms possible per day

		alarm_clock()
		{


			//std::cout << "Constructor is executing....\n";
			timer = time(0);
			now = localtime(&timer);

			// load daily alarm schedule from file
		
			config_file.open ("alarm_clock_config.txt");
		
			if (config_file.is_open()) 
				{
				std::cout << "\nConfig File is open";

				}	
			else
				{
				std::cout << "\nCreating Config file alarm_clock_config.txt";
				config_file.open ("alarm_clock_config.txt",std::ios::out);
				config_file.close();
				config_file.open("alarm_clock_config.txt");
				if (config_file.is_open())
					{
					std::cout << "...success!!";
					}
				else
					{
					std::cout << "...failed to create config file.  Settings cannot be saved";
					}	


				}

			config_file.close();		



			read_daily_alarm_schedule();


			
			//print daily alarm schedule to scren



		}


		void alarm_monitor(tm * alarm)
		{
	
					//get alarm for the current day
					timer = time(0);
					now = localtime(&timer);
					
					alarm_hour = daily_alarm[now->tm_wday][0].tm_hour;				
					alarm_min = daily_alarm[now->tm_wday][0].tm_min;
					alarm_sec = daily_alarm[now->tm_wday][0].tm_sec;
					


					if (alarm_hour == now->tm_hour && alarm_min == now->tm_min && alarm_sec == now->tm_sec)
						{ std::cout << "\nAlarm\n";
						//std::this_thread::sleep_for(std::chrono::seconds(1));
 	  					
						while (alarm_min == now->tm_min) 
							{
							i=system("aplay ./bcch.wav");
							timer = time(0);
							now = localtime(&timer);
							}
						}
					else
						{
						//std::cout << "\nno alarm yet.  alarm_hour is " << alarm_hour << " and tm_second is " << now->tm_sec ;

						//std::this_thread::sleep_for(std::chrono::seconds(1));	
						}

		}





		void print_current_time()
		{

			// call function time() with 0 as the argument which returns the current time (seconds since epoch) and assigns the result to variable timer
			timer = time(0);

			//print the current time
			std::cout << ctime(& timer);
		};





		void  set_alarm_time(tm * alarm_pointer)
		{
			
			int hour=0, minute=0, second=0;		
			std::cout << "\nEnter Alarm hour :";
				
			std::cin >> hour;	
			
			while (hour < 0 || hour >= 24) 
				{ 
			
				std::cout << "\nHour is invalid.  Re-enter hour.";
				std::cin >> hour;			
	
				}
			
			alarm_pointer->tm_hour = hour;
			

			std::cout << "\nEnter Alarm minute :";
			std::cin >> minute;
		
			while (minute < 0 || minute >= 60) 
				{ 
			
				std::cout << "\nMinute is invalid.  Re-enter minute.";
				std::cin >> hour;			
	
				}
	
				alarm_pointer->tm_min = minute;		
			
			std::cout << "\nEnter Alarm second :";
			std::cin >> second;

			while (second < 0 || hour >= 60) 
				{ 
			
				std::cout << "\nSecond is invalid.  Re-enter second.";
				std::cin >> hour;			
	
				}
			alarm_pointer->tm_sec = second;
			std::cout << "set_alarm_time alarm address : " << alarm_pointer;

		
			
		}



	
		void print_daily_alarm_schedule()
		{
			

		}



		int save_daily_alarm_schedule()
		{
		//save daily alarm schedule to config file
		config_file.open("alarm_clock_config.txt",std::ios::out|std::ios::trunc);
		
//		if (config_file.eof())	{
					for (i=0; i<7; i++)
						{
						std::cout << i << "\n";
						config_file << i << " " << daily_alarm[i][0].tm_hour << ":" << daily_alarm[i][0].tm_min << ":" << daily_alarm[i][0].tm_sec << "\n"; 

						}

						std::cout << "\nDaily alarms saved to file";
/*					}
			 	
		else // alarm info already exists
	
					{
						for (i=0; i<7; i++)
						{
						config_file << i << " " << daily_alarm[i][0].tm_hour << ":" << daily_alarm[i][0].tm_min << ":" << daily_alarm[i][0].tm_sec << "\n"; 

						}

						std::cout << "\nDaily alarms saved to file";
	

					}
*/

		config_file.close();


		}




		tm * read_daily_alarm_schedule()
		{
		std::string line;
		int buf_len = 15;
		char string_array[buf_len];
		char * buffer = string_array;
		
		if (config_file.is_open()) {std::cout << "\nERROR:Config file open before opening it!";} 

		config_file.open("alarm_clock_config.txt",std::ios::in);
		if (config_file.is_open()) 
			{
			std::cout << "\nConfig File Opened Sucessfully!";
			}
		else
			{
			std::cout << "\n Failed to open config file...";
			}
		

		//config_file.seekg(0, std::ios::beg);
/*		while ( ! config_file.eof() )
			{
			std::getline(config_file, line);
			std::cout << line << "..." << config_file.bad() << " ... \n";
			
			}
*/
		int next_alarm_position = 0;
		int day_number = 0;
		int alarm_day = 0;
		int alarm_hour = 0;
		int alarm_minute = 0;
		int alarm_second = 0;
		int n = 0;
		std::string temp_str = "";

		config_file.seekg(0); // goto beginning of file


		for (i=0; i<7; i++)  // 7 alarms, one for each day
			{
			//std::getline(config_file,line);		
			config_file.seekg(next_alarm_position);
			config_file.read(buffer,1);  // get day number
			alarm_day =  std::stoi(buffer);
			std::cout << "\nDay " << *buffer;	
			*buffer = 0x00;  
			

			config_file.read(buffer,1);  // this should be a space

			if (*buffer != 0x20) {std::cout << "\nError, no space after day numnber in alarm file";}
			else {std::cout << "\nSkipping space between day and hour";}

			// get the alarm hour	
			config_file.read(buffer,1);
			temp_str = "";
			std::cout << "\nHour ";
			while ( *buffer  != 0x3A) //get characters up to the colon
				{ 
				//std::cout << *buffer;
				temp_str = temp_str + *buffer;
				config_file.read(buffer,1);
				}	
			alarm_hour = std::stoi(temp_str);	
			std::cout << alarm_hour;
			*buffer = 0x00;	
			
			

			//get the alarm minute
			config_file.read(buffer,1);
			temp_str = "";
			std::cout << "\nMinute ";
			while (*buffer  != 0x3A ) //get characters up to the colon
				{ 
				//std::cout << *buffer;
				temp_str = temp_str + *buffer;
				config_file.read(buffer,1);
				}	
			alarm_minute = std::stoi(temp_str);
			std::cout << alarm_minute;
			*buffer = 0x00;

			//get the alarm second
			
			
			config_file.read(buffer,1);
			
			temp_str = "";
			

			std::cout << "\nSecond ";
		
					
			while (*buffer  != 0x0A ) //get characters up to the colon
				{ 
				//std::cout << *buffer;
				temp_str = temp_str + *buffer;
				config_file.read(buffer,1);
				}	
			
			alarm_second = std::stoi(temp_str);
			std::cout << alarm_second;
			*buffer = 0x00;

			


			//store alarm in daily_alarm array variable
			daily_alarm[alarm_day][0].tm_hour = alarm_hour;
			daily_alarm[alarm_day][0].tm_min = alarm_minute;
			daily_alarm[alarm_day][0].tm_sec = alarm_second;



			next_alarm_position = config_file.tellg();
			std::cout << "\n Next alarm string is at " << next_alarm_position;



			//std::cout << "\nGet file pointer posistion : " << config_file.tellg() << " - line text - " << line << std::endl;	
			}
		config_file.close();	


		return &daily_alarm[0][0];


		}




	
		tm * set_daily_alarm()
		{
		
			//config_file.open("alarm_clock_config.txt");		
			
			std::cout << "\nEnter Alarm for Sunday";
			
			set_alarm_time(&daily_alarm[0][0]);

			std::cout << "\nSunday Alarm is " <<  daily_alarm[0][0].tm_hour << ":" << daily_alarm[0][0].tm_min << ":" << daily_alarm[0][0].tm_sec << "\n";
			//config_file << "\nSunday " <<  daily_alarm[0][0].tm_hour << ":" << daily_alarm[0][0].tm_min << ":" << daily_alarm[0][0].tm_sec << "\n";



			std::cout << "\nEnter Alarm Time for Monday";
				

			set_alarm_time(&daily_alarm[1][0]);

			std::cout << "\nMonday Alarm is " <<  daily_alarm[1][0].tm_hour << ":" << daily_alarm[1][0].tm_min << ":" << daily_alarm[1][0].tm_sec << "\n";



			std::cout << "\nEnter Alarm Time for Tuesday";


			set_alarm_time(&daily_alarm[2][0]);

			std::cout << "\nTuesday Alarm is " <<  daily_alarm[2][0].tm_hour << ":" << daily_alarm[2][0].tm_min << ":" << daily_alarm[2][0].tm_sec << "\n";



			std::cout << "\nEnter Alarm Time for Wednesday";		
			set_alarm_time(&daily_alarm[3][0]);

			std::cout << "\nWednesday Alarm is " <<  daily_alarm[3][0].tm_hour << ":" << daily_alarm[3][0].tm_min << ":" << daily_alarm[3][0].tm_sec << "\n";


	

			std::cout << "\nEnter Alarm Time for Thursday";
			set_alarm_time(&daily_alarm[4][0]);

			std::cout << "\nThursday Alarm is " <<  daily_alarm[4][0].tm_hour << ":" << daily_alarm[4][0].tm_min << ":" << daily_alarm[4][0].tm_sec << "\n";


			std::cout << "\nEnter Alarm Time for Friday";
			set_alarm_time(&daily_alarm[5][0]);

			std::cout << "\nFriday Alarm is " <<  daily_alarm[5][0].tm_hour << ":" << daily_alarm[5][0].tm_min << ":" << daily_alarm[5][0].tm_sec << "\n";


			std::cout << "\nEnter Alarm Time for Saturday";


			set_alarm_time(&daily_alarm[6][0]);

			std::cout << "\nSaturday Alarm is " <<  daily_alarm[6][0].tm_hour << ":" << daily_alarm[6][0].tm_min << ":" << daily_alarm[6][0].tm_sec << "\n";

			save_daily_alarm_schedule();
			//config_file.close();
			
			return  &daily_alarm[0][0];



		}





	};




// instanciate object kerris_clock from class alarm_clock
alarm_clock kerris_clock;

//kerris_clock.set_alarm_time();


tm * daily_alarm_ptr = kerris_clock.read_daily_alarm_schedule();




// print current time
kerris_clock.print_current_time();
//set the alarm time
//kerris_clock.set_alarm_time();

//print out the current times in human readable format
//std::cout << "\nthe current time retuned by function time(0) is " << timer << " which is seconds since epoch Jan 1, 1970";
//std::cout << "\nThe current Hour is : " << now->tm_hour;
//std::cout << "\nThe current minute is : " << now->tm_min;
//std::cout << "\nThe current second is : " << now->tm_sec << "\n";

//std::cout << "\n " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";

//now print the tm structure into an ascii string
//std::cout << asctime(now);

while(1){
	kerris_clock.print_current_time();
//	kerris_clock.alarm_monitor();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	kerris_clock.alarm_monitor(daily_alarm_ptr);
	};





}  //main


