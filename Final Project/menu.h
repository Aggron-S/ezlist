#pragma once
#include <iostream>
#include <Windows.h>
#include <limits>					// 
#include "rlutil.h"
#include <ctime>
#include <fcntl.h>
#include <io.h>
#define WIN_WIDTH 110
#define WIN_HEIGHT 26
using namespace std;
bool renderNote = true;
int selOpt = 7, exiSelOpt = 33, montResTasks;
//CALENDAR//
time_t ttime = time(0);
tm* local_time = localtime(&ttime);
int year = 1900 + local_time->tm_year;								// changing in print Cal
int Year = 1900 + local_time->tm_year;									// printed year in vSTATS (const)
//Parameters//
int page = 1;
//			//
// SysMon //
time_t Ttime = time(0);
tm* Local_time = localtime(&Ttime);
int mon = Local_time->tm_mon;
string MONTHS[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };
//       //
//	SysDAY	//
time_t Time = time(0);
tm* LOCAL_TIME = localtime(&Time);
int day = LOCAL_TIME->tm_mday;			//day of the present month
//			//
// MAIN MENU //
int dueD_Idx = 0;
//			 //
void readDueD(int storageDue[], string storageTas[]) {				// Due Date for Main Menu(INC TASKS)
	int cnt = 0;
	ifstream gt("duedate.txt"), getTas("tasks.txt");
	if (!(gt) || !(getTas)) {				//Access File checker
		rlutil::locate(10, 24); cout << "Cannot find input file. Press any key to continue."; rlutil::getkey(); system("cls");
	}
	while (!(gt.eof() && getTas.eof())) {				// While not end of file, just get all elements in .txt
		gt >> storageDue[cnt];									// put all elements from .txt inside storage[]
		getline(getTas >> ws, storageTas[cnt]);
		cnt++;
	}
	for (cnt = dueD_Idx; cnt <= dueD_Idx; cnt++) {					//if press KEY LEFT/RIGHT in inputMain()
		
		if (storageDue[cnt] == (day + 2)) {					// 2 days before submission, print task	
			rlutil::locate(10, 25); cout << cnt + 1 << ". " << storageTas[cnt];	
		}
		else { rlutil::locate(10, 25); cout << cnt + 1 << ". No incoming task for this number."; }
	}
}
void readDueDt(int storDue[]) {						// Read only Due dates for SORT TASKS
	ifstream acq("duedate.txt");
	int incr = 0;
	if (!(acq)) {
		rlutil::locate(10, 24); cout << "Cannot read duedate.txt. Press any key to continue."; rlutil::getkey(); system("cls");
	}
	while (!(acq.eof())) {
		acq >> storDue[incr];
		incr++;
	}
}
void readFileInd(int& idx_No) {		// Show Idx_No
	ifstream get("idx.txt");
	get >> idx_No;
}
void Show(int Entries, string Arr[]) {			// Show Tasks
	int elem = 0;
	ifstream take("tasks.txt");
	if (!(take)) {
		rlutil::locate(10, 24); cout << "Cannot read tasks.txt. Press any key to continue."; rlutil::getkey(); system("cls");
	}
	while (!(take.eof())) {
		getline (take >> ws, Arr[elem]);
		elem++;
	}
	//-------------------------------------PRINT SAVED TASKS----------------------------------------//
	if (page == 1) {
		for (int i = 0; i < 16; i++) { rlutil::locate(10, i + 6); cout << i + 1 << ". " << Arr[i]; }
		for (int i = 16; i < 32; i++) { rlutil::locate(50, i - 10); cout << i + 1 << ". " << Arr[i]; }
	}
	else if (page == 2) {
		for (int i = 0; i < 16; i++) { rlutil::locate(10, i + 6); cout << i + 33 << ". " << Arr[i + 32]; }
		for (int i = 17; i < 33; i++) { rlutil::locate(50, i - 11); cout << i + 32 << ". " << Arr[i + 31]; }
	}
	else if (page == 3) {
		for (int i = 0; i < 16; i++) { rlutil::locate(10, i + 6); cout << i + 65 << ". " << Arr[i + 64]; }
		for (int i = 17; i < 33; i++) { rlutil::locate(50, i - 11); cout << i + 64 << ". " << Arr[i + 63]; }
	}
	else if (page == 4) {
		for (int i = 0; i < 4; i++) { rlutil::locate(10, i + 6); cout << i + 97 << ". " << Arr[i + 96]; }
	}
}
void clrScr(int num) {
	if (num == 1) {			//erase all excluding right menu
		for (int i = 0; i < WIN_HEIGHT; i++)		// - 7 if you don't want to erase INFO
		{
			for (int j = 0; j < WIN_WIDTH - 30; j++)
			{
				rlutil::locate(j + WIN_WIDTH - 105, i + WIN_HEIGHT - 23); cout << " ";
			}
		}
	}
	else if (num == 2) {							//clrscr excluding INFO
		for (int i = 0; i < WIN_HEIGHT - 9; i++) {
			for (int j = 0; j < WIN_WIDTH - 31; j++) {
				rlutil::locate(j + WIN_WIDTH - 105, i + WIN_HEIGHT - 21); cout << " ";
			}
		}
	}
	else if (num == 3) {			//Erase INFO Contents
		for (int i = 0; i < WIN_HEIGHT - 21; i++) {
			for (int j = 0; j < WIN_WIDTH - 36; j++) {
				rlutil::locate(j + WIN_WIDTH - 102, i + WIN_HEIGHT - 3); cout << " ";
			}
		}
	}
	else if (num == 4) {				//ERASE LEFT SCR PORTION (if user press ENTER while doing input)
		for (int i = 1; i <= 30; i++) {
			for (int j = 1; j <= 3; j++) { rlutil::locate(0 + j, 0 + i); cout << " "; }
		}
	}
	else if (num == 5) {					//Erase Incoming Tasks
		for (int i = 0; i < WIN_HEIGHT - 22; i++) {
			for (int j = 0; j < WIN_WIDTH - 62; j++) {
				rlutil::locate(j + WIN_WIDTH - 102, i + WIN_HEIGHT - 2); cout << " ";
			}
		}
	}
}
void clrOpt() {
	//-----------------------------------OPTIONS ERASE-------------------------------------//
	for (int i = 0; i < WIN_HEIGHT - 15; i++)
	{
		for (int j = 0; j < WIN_WIDTH - 85; j++)
		{
			rlutil::locate(j + WIN_WIDTH - 23, i + WIN_HEIGHT - 22); cout << " ";
		}
	}
	//-----------------------------------CONTROLS ERASE-------------------------------------//
	for (int i = 0; i < WIN_HEIGHT - 14; i++)
	{
		for (int j = 0; j < WIN_WIDTH - 85; j++)
		{
			rlutil::locate(j + WIN_WIDTH - 23, i + WIN_HEIGHT - 10); cout << " ";
		}
	}
}
void clrDialBox(int num) {		//Clear Dialogue Box Content
//-----------------------------------------Clear Content---------------------------------------------------//
	if (num == 1) {
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 41; j++)
			{
				rlutil::locate(j + 26, i + 12); cout << " ";
			}
		}
	}
	//-----------------------------------------Clear Whole Box---------------------------------------------------//
	else if (num == 2) {
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 43; j++)
			{
				rlutil::locate(j + 26, i + 12); cout << ".";
			}
		}
	}
}
void mainMenu(int num) {
	if (num == 1) {
		(void)_setmode(_fileno(stdout), _O_TEXT);
//================================================  EOM RESET TASKS NOTIF  ==============================================================//
	
	//----------------------------------------JAN, MAR, MAY, JUL, AUG, OCT, DEC------------------------------------------------------------//
		if (mon % 2 == 0 && (mon != 8 && mon != 10) || (mon == 7 || mon == 9 || mon == 11)) {			// months with 31 days
			if (renderNote && day == 30) {						// 2 Days b4 Month End RESET MSG
				clrScr(1);
				rlutil::setColor(12); rlutil::locate(WIN_WIDTH - 66, WIN_HEIGHT - 22); cout << "NOTE"; rlutil::resetColor();
				rlutil::setColor(14);
				rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 18); cout << "Tomorrow is LAST DAY of the month. You need to accomplish all TASKS before";
				rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "month ends. The system will automatically RESET its settings to DEFAULT and";
				rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 16); cout << " DELETES all Saved Tasks. Press ANY KEY to go back to Main Menu."; rlutil::getkey(); clrScr(1);
				
				renderNote = false; rlutil::resetColor();
			}
		//--------------------------------RESET TASKS LOGIC---------------------------------//
			if (day <= 31 && day != 1) {			// Starting DAY 2, it will output '1' (Logic in reset.txt) to avoid not reset funct when user doesn't open app for a long time
				montResTasks = 1;
				ofstream resetTask_Out("reset.txt");
				resetTask_Out << montResTasks; resetTask_Out.close();
			}
			ifstream inpt_ResTas_Log("reset.txt");
			inpt_ResTas_Log >> montResTasks;

			if (day == 1 && (montResTasks == 1)) {				// reset Tasks every first day of month "montResTasks = 1"
				ofstream output("tasks.txt"), dueD_Out("duedate.txt"), idx_Out("idx.txt"), reset_Out ("reset.txt"), heh("tas_stat.txt");
				output.open("tasks.txt", ofstream::out | ofstream::trunc); output.close();
				dueD_Out.open("duedate.txt", ofstream::out | ofstream::trunc); dueD_Out.close();
				for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();				// reset TASKS STATUS (D - DONE)

			//----------------------------RESET ALL IF JANUARY 1------------------------------//
				if (mon == 0) {
					ofstream  hehe("stats.txt"), heh("tas_stat.txt");
					for (int j = 0; j < 12; j++) { hehe << "0" << endl; } hehe.close();				// reset stats
					for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();				// reset TASKS STATUS (D - DONE)
				}
				idx_Out << 0; reset_Out << 0;				// reset tasks only ONCE every first day of month and back to reset_Out = 0 :)
			}
		
		}

	//------------------------------------------------APR, JUNE, SEPT, NOV----------------------------------------------------------------//
		else if ((mon % 2 != 0 || (mon == 8 || mon == 10)) && (mon != 1 && mon != 7 && mon != 9 && mon != 11)) {	// months with 30 days
			if (renderNote && day == 29) {							// 2 Days b4 Month End RESET MSG
				clrScr(1);
				rlutil::setColor(12); rlutil::locate(WIN_WIDTH - 66, WIN_HEIGHT - 22); cout << "NOTE"; rlutil::resetColor();
				rlutil::setColor(14);
				rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 18); cout << "Tomorrow is LAST DAY of the month. You need to accomplish all TASKS before";
				rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "month ends. The system will automatically RESET its settings to DEFAULT and";
				rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 16); cout << " DELETES all Saved Tasks. Press ANY KEY to go back to Main Menu."; rlutil::getkey(); clrScr(1);
				renderNote = false; rlutil::resetColor();
			}
			//--------------------------------RESET TASKS LOGIC---------------------------------//
			if (day <= 30 && day != 1) {				// Starting DAY 2, it will output '1' (Logic in reset.txt) to avoid not reset funct when user doesn't open app for a long time
				montResTasks = 1;
				ofstream resetTask_Out("reset.txt");
				resetTask_Out << montResTasks; resetTask_Out.close();
			}
			ifstream inpt_ResTas_Log("reset.txt");
			inpt_ResTas_Log >> montResTasks;

			if (day == 1 && (montResTasks == 1)) {				// reset Tasks every first day of month "montResTasks = 1"
				ofstream output("tasks.txt"), dueD_Out("duedate.txt"), idx_Out("idx.txt"), reset_Out("reset.txt"), heh("tas_stat.txt");
				output.open("tasks.txt", ofstream::out | ofstream::trunc); output.close();
				dueD_Out.open("duedate.txt", ofstream::out | ofstream::trunc); dueD_Out.close();
				for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();				// reset TASKS STATUS (D - DONE)
				idx_Out << 0; reset_Out << 0;						// reset tasks only ONCE every first day of month and back to reset_Out = 0 :)
			}
		}

	//-----------------------------------------------------FEBRUARY----------------------------------------------------------------//
		else if (mon == 1) {
			if (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0)) {			// if Leap Year
				if (renderNote && day == 28) {		// 2 Days b4 Month End RESET MSG
					clrScr(1);
					rlutil::setColor(12); rlutil::locate(WIN_WIDTH - 66, WIN_HEIGHT - 22); cout << "NOTE"; rlutil::resetColor();
					rlutil::setColor(14);
					rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 18); cout << "Tomorrow is LAST DAY of the month. You need to accomplish all TASKS before";
					rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "month ends. The system will automatically RESET its settings to DEFAULT and";
					rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 16); cout << " DELETES all Saved Tasks. Press ANY KEY to go back to Main Menu."; rlutil::getkey(); clrScr(1);
					renderNote = false; rlutil::resetColor();
				}
				//--------------------------------RESET TASKS LOGIC (Leap Year)---------------------------------//
				if (day <= 29 && day != 1) {				// Starting DAY 2, it will output '1' (Logic in reset.txt) to avoid not reset funct when user doesn't open app for a long time
					montResTasks = 1;
					ofstream resetTask_Out("reset.txt");
					resetTask_Out << montResTasks; resetTask_Out.close();
				}
				ifstream inpt_ResTas_Log("reset.txt");	inpt_ResTas_Log >> montResTasks;

				if (day == 1 && (montResTasks == 1)) {				// reset Tasks every first day of month
					ofstream output("tasks.txt"), dueD_Out("duedate.txt"), idx_Out("idx.txt"), reset_Out("reset.txt"), heh("tas_stat.txt");
					output.open("tasks.txt", ofstream::out | ofstream::trunc); output.close();
					dueD_Out.open("duedate.txt", ofstream::out | ofstream::trunc); dueD_Out.close();
					for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();				// reset TASKS STATUS (D - DONE)
					idx_Out << 0; reset_Out << 0;						// reset tasks only ONCE every first day of month and back to reset_Out = 0 :)
				}
			}
			else {		// if not Leap Year
				if (renderNote && day == 27) {		// 2 Days b4 Month End RESET MSG
					clrScr(1);
					rlutil::setColor(12); rlutil::locate(WIN_WIDTH - 66, WIN_HEIGHT - 22); cout << "NOTE"; rlutil::resetColor();
					rlutil::setColor(14);
					rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 18); cout << "Tomorrow is LAST DAY of the month. You need to accomplish all TASKS before";
					rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "month ends. The system will automatically RESET its settings to DEFAULT and";
					rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 16); cout << " DELETES all Saved Tasks. Press ANY KEY to go back to Main Menu."; rlutil::getkey(); clrScr(1);
					renderNote = false; rlutil::resetColor();
				}
				//-------------------------------------RESET TASKS LOGIC (Not Leap Year)-----------------------------------------------//
				if (day <= 28 && day != 1) {							// Starting DAY 2, it will output '1' (Logic in reset.txt) to avoid not reset funct when user doesn't open app for a long time
					montResTasks = 1;
					ofstream resetTask_Out("reset.txt");
					resetTask_Out << montResTasks; resetTask_Out.close();
				}
				ifstream inpt_ResTas_Log("reset.txt");	inpt_ResTas_Log >> montResTasks;

				if (day == 1 && (montResTasks == 1)) {				// reset Tasks every first day of month "montResTasks = 1"
					ofstream output("tasks.txt"), dueD_Out("duedate.txt"), idx_Out("idx.txt"), reset_Out("reset.txt"), heh("tas_stat.txt");
					output.open("tasks.txt", ofstream::out | ofstream::trunc); output.close();
					dueD_Out.open("duedate.txt", ofstream::out | ofstream::trunc); dueD_Out.close();
					for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();				// reset TASKS STATUS (D - DONE)
					idx_Out << 0; reset_Out << 0;						// reset tasks only ONCE every first day of month and back to reset_Out = 0 :)
				}
			}
		}
//=========================================================================================================================================//

//==============================================  New Year Greetings/ RESET ALL ===========================================================//
		if (renderNote && (mon == 0 && day == 1)) {	
			clrScr(1);
			rlutil::setColor(11); rlutil::locate(WIN_WIDTH - 72, WIN_HEIGHT - 22); cout << "Happy New Year!"; rlutil::resetColor();
			rlutil::setColor(14);																												//
			rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 18); cout << "On this New Year, may you change your direction and not dates, change your";
			rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "commitments and not the calendar, change your attitude and not the actions,";
			rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 16); cout << "and bring about a change in your faith, your force, and your focus and not";
			rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 15); cout << "the fruit. May you live up to the promises you have made and may you create";
			rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 14); cout << "for you and your loved ones the happiest New Year ever."; rlutil::getkey(); clrScr(1);
			renderNote = false; rlutil::resetColor();
		}
//=========================================================================================================================================//
	
		rlutil::setColor(14);
		//-----------------------------------------EZLIST------------------------------------------------------//
			//-----------------------E------------------------------------//
		for (int i = 0; i < 6; i++) { rlutil::locate(WIN_WIDTH - 100 + i, WIN_HEIGHT - 22); cout << "±±"; }
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 100, WIN_HEIGHT - 22 + i); cout << "±±"; }
		for (int i = 0; i < 5; i++) { rlutil::locate(WIN_WIDTH - 99 + i, WIN_HEIGHT - 20); cout << "±±"; }
		for (int i = 0; i < 6; i++) { rlutil::locate(WIN_WIDTH - 100 + i, WIN_HEIGHT - 18); cout << "±±"; }
		//-----------------------Z------------------------------------//
		for (int i = 0; i < 6; i++) { rlutil::locate(WIN_WIDTH - 88 + i, WIN_HEIGHT - 22); cout << "±±"; }
		rlutil::locate(WIN_WIDTH - 83, WIN_HEIGHT - 21); cout << "±±";
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 86 + i, WIN_HEIGHT - 20); cout << "±±"; }
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 88, WIN_HEIGHT - 19 + i); cout << "±±"; }
		for (int i = 0; i < 5; i++) { rlutil::locate(WIN_WIDTH - 87 + i, WIN_HEIGHT - 18); cout << "±±"; }
		//-----------------------L------------------------------------//
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 76 + i, WIN_HEIGHT - 22); cout << "±±"; }
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 76, WIN_HEIGHT - 21 + i); cout << "±±±"; }
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 73 + i, WIN_HEIGHT - 18); cout << "±±"; }
		//-----------------------I------------------------------------//
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 62 + i, WIN_HEIGHT - 22); cout << "±±"; }
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 62, WIN_HEIGHT - 21 + i); cout << "±±±"; }
		//-----------------------S------------------------------------//
		for (int i = 0; i < 6; i++) { rlutil::locate(WIN_WIDTH - 52 + i, WIN_HEIGHT - 22); cout << "±±"; }
		rlutil::locate(WIN_WIDTH - 53, WIN_HEIGHT - 21); cout << "±±±";
		for (int i = 0; i < 5; i++) { rlutil::locate(WIN_WIDTH - 52 + i, WIN_HEIGHT - 20); cout << "±±±"; }
		rlutil::locate(WIN_WIDTH - 47, WIN_HEIGHT - 19); cout << "±±±";
		for (int i = 0; i < 5; i++) { rlutil::locate(WIN_WIDTH - 53 + i, WIN_HEIGHT - 18); cout << "±±±"; }
		//-----------------------T------------------------------------//
		for (int i = 0; i < 8; i++) { rlutil::locate(WIN_WIDTH - 40 + i, WIN_HEIGHT - 22); cout << "±±"; }
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 37, WIN_HEIGHT - 21 + i); cout << "±±±"; }
		rlutil::resetColor();

		//--------------------------------------Title Border----------------------------------------------------//
		rlutil::setColor(11);
		//-----------------------E------------------------------------//
		rlutil::locate(WIN_WIDTH - 93, WIN_HEIGHT - 22); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 92, WIN_HEIGHT - 21); cout << (char)0xD9;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 96 + i, WIN_HEIGHT - 21); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 97, WIN_HEIGHT - 21); cout << (char)0xDa;
		rlutil::locate(WIN_WIDTH - 93, WIN_HEIGHT - 20); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 92, WIN_HEIGHT - 19); cout << (char)0xB3;
		rlutil::locate(WIN_WIDTH - 92, WIN_HEIGHT - 19); cout << (char)0xD9;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 96 + i, WIN_HEIGHT - 19); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 97, WIN_HEIGHT - 19); cout << (char)0xDa;
		rlutil::locate(WIN_WIDTH - 93, WIN_HEIGHT - 18); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 92, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 7; i++) { rlutil::locate(WIN_WIDTH - 99 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 100, WIN_HEIGHT - 17); cout << (char)0xC0;
		//-----------------------Z------------------------------------//
		rlutil::locate(WIN_WIDTH - 81, WIN_HEIGHT - 22); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 80, WIN_HEIGHT - 21); cout << (char)0xB3;
		rlutil::locate(WIN_WIDTH - 80, WIN_HEIGHT - 20); cout << (char)0xD9;
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 82 + i, WIN_HEIGHT - 20); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 82, WIN_HEIGHT - 20); cout << (char)0xDa;
		rlutil::locate(WIN_WIDTH - 82, WIN_HEIGHT - 19); cout << (char)0xD9;
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 84 + i, WIN_HEIGHT - 19); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 85, WIN_HEIGHT - 19); cout << (char)0xDa;

		rlutil::locate(WIN_WIDTH - 81, WIN_HEIGHT - 18); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 80, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 7; i++) { rlutil::locate(WIN_WIDTH - 87 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 88, WIN_HEIGHT - 17); cout << (char)0xC0;

		rlutil::locate(WIN_WIDTH - 88, WIN_HEIGHT - 21); cout << (char)0xC0;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 87 + i, WIN_HEIGHT - 21); cout << (char)0xC4; }
		//-----------------------L------------------------------------//
		rlutil::locate(WIN_WIDTH - 73, WIN_HEIGHT - 22); cout << (char)0xC4;
		rlutil::locate(WIN_WIDTH - 72, WIN_HEIGHT - 22); cout << (char)0xBF;
		for (int i = 0; i < 3; i++) { rlutil::locate(WIN_WIDTH - 72, WIN_HEIGHT - 21 + i); cout << (char)0xB3; }

		rlutil::locate(WIN_WIDTH - 68, WIN_HEIGHT - 18); cout << (char)0xC4;
		cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 67, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 8; i++) { rlutil::locate(WIN_WIDTH - 75 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 76, WIN_HEIGHT - 17); cout << (char)0xC0;
		//-----------------------I------------------------------------//
		rlutil::locate(WIN_WIDTH - 59, WIN_HEIGHT - 22); cout << (char)0xC4;
		rlutil::locate(WIN_WIDTH - 58, WIN_HEIGHT - 22); cout << (char)0xBF;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 58, WIN_HEIGHT - 21 + i); cout << (char)0xB3; }
		rlutil::locate(WIN_WIDTH - 58, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 3; i++) { rlutil::locate(WIN_WIDTH - 61 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 62, WIN_HEIGHT - 17); cout << (char)0xC0;
		//-----------------------S------------------------------------//
		rlutil::locate(WIN_WIDTH - 45, WIN_HEIGHT - 22); cout << (char)0xC4;
		rlutil::locate(WIN_WIDTH - 44, WIN_HEIGHT - 22); cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 44, WIN_HEIGHT - 21); cout << (char)0xD9;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 48 + i, WIN_HEIGHT - 21); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 49, WIN_HEIGHT - 21); cout << (char)0xDa;
		rlutil::locate(WIN_WIDTH - 45, WIN_HEIGHT - 20); cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 53, WIN_HEIGHT - 20); cout << (char)0xC0;

		rlutil::locate(WIN_WIDTH - 44, WIN_HEIGHT - 19); cout << (char)0xC4;
		rlutil::locate(WIN_WIDTH - 44, WIN_HEIGHT - 19); cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 44, WIN_HEIGHT - 18); cout << (char)0xD9;

		rlutil::locate(WIN_WIDTH - 45, WIN_HEIGHT - 18);  cout << (char)0xDa;

		rlutil::locate(WIN_WIDTH - 45, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 6; i++) { rlutil::locate(WIN_WIDTH - 51 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 52, WIN_HEIGHT - 17); cout << (char)0xC0;

		rlutil::locate(WIN_WIDTH - 52, WIN_HEIGHT - 19); cout << (char)0xC0;
		for (int i = 0; i < 4; i++) { rlutil::locate(WIN_WIDTH - 51 + i, WIN_HEIGHT - 19); cout << (char)0xC4; }
		//-----------------------T------------------------------------//
		rlutil::locate(WIN_WIDTH - 31, WIN_HEIGHT - 22); cout << (char)0xC4;
		rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 22); cout << (char)0xBF;
		rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 21); cout << (char)0xD9;
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 32 + i, WIN_HEIGHT - 21); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 33, WIN_HEIGHT - 21); cout << (char)0xDa;
		for (int i = 0; i < 3; i++) { rlutil::locate(WIN_WIDTH - 33, WIN_HEIGHT - 20 + i); cout << (char)0xB3; }
		rlutil::locate(WIN_WIDTH - 33, WIN_HEIGHT - 17); cout << (char)0xD9;
		for (int i = 0; i < 3; i++) { rlutil::locate(WIN_WIDTH - 36 + i, WIN_HEIGHT - 17); cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 37, WIN_HEIGHT - 17); cout << (char)0xC0;


		rlutil::locate(WIN_WIDTH - 40, WIN_HEIGHT - 21); cout << (char)0xC0;
		for (int i = 0; i < 2; i++) { rlutil::locate(WIN_WIDTH - 39 + i, WIN_HEIGHT - 21); cout << (char)0xC4; }
		rlutil::resetColor();
		//-------------------------------------------------------------------------------------------------------//
		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 14, 5); cout << "OPTIONS";
		rlutil::resetColor();

		//Navigate Options//
		rlutil::setColor(14);
		rlutil::locate(WIN_WIDTH - 18, selOpt); cout << "*";
		rlutil::locate(WIN_WIDTH - 18, selOpt - 1); cout << " ";
		rlutil::locate(WIN_WIDTH - 18, selOpt + 1); cout << " ";
		rlutil::resetColor();
		//---------------//
		rlutil::setColor(11);
		rlutil::locate(WIN_WIDTH - 15, 7); cout << "OVERVIEW";
		rlutil::locate(WIN_WIDTH - 15, 8); cout << "ADD TASKS";
		rlutil::locate(WIN_WIDTH - 16, 9); cout << "VIEW TASKS";
		rlutil::locate(WIN_WIDTH - 16, 10); cout << "VIEW STATS";
		rlutil::locate(WIN_WIDTH - 15, 11); cout << "CALENDAR";
		rlutil::resetColor();

		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 14, WIN_HEIGHT - 9); cout << "CONTROLS";
		rlutil::resetColor();

		rlutil::setColor(11);
		(void)_setmode(_fileno(stdout), _O_U16TEXT);
		rlutil::locate(WIN_WIDTH - 23, WIN_HEIGHT - 7); wprintf(L"↑ = Go Up");
		rlutil::locate(WIN_WIDTH - 23, WIN_HEIGHT - 6); wprintf(L"↓ = Go Down");
		(void)_setmode(_fileno(stdout), _O_TEXT);
		rlutil::locate(WIN_WIDTH - 23, WIN_HEIGHT - 5); cout << "ENTER = Select Option";
		rlutil::locate(WIN_WIDTH - 23, WIN_HEIGHT - 4); cout << "ESC = Go to Previous";
		rlutil::locate(WIN_WIDTH - 14, WIN_HEIGHT - 3); cout << "Menu";
		rlutil::resetColor();

	//-----------------------------------------RENDER TIME---------------------------------------------------//
		rlutil::setColor(14);
		//Current date/time based on current system
		time_t now = time(0);
		//convert now to string form
		char* dt = ctime(&now);
		rlutil::locate(64, 23); cout << "DATE & TIME";
		rlutil::locate(56, 25); cout << dt;
	//-----------------------------------------INCOMING TASKS---------------------------------------------------//
		if (mon % 2 == 0 && (mon != 8 && mon != 10) || (mon == 7 || mon == 9 || mon == 11)) {			// months w/ 31 days
			if (day <= 29) {
				rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + 2 << "] "; cout << "Use LEFT & RIGHT keys";
			}
			else if (day > 29) {
				rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + (31 - day) << "] "; cout << "Use LEFT & RIGHT keys";
			}
		}
		else if ((mon % 2 != 0 || (mon == 8 || mon == 10)) && (mon != 1 && mon != 7 && mon != 9 && mon != 11)) {	// months with 30 days
			if (day <= 28) {
				rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + 2 << "] "; cout << "Use LEFT & RIGHT keys";
			}
			else if (day > 28) {
				rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + (30 - day) << "] "; cout << "Use LEFT & RIGHT keys";
			}
		}
		//--------------------------FEBRUARY--------------------------------//
		else if (mon == 1) {
			if (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0)) {			// if Leap Year
				if (day <= 27) {
					rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + 2 << "] "; cout << "Use LEFT & RIGHT keys";
				}
				else if (day > 27) {
					rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + (29 - day) << "] "; cout << "Use LEFT & RIGHT keys";
				}
			}
			else {		// if not Leap Year
				if (day <= 26) {
					rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + 2 << "] "; cout << "Use LEFT & RIGHT keys";
				}
				else if (day > 26) {
					rlutil::locate(9, 23); cout << "INCOMING TASKS [" << MONTHS[mon] << " " << day + (28 - day) << "] "; cout << "Use LEFT & RIGHT keys";
				}
			}
		}
	//----------------------------------------------------------------------------------------------------------------------------//
		int storageDue[100]; string storageTas[100];
		readDueD(storageDue, storageTas);
		rlutil::resetColor();
	//------------------------------------WIDGETS--------------------------------------------//
		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 4);cout << (char)0xDa;
		for (int i = 0; i < 22; i++) { rlutil::locate(8 + i, 22); cout << (char)0xC4; }
		cout << (char)0xB3;
		rlutil::locate(33, 22); cout << "INFO";
		rlutil::locate(40, 22); cout << (char)0xB3;
		for (int i = 0; i < 41; i++) { rlutil::locate(41 + i, 22); cout << (char)0xC4; }
		cout << (char)0xBF;
		for (int i = 0; i < 5; i++) { rlutil::locate(7, 23 + i); cout << (char)0xB3; }
		rlutil::locate(7, 28); cout << (char)0xC0;
		for (int i = 0; i < 74; i++) { rlutil::locate(8 + i, 28); cout << (char)0xC4; }
		cout << (char)0xD9;
		for (int i = 0; i < 5; i++) { rlutil::locate(82, 23 + i); cout << (char)0xB3; }
		rlutil::resetColor();
	}
	else if (num == 2) {
		//----------------------------------Access Menu for Other Menu(Not Main M)--------------------------------------------//
		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 103, WIN_HEIGHT - 4);cout << (char)0xDa;
		for (int i = 0; i < 22; i++) { rlutil::locate(8 + i, 22); cout << (char)0xC4; }
		cout << (char)0xB3;
		rlutil::locate(33, 22); cout << "INFO";
		rlutil::locate(40, 22); cout << (char)0xB3;
		for (int i = 0; i < 41; i++) { rlutil::locate(41 + i, 22); cout << (char)0xC4; }
		cout << (char)0xBF;
		for (int i = 0; i < 5; i++) { rlutil::locate(7, 23 + i); cout << (char)0xB3; }
		rlutil::locate(7, 28); cout << (char)0xC0;
		for (int i = 0; i < 74; i++) { rlutil::locate(8 + i, 28); cout << (char)0xC4; }
		cout << (char)0xD9;
		for (int i = 0; i < 5; i++) { rlutil::locate(82, 23 + i); cout << (char)0xB3; }
		rlutil::resetColor();
	}
}
void dialBoxBord() {
	rlutil::locate(25, 11); cout << (char)0xDa;
	for (int i = 0; i < 42; i++) { rlutil::locate(i + 26, 11);	cout << (char)0xC4; }
	rlutil::locate(67, WIN_HEIGHT - 15);cout << (char)0xC4;
	rlutil::locate(68, WIN_HEIGHT - 15); cout << (char)0xBF;
	for (int i = 0; i < WIN_HEIGHT - 20; i++) { rlutil::locate(25, i + WIN_HEIGHT - 14);cout << (char)0xB3; } //Left Vertical Line

	for (int i = 0; i < WIN_HEIGHT - 20; i++) { rlutil::locate(68, i + WIN_HEIGHT - 14);cout << (char)0xB3; } //Right Vertical Line
	rlutil::locate(68, WIN_HEIGHT - 8);	cout << (char)0xD9;

	for (int i = 0; i < 42; i++) { rlutil::locate(i + 26, 18);	cout << (char)0xC4; }
	rlutil::locate(25, 18);	cout << (char)0xC0;
}
void dialBox(int num) {
	//-------------------------------------------Loading Box--------------------------------------------//
	if (num == 1) {
		dialBoxBord();
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Loading... ";
		for (int i = 0; i < 35; i++) { rlutil::locate(29 + i, WIN_HEIGHT - 11); Sleep(25); cout << "Ü"; }
		Sleep(500);
	}
	//-------------------------------------------Saved Box--------------------------------------------//
	else if (num == 2) {
		clrDialBox(1);
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Saved ";
		Sleep(1500);
	}
	//-------------------------------------------Not Saved Box--------------------------------------------//
	else if (num == 3) {
		dialBoxBord();
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Task was not Saved ";
		Sleep(1500);
	}
	//-------------------------------------------Delete Option Box--------------------------------------------//
	else if (num == 4) {
		clrDialBox(1);
		dialBoxBord();
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Deleted ";
		Sleep(1500);
	}
	//-------------------------------------------Press Any Key Option Box--------------------------------------------//
	else if (num == 5) {
		dialBoxBord();
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Press any key to continue ";
	}
	//----------------------------------------Exit Confirmation Option Box--------------------------------------------//
	else if (num == 6) {
		dialBoxBord();
		rlutil::locate(27, WIN_HEIGHT - 13); cout << "Do you want to exit?";
		rlutil::locate(35, WIN_HEIGHT - 10); cout << "Yes";
		rlutil::locate(56, WIN_HEIGHT - 10); cout << "No";
		//Navigate Options//
		rlutil::setColor(14);
		rlutil::locate(exiSelOpt, WIN_HEIGHT - 10); cout << "*";
		rlutil::locate(exiSelOpt - 21, WIN_HEIGHT - 10); cout << " ";
		rlutil::locate(exiSelOpt + 21, WIN_HEIGHT - 10); cout << " ";
		rlutil::resetColor();
	}
}
void Opt_ContrM(int num) {			//For Options and Control Menu Text Output
	if (num == 1) {
		rlutil::resetColor();
		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 14, 5); cout << "OPTIONS";
		rlutil::resetColor();
		//Navigate Options//
		rlutil::setColor(14);
		rlutil::locate(WIN_WIDTH - 20, selOpt); cout << "*";
		rlutil::locate(WIN_WIDTH - 20, selOpt - 1); cout << " ";
		rlutil::locate(WIN_WIDTH - 20, selOpt + 1); cout << " ";
		rlutil::resetColor();
	}
	else if (num == 2) {
		rlutil::setColor(12);
		rlutil::locate(WIN_WIDTH - 14, WIN_HEIGHT - 9); cout << "CONTROLS";
		rlutil::resetColor();
	}
}
void Over_VOpt() {
	rlutil::locate(WIN_WIDTH - 22, 8); cout << "Want to see lucky Donut?";
	rlutil::locate(WIN_WIDTH - 18, 9); cout << "Go to Next Page!";

	Opt_ContrM(2);
	rlutil::setColor(11);
	(void)_setmode(_fileno(stdout), _O_U8TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 7); wprintf(L"→ = Next Page");
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 6); wprintf(L"← = Previous Page");
	(void)_setmode(_fileno(stdout), _O_TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 4); cout << "ESC = Go to Main Menu";
	rlutil::resetColor();
}
void Input_MOpt() {
	Opt_ContrM(1);
	rlutil::setColor(11);
	rlutil::locate(WIN_WIDTH - 17, 7); cout << "1. ADD TASK";
	rlutil::locate(WIN_WIDTH - 17, 8); cout << "2. EXIT";
	rlutil::resetColor();
}
void View_TasOpt() {
	Opt_ContrM(1);
	rlutil::setColor(11);
	rlutil::locate(WIN_WIDTH - 16, 7); cout << "SORT TASKS";
	rlutil::locate(WIN_WIDTH - 16, 8); cout << "DELETE TASK";
	rlutil::locate(WIN_WIDTH - 18, 9); cout << "DELETE ALL TASKS";
	rlutil::locate(WIN_WIDTH - 17, 10); cout << "TASKS STATUS";
	rlutil::resetColor();
	Opt_ContrM(2);
	rlutil::setColor(11);
	(void)_setmode(_fileno(stdout), _O_U8TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 7); wprintf(L"→ = Next Page");
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 6); wprintf(L"← = Previous Page");
	(void)_setmode(_fileno(stdout), _O_TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 4); cout << "ESC = Go to Main Menu";
	rlutil::resetColor();
}
void View_StOpt() {
	Opt_ContrM(1);
	rlutil::setColor(11);
	rlutil::locate(WIN_WIDTH - 16, 7); cout << "NUMERIC VIEW";
	rlutil::resetColor();
	Opt_ContrM(2);
	rlutil::setColor(11);
	(void)_setmode(_fileno(stdout), _O_U8TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 7); wprintf(L"→ = Next Page");
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 6); wprintf(L"← = Previous Page");
	(void)_setmode(_fileno(stdout), _O_TEXT);
	rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 4); cout << "ESC = Go to Main Menu";
	rlutil::resetColor();
}
//------------------------------------------------------------------------------------------------------------//