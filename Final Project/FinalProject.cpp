﻿#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "rlutil.h"
//		D		//
#include <stdio.h>
#include <synchapi.h>
#include <math.h>
//		D		//
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include "menu.h"
using namespace std;
#define WIN_WIDTH 110
#define WIN_HEIGHT 26
int choose = 0, navigDate = 3;
unsigned int a = 0;		//Timer
// Input Menu	//
bool addTasks = false, removeTasks = false;
string tasks[100], savedTasks[100], title = "EZLIST";
int dySub, daySub[100], idx_No;					// day of submission for system month only
int delTask, max_Inp = 25;
//----------------//
string showDoneTas[100];		// MARK TASK
//STATS//
string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec" };
int monTasCompl[100], drawBar[100];
int ind_Label = 0, months_ind = mon;				// invalid reading if mon is directly thrown in months[] bug FIXED


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void fontsize(int x, int y) {							// Console Window Size Extended
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(console, 0, lpConsoleCurrentFontEx);
}
void drawBorder(int num) {
	if (num == 1) {
		// 1st top line and corners
		rlutil::setColor(13);
		(void)_setmode(_fileno(stdout), _O_TEXT);
		rlutil::locate(4, 2);	cout << (char)0xDa;
		for (int i = 0; i < WIN_WIDTH; i++) { rlutil::locate(i + WIN_WIDTH - 105, 2);	cout << (char)0xC4; }
		cout << (char)0xBF;
		cout << '\n';
		rlutil::setConsoleTitle(title);
		// vertical edges
		for (int i = 0; i < WIN_HEIGHT; i++) {
			rlutil::locate(4, i + WIN_HEIGHT - 23);	cout << (char)0xB3;
			rlutil::locate(WIN_WIDTH + 5, 3 + i);cout << (char)0xB3;
			cout << '\n';
		}
		// bottom line and corners
		rlutil::locate(4, WIN_HEIGHT + 3);	cout << (char)0xC0;
		for (int i = 0; i < WIN_WIDTH; i++) { rlutil::locate(i + WIN_WIDTH - 105, WIN_HEIGHT + 3);	cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH + 5, WIN_HEIGHT + 3);	cout << (char)0xD9;
		cout << '\n';
		rlutil::resetColor();
		//--------------------------------------RIGHT MENU------------------------------------------------------//
		rlutil::setColor(3);
		rlutil::locate(WIN_WIDTH - 25, 3); cout << (char)0xDa;
		for (int i = 0; i < WIN_WIDTH - 83; i++) { rlutil::locate(WIN_WIDTH - 24 + i, 3); cout << (char)0xC4; }
		cout << (char)0xBF;
		for (int i = 0; i < WIN_HEIGHT - 2; i++) { rlutil::locate(WIN_WIDTH + 3, 4 + i); cout << (char)0xB3; }
		rlutil::locate(WIN_WIDTH + 3, 28); cout << (char)0xD9;
		for (int i = 0; i < WIN_WIDTH - 83; i++) { rlutil::locate(WIN_WIDTH - 24 + i, 28);cout << (char)0xC4; }
		rlutil::locate(WIN_WIDTH - 25, 28); cout << (char)0xC0;
		for (int i = 0; i < WIN_HEIGHT - 2; i++) { rlutil::locate(WIN_WIDTH - 25, 4 + i); cout << (char)0xB3; }
		//-----MID LINE-----//
		for (int i = 0; i < WIN_WIDTH - 83; i++) { rlutil::locate(i + WIN_WIDTH - 24, WIN_HEIGHT - 11); cout << (char)0xC4; }
		//-----------------------------------------------------------------------------------------------------------//
		rlutil::resetColor();
	}
}
void overView(int pg) {
	if (pg == 1) {
		rlutil::locate(WIN_WIDTH - 66, WIN_HEIGHT - 22); cout << "EZLIST";
		rlutil::setColor(8);
		rlutil::locate(64, WIN_HEIGHT + 1);
		(void)_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << setw(10) << "© 2021 by W.C & A.D";
		rlutil::resetColor();
		(void)_setmode(_fileno(stdout), _O_TEXT);
		rlutil::setColor(14);
		rlutil::locate(WIN_WIDTH - 99, WIN_HEIGHT - 18); cout << "EZLIST is a console-based app developed as a solution to task management";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 17); cout << "problem. It is free to use, with the goal of helping people to manage tasks";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 16); cout << "with ease and convenience. It has functional features where user can add,";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 15); cout << "edit and save tasks. It is also user-friendly because you can sort tasks";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 14); cout << "according to your preferences in a way which is more manageable for you. ";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 13); cout << "Progress can be tracked with the help of graph in \"ViewStats\" Menu. Monito";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 12); cout << "ring due dates made easy with the help of Calendar feature. With its easy-to";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 11); cout << "-use system, people can be now less worried about app usage complexity and em";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 10); cout << "powering lives as we are here to bring you this powerful yet simple console-";
		rlutil::locate(WIN_WIDTH - 102, WIN_HEIGHT - 9); cout << "based task tracking system.";
		rlutil::resetColor();
	}
	//--------------------------------------------DONUT------------------------------------------------------//
	else if (pg == 2) {
		mainMenu(2);
		float A = 0, B = 0;
		float i, j;
		int k;
		float z[1760];
		char b[1760];
		//----------------------------------------Timer-------------------------------------------------//
		for (int i = 0; i < 20; i++) { rlutil::locate(i + 3, 1); cout << "="; }
		rlutil::locate(11, 2); cout << "TIMER";
		for (int i = 0; i < 20; i++) { rlutil::locate(i + 3, 3); cout << "="; };
		rlutil::locate(2, 6); cout << "Before seeing the Lucky Donut, you must first set a time on how long you can be able to see it.";
		rlutil::locate(2, 8); cout << "[ NOTE: You cannot exit once you press ENTER unless you exit the whole console. Still continue? ]";
		rlutil::locate(2, 10); cout << "[ ENTER = Continue    ESC = Cancel ]";
		char op = rlutil::getkey();
		if (op == rlutil::KEY_ENTER) {		//Timer  / Donut will only function if key = ENTER
			rlutil::locate(2, 12); cout << "Enter Seconds [ MAX = 1 Hour(3600s) ]: ";
			rlutil::showcursor();
			while (!(cin >> a))		// (cin) - will still run while input is not integer
			{
				rlutil::hidecursor();
				rlutil::locate(12, 24);  rlutil::setColor(14); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
				//------------------------Erase Wrong Input------------------------------//
				for (int i = 0; i < 80; i++) { rlutil::locate(41 + i, 12); cout << " "; }
				for (int j = 0; j < 9; j++) {
					for (int k = 1; k <= 120; k++) { rlutil::locate(0 + k, 13 + j); cout << " "; }
				}
				rlutil::showcursor();
				cin.clear();				//Clear the error state
				rlutil::locate(41, 12); cin.ignore(1024, '\n');			//Discard all char in the stream (i just set up to 1024 chars to be ignored)
			}
			rlutil::hidecursor();
			a *= 10;			// Just to verify that INPUT time should not be less than 5s nor > 1hr(3600s)
			unsigned int h = 0, tl;
			h = a;			// 'h' will decrement instead of 'a' (timer)
			//-----------------------------------------DONUT LOGIC-------------------------------------------------//
			system("cls");
			while (1) {
				if (a >= 50 && a <= 36000) {			// Minimum of 5 sec & max of 1hr(3600s) INPUT : in int, 1hr(3600s) = 36000
					if (h > 10) {			// to counter its forever looping func, use timer :) (if h > 0sec)
						rlutil::setColor(11);
						rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 18); cout << "\" Do the hard tasks first. The easy";
						rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 17); cout << "tasks will take care of themselves.\"";
						rlutil::locate(WIN_WIDTH - 10, WIN_HEIGHT - 15); cout << "- Dale Carnegie";
						rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 10); cout << "\" Whenever you feel upset, just stare";
						rlutil::locate(WIN_WIDTH - 30, WIN_HEIGHT - 9); cout << "at me. ^_^ \"";
						rlutil::locate(WIN_WIDTH - 10, WIN_HEIGHT - 7); cout << "- Lucky Donut";
						rlutil::resetColor();
						memset(b, 32, 1760);
						memset(z, 0, 7040);
						for (j = 0; j < 6.28; j += 0.07) {
							for (i = 0; i < 6.28; i += 0.02) {
								float c = sin(i);
								float d = cos(j);
								float e = sin(A);
								float f = sin(j);
								float g = cos(A);
								float h = d + 2;
								float D = 1 / (c * h * e + f * g + 5);
								float l = cos(i);
								float m = cos(B);
								float n = sin(B);
								float t = c * h * g - f * e;
								int x = 40 + 30 * D * (l * h * m - t * n);
								int y = 12 + 15 * D * (l * h * n + t * m);
								int o = x + 80 * y;
								int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
								if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
									z[o] = D;
									b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
								}
							}
						}
						printf("\x1b[H");
						rlutil::setColor(14);
						for (k = 0; k < 1761; k++) {
							putchar(k % 80 ? b[k] : 10);
							A += 0.00004;
							B += 0.00002;
						}
						rlutil::resetColor();
						tl = h / 10;			// to have better (s) output
						rlutil::locate(30, 27); cout << "Time Remaining: " << tl;
						h--;
					}
					else {
						system("cls");
						rlutil::setColor(11);rlutil::locate(40, 14); cout << "[Time is over. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor();
						system("cls");
						break;
					}
				}
				else {
					system("cls");
					rlutil::setColor(14); rlutil::locate(18, 14); cout << "[Time(s) shall not be less than 5s or greater than 1hr(3600s). Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor();
					system("cls");
					break;
				}
			}
		}
		else if (op == rlutil::KEY_ESCAPE) { system("cls"); }
		else {
			system("cls");
			rlutil::setColor(14); rlutil::locate(40, 14); cout << "[Invalid Input. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor();
			system("cls");
		}
	}
}
void inputMenu() {
	//----------------------------------Input Menu Descrip Border-------------------------------------------//
	mainMenu(2);
	int numOfTasks;
	readFileInd(idx_No);	//Read Idx File
	//top line//
	rlutil::setColor(4);
	rlutil::locate(7, 6); cout << (char)0xDa;
	for (int i = 0; i < 72; i++) { rlutil::locate(i + WIN_WIDTH - 102, 6);	cout << (char)0xC4; }
	cout << (char)0xBF;
	//vertical lines//
	for (int i = 0; i < 2; i++) { rlutil::locate(7, i + 7);	cout << (char)0xB3;  rlutil::locate(80, i + 7);cout << (char)0xB3; }
	//bottom line//
	rlutil::locate(7, 9);	cout << (char)0xC0;
	for (int i = 0; i < 72; i++) { rlutil::locate(i + WIN_WIDTH - 102, 9);	cout << (char)0xC4; }
	rlutil::locate(80, 9);	cout << (char)0xD9;
	rlutil::resetColor();
	//--------------------------------------------------------------------------------------------------------------//
	rlutil::locate(WIN_WIDTH - 68, WIN_HEIGHT - 22); cout << "TASK MENU";
	rlutil::locate(9, 7); cout << "Welcome to TASK MENU. Here, you can add any tasks you want to add. You ";
	rlutil::locate(10, 8); cout << "can have a maximum input of 32 tasks. Select 'ADD TASK' to add a task.";
	if (addTasks && (idx_No >= 0 && idx_No <= 99)) {			//If tasks = 99, it can still add pero dapat 1 task n lng
		rlutil::showcursor();
		rlutil::locate(10, 11);	cout << "How many task do you like to Input? ";
		
		while (!(cin >> numOfTasks)) {						//While user input (cin) != to int it will continue to prompt user for input
			rlutil::hidecursor();
			rlutil::locate(12, 24); rlutil::setColor(14); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
			rlutil::locate(46, 11); cout << "                                      ";	// Erase every input in a line

			clrScr(4);					// Erase left scr portion (if user press ENTER while doing input)
			rlutil::showcursor();
			cin.clear();				//Clear the error state
			rlutil::locate(47, 11);	cin.ignore(1024, '\n');
		}
		if (numOfTasks >= 1 && numOfTasks <= 32) {			//numOfTasks( MIN = 1, MAX = 32 per set )
			if ((numOfTasks + idx_No) <= 100) {					//If input # of tasks + idx_No (idx.txt) <= 100, you can stil add a task
				rlutil::setColor(11); rlutil::locate(10, 13); cout << "[ You have Input " << numOfTasks << " tasks. Only '25' characters are accepted. ]"; rlutil::resetColor();
				rlutil::showcursor();
				rlutil::setColor(14); rlutil::locate(10, 15); cout << "Enter a task: "; rlutil::resetColor();
				for (int i = idx_No; i < numOfTasks + idx_No; i++) 
				{
				//---------------------------------INPUT ERASE WHEN CHAR > 25 BUG FIXED-------------------------------------//
					if (i < ((numOfTasks - 1) + idx_No)) {
						rlutil::locate(27, 15); cout << "                                                          ";
					}
				//---------------------------------------------------------------------------------------------------------//
					rlutil::locate(24, 15); cout << i + 1 << ". "; getline(cin >> ws, tasks[i]);	//whitespace error fixed (ws)
	
					if (i < ((numOfTasks - 1) + idx_No)) {
						rlutil::locate(27, 15); cout << "                                                          ";	// Erase every input in a line
					}
				//---------------------------------INPUT LENGTH CHECKER------------------------------------//
					while (!(tasks[i].length() <= 25)) {		// if input char length is greater than 25 gagana to
						rlutil::hidecursor();
				
						tasks[i].erase(tasks[i].begin(), tasks[i].end());
						rlutil::setColor(14); rlutil::locate(9, 24); cout << "Maximum no. of chars are '25'. Try again. Press any key to continue."; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
						rlutil::showcursor();
						//----------------------Cursor Pos Error in # 100 FIXED-------------------------//
						if (i == 99) { rlutil::locate(28, 15); cout << "                                                         "; rlutil::locate(29, 15); getline(cin >> ws, tasks[i]); }
						else { rlutil::locate(28, 15); getline(cin >> ws, tasks[i]); }		// rewrite tasks if exceed max '25' chars
					}
				}
			//--------------------------------------------TASKS TO BE INCLUDED-------------------------------------------------//
				clrScr(1); mainMenu(2);
				rlutil::locate(WIN_WIDTH - 71, WIN_HEIGHT - 22); cout << "TASKS TO BE INCLUDED";
				for (int i = idx_No; i < (numOfTasks + idx_No); i++) {
					if (i >= idx_No && i <= idx_No + 15) {						// Print Tasks to be Included
						rlutil::locate(10, 6 + (i - (idx_No))); cout << i + 1 << ". " << tasks[i];
					}
					else if (i >= (idx_No + 16) && i <= (idx_No + 32)) {
						rlutil::locate(50, 7 + (i - (idx_No + 17))); cout << i + 1 << ". " << tasks[i];
					}
				}
				for (int k = idx_No; k < numOfTasks + idx_No; k++) {
				//-----------------------------INPUT ERASE WHEN INPUT # ! <= 1 && >= 31  BUG FIXED-------------------------------------//
					if (k < (numOfTasks + idx_No)) {						 
						rlutil::locate(55, 24); cout << "                          ";
					}
				//---------------------------------------------------------------------------------------------------------------------//
				Inp_Due:
					rlutil::locate(12, 24); cout << "Enter due date [Day of current Month]: " << k + 1 << ".  ";
					
					while (!(cin >> dySub)) {		
						rlutil::hidecursor(); clrScr(3);
						rlutil::locate(12, 24);  rlutil::setColor(14); cout << " [Invalid Input. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor(); clrScr(3), clrScr(4);
						
						rlutil::showcursor(); rlutil::locate(12, 24); cout << "Enter due date [Day of current Month]: " << k + 1 << ".  ";
		
						cin.clear();
						rlutil::locate(55, 24); cin.ignore(1024, '\n');
					}
					if (dySub >= 1 && dySub <= 31) {		// CHECK IF INPUT DUE Day IS >= 1 AND <= 31 (min/ max days of month)
						daySub[k] = dySub;
					}
					else {
						rlutil::hidecursor();
						rlutil::locate(8, 24); rlutil::setColor(14); cout << " [Input numbers must be from 1-31. Try again. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor(); clrScr(3), clrScr(4);
						rlutil::showcursor(); goto Inp_Due;
					}
				}
				clrScr(3); rlutil::hidecursor();
			//----------------------------------------Saving Tasks-------------------------------------------------//
				rlutil::locate(9, 24); cout << "You need to save your Input.Pressing ENTER will automatically save your"; rlutil::locate(9, 25); cout << "tasks.Press ESC if you want to cancel.";
			SaveT_Opt:
				char op = rlutil::getkey();
				if (op == rlutil::KEY_ENTER) {
					clrScr(1); clrScr(3);
					clrOpt();
					dialBox(1);
					ofstream output("tasks.txt", ios::app), dueD_Out("duedate.txt", ios::app), idx_Out("idx.txt");			// save in a txt file//
					if (idx_No >= 0 && idx_No <= 100) {				//Only output values from 0 - 100 in idx.txt
						idx_Out << idx_No + numOfTasks;
					}
					for (int i = idx_No; i < numOfTasks + idx_No; i++) {
						savedTasks[i] = tasks[i];
						 output << savedTasks[i] << "\n";
						 dueD_Out << daySub[i] << "\n"; 
						
					}
					dialBox(2);  clrScr(1);  system("cls");
				}
				else if (op == rlutil::KEY_ESCAPE) {
					clrScr(1); clrScr(3);
					clrOpt();
					dialBox(3);
					clrScr(1); system("cls");
				}
				else {
					goto SaveT_Opt;
				}
			}
			else {			// To see how many Tasks User can Add
				system("cls"); rlutil::hidecursor();
				rlutil::setColor(11);rlutil::locate(34, 14); cout << "[ Only " << 100 - idx_No  << " task/s left to add. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor();
				system("cls");
			}
		}
		else {				// if number of Input Tasks > 32
			rlutil::hidecursor();
			rlutil::setColor(14); rlutil::locate(10, 24); cout << "[Minimum number of tasks is 1 and Maximum number is 32] "; Sleep(3000); rlutil::resetColor(); system("cls");
		}
	}
	else if (addTasks && (idx_No >= 100)) {			// if addTasks but tasks is already 100
		system("cls");
		rlutil::setColor(11);rlutil::locate(31, 14); cout << "[Maximum number of tasks \"100\" reached. Press any key to continue.]"; rlutil::getkey(); rlutil::resetColor();
		system("cls");
	}
	numOfTasks = 0; addTasks = false;
}

void viewTasks(int modTas) {
	mainMenu(2);
	rlutil::locate(WIN_WIDTH - 69, WIN_HEIGHT - 22); cout << "VIEW TASKS";
	readFileInd(idx_No);	//Read Idx File
	//------------------------------------------Access Txt File----------------------------------------------//
	int count = 100, getDueDATE[100]; string stor[100];
	if (idx_No != 0) {								// tasks can be viewed unless user deletes all tasks
		Show(count, stor); readDueDt(getDueDATE);
	}
	//------------------------------------------------------------------------------------------------------//
	for (int i = 0; i < count; i++) { tasks[i] = stor[i];}				// store tasks from tasks.txt inside tasks[i] 
	for (int j = 0; j < count; j++) { daySub[j] =  getDueDATE[j]; }			// store due dates from duedate.txt inside daySub[j]
	//----------------------------------------Sorting Tasks-------------------------------------------------//
	if (modTas == 1) {
		int num1, num2, TEMP; string temp;
		rlutil::showcursor();  rlutil::setColor(14);
		rlutil::locate(10, 24); cout << "Choose the number of task you want to change position: "; 
		while (!(cin >> num1)) {
			rlutil::hidecursor();
			rlutil::locate(12, 26); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::getkey(); clrScr(3);
			rlutil::locate(10, 24); cout << "Choose the number of task you want to change position: ";
			clrScr(4); rlutil::showcursor(); cin.clear();
			rlutil::locate(65, 24); cin.ignore(1024, '\n');
		}
		rlutil::locate(10, 25); cout << "Number " << num1 << " change to number: ";
		while (!(cin >> num2)) {
			clrScr(3); rlutil::hidecursor();
			rlutil::locate(12, 24); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::getkey(); clrScr(3);
			rlutil::locate(10, 25); cout << "Number " << num1 << " change to number: ";
			clrScr(4); rlutil::showcursor(); cin.clear();
			rlutil::locate(38, 25); cin.ignore(1024, '\n');
		}
		if ((num1 <= idx_No && num2 <= idx_No) && (num1 >= 1 && num2 >= 1)) {	// Sorting Task will func if this is true
			clrScr(3); rlutil::hidecursor();
			rlutil::locate(9, 24); cout << " Are you sure you want to save changes? Press ENTER to continue, ESC"; rlutil::locate(9, 25); cout << " to cancel.";
			char oper = rlutil::getkey();
			if (oper == rlutil::KEY_ENTER) {
				clrScr(2); clrScr(3);
			//----------SORT TASKS------------//
				temp = tasks[num1 - 1];
				tasks[num1 - 1] = tasks[num2 - 1];
				tasks[num2 - 1] = temp;
			//----------SORT DUE DATES------------//
				TEMP = daySub[num1 - 1];
				daySub[num1 - 1] = daySub[num2 - 1];
				daySub[num2 - 1] = TEMP;

				ofstream output("tasks.txt") , dueD_Out("duedate.txt");
				for (int i = 0; i < idx_No; i++) {
					savedTasks[i] = tasks[i];
					output << savedTasks[i] <<"\n";
					dueD_Out << daySub[i] << "\n";
				}
			}
			else if (oper == rlutil::KEY_ESCAPE) {
				clrScr(3); rlutil::locate(12, 24); cout << "[Operation cancelled]"; Sleep(2000); clrScr(3);
			}
		}
		else {
			clrScr(3); rlutil::hidecursor();
			rlutil::locate(10, 24); cout << "Input number range must be within the range of number of tasks. Press "; rlutil::locate(10, 25); cout << "any key to continue."; rlutil::getkey(); clrScr(1);
		
		}
			rlutil::resetColor();
	}
	//------------------------------------------Deleting Tasks--------------------------------------------------//
	else if (modTas == 2) {
		int k = 0;
		ifstream tas_StatuInpt("tas_stat.txt");				// MARK TASK DELETE 1
		while (!tas_StatuInpt.eof()) { getline(tas_StatuInpt, showDoneTas[k]); k++; } tas_StatuInpt.close();
		
		rlutil::locate(10, 24);	cout << "Choose the number of task you want to Delete: ";
		rlutil::showcursor();

		while (!(cin >> delTask)) {
			rlutil::hidecursor();
			rlutil::locate(12, 26); rlutil::setColor(14); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::resetColor(); rlutil::getkey(); clrScr(3);

			rlutil::locate(10, 24);	cout << "Choose the number of task you want to Delete: ";	// :) 
			clrScr(4); rlutil::showcursor();
			cin.clear();
			rlutil::locate(56, 24); cin.ignore(1024, '\n');
		}
		rlutil::hidecursor(); clrScr(3);
		rlutil::locate(10, 24);	cout << "Are you sure you want to Delete the Task? Press ENTER to continue, ESC "; rlutil::locate(10, 25); cout << "to cancel.";
		char ope = rlutil::getkey();
		if (ope == rlutil::KEY_ENTER) {
			if (delTask >= 1 && delTask <= idx_No) {					// To avoid user from putting negative, 0 or num > idx_No
				for (int i = delTask - 1; i <= (idx_No - 1); i++) {
					if (i <= idx_No - 2) {
						tasks[i] = tasks[i + 1]; daySub[i] = daySub[i + 1];
					}
				}
			//------------------------------------ MARK TASK DELETE 1 task LOGIC---------------------------------------//
				for (int j = delTask - 1; j <= 99; j++) {			
					if (j <= 100 - 2) { showDoneTas[j] = showDoneTas[j + 1]; }
					else if (j == 99) { showDoneTas[j] = " "; }
				}


				idx_No--;				//idx_No decreases evertime you deleted a Task
				ofstream output("tasks.txt"), idx_noOut ("idx.txt"), dueD_Out("duedate.txt"), tasStatus("tas_stat.txt");
				output.open("tasks.txt", ofstream::out | ofstream::trunc);	 output.close();	output.open("tasks.txt");									
				idx_noOut << idx_No;
				for (int i = 0; i < idx_No; i++) {
					savedTasks[i] = tasks[i];				
					output << savedTasks[i] << "\n";
					dueD_Out << daySub[i] << "\n";
				}
				for (int j = 0; j < 100; j++) {	tasStatus << showDoneTas[j] << endl; }			// MARK TASK PUTS modified array in txt file
				clrScr(1); dialBox(4); system("cls");
			}
			else { rlutil::setColor(14); rlutil::locate(8, 27); cout << "[Minimum number of task is 1 and Maximum is " << idx_No  <<" (number of tasks) tasks.] "; Sleep(3000); system("cls"); rlutil::resetColor(); }
		}
		else if (ope == rlutil::KEY_ESCAPE) { system("cls"); }
		else { clrScr(3); rlutil::setColor(14); rlutil::locate(12, 25); cout << "[Invalid Option. Press any key to continue.]"; rlutil::resetColor(); rlutil::getkey(); clrScr(3); }
	}
	//------------------------------------------Delete ALL TASKS--------------------------------------------------//
	else if (modTas == 3) {	
		clrScr(3);
		rlutil::locate(10, 24);	cout << "Are you sure you want to Delete All Tasks? Press ENTER to continue, ESC "; rlutil::locate(10, 25); cout << "to cancel.";
		char ope = rlutil::getkey();
		if (ope == rlutil::KEY_ENTER) {
			ofstream output("tasks.txt"), dueD_Out("duedate.txt"), ind_Out("idx.txt");

			output.open("tasks.txt", ofstream::out | ofstream::trunc);	output.close();		//open tasks.txt & clear contents
			dueD_Out.open("duedate.txt", ofstream::out | ofstream::trunc); 	dueD_Out.close();	//open duedate.txt & clear contents
			idx_No = 0; ind_Out << idx_No;										//reset idx_No so user can add tasks again :)
		//--------------------------CLEAR ALL TASK STATUS OUTPUT (D - DONE)------------------------------//
			ofstream heh("tas_stat.txt"); for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();
			clrScr(1); dialBox(1); dialBox(4); clrScr(1);
		}
		else if (ope == rlutil::KEY_ESCAPE) { clrScr(1); }
		else { clrScr(3); rlutil::setColor(14); rlutil::locate(12, 25); cout << "[Invalid Option. Press any key to continue.]"; rlutil::resetColor(); rlutil::getkey(); clrScr(3); }
	}
	//-----------------------------------------------TASKS STATUS--------------------------------------------------------//
	else if (modTas == 4) {
	int num1, k = 0, s = 0; bool markTas = false;
		selOpt = 7; clrOpt(); page = 1;
	//-------------------------------RESET AND WHITE SPACE RECOVERY LOGIC IN TXT FILES------------------------------------------//
		/* NOTE : COMMENT ONE LINE IF YOU WANT TO PRINT WS OR 0 IN OTHER TXT FILE, OR ELSE IT WILL NOT WORK */
		//ofstream heh("tas_stat.txt"); for (int i = 0; i < 100; i++) { heh << " " << endl; } heh.close();    // WHITE SPACE ADDING LOGIC (ONLY IF USER ACCIDENTALLY ERASES WS CONTENT IN tas_stat.txt)
		//ofstream hehe("stats.txt"); for (int j = 0; j < 12; j++) { hehe << "0" << endl; } hehe.close();	  // Number "0" ADDING LOGIC (ONLY IF USER ACCIDENTALLY ERASES # "0" CONTENT IN stats.txt) 
	//-----------------------------------------------------------------------------------------------------------------//
		ifstream input("stats.txt"), tas_StatuInpt("tas_stat.txt");
		while (!input.eof()) { input >> monTasCompl[s];					s++;	/* 's' up to 11 only*/	} // store elem from stats.txt into array
		while (!tas_StatuInpt.eof()) { getline(tas_StatuInpt, showDoneTas[k]);	 k++;	/* 'k' up to 99 only*/ }  // store elem from tas_stat.txt into array
		input.close(); tas_StatuInpt.close();
	
		rlutil::locate(WIN_WIDTH - 70, WIN_HEIGHT - 22); cout << "TASKS STATUS";
		rlutil::setColor(11); rlutil::locate(WIN_WIDTH - 15, 7); cout << "MARK TASK"; rlutil::resetColor();
		rlutil::setColor(12); rlutil::locate(WIN_WIDTH - 18, 10); cout << "MARKING REFERENCE"; rlutil::resetColor();
		rlutil::setColor(10); rlutil::locate(WIN_WIDTH - 14, 12); cout << "D"; rlutil::resetColor();	rlutil::setColor(14); rlutil::locate(WIN_WIDTH - 12, 12); cout << "- Done"; rlutil::resetColor();
	//------------------------CONTROLS MENU-------------------------------//
		rlutil::setColor(11);
		(void)_setmode(_fileno(stdout), _O_U8TEXT);
		rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 7); wprintf(L"→ = Next Page");
		rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 6); wprintf(L"← = Previous Page");
		(void)_setmode(_fileno(stdout), _O_TEXT);
		rlutil::locate(WIN_WIDTH - 21, WIN_HEIGHT - 4); cout << "ESC = Go to Previous"; rlutil::locate(WIN_WIDTH - 15, WIN_HEIGHT - 3); cout << "Menu";
		rlutil::resetColor();
	//---------------------------------MARK TASK-------------------------------------//
	Mar_Tas:
		if (markTas) {
			rlutil::showcursor(); rlutil::locate(10, 24); cout << "Choose the number of task you want to mark: ";
			while (!(cin >> num1)) {
				rlutil::hidecursor();
				rlutil::locate(12, 26); cout << " [Invalid Input. Use numbers only. Press any key to continue.]"; rlutil::getkey(); clrScr(3);
				rlutil::locate(10, 24); cout << "Choose the number of task you want to mark: ";
				clrScr(4); rlutil::showcursor(); cin.clear();
				rlutil::locate(54, 24); cin.ignore(1024, '\n');
			}
			rlutil::hidecursor(); clrScr(3);
			if (num1 <= idx_No && num1 >= 1) {			// User can't mark tasks unless input is >= 1 and <= idx_No
				rlutil::locate(10, 24);	cout << "Are you sure you want to MARK task as done? Press ENTER to continue,"; rlutil::locate(10, 25); cout << " ESC to cancel.";
				char op = rlutil::getkey();
				if (op == rlutil::KEY_ENTER) {
					clrScr(3);

					if (page == 1) {
						if (num1 >= 1 && num1 <= 16) { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}

						else if (num1 >= 17 && num1 <= 32) { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else {
							rlutil::setColor(14); rlutil::locate(9, 24); cout << "Go to NEXT or PREVIOUS Page if you want to mark numbers that are not in";
							rlutil::locate(9, 25); cout << "this page. Press any key to continue."; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
						}	clrScr(4);
					}

					else if (page == 2) {
						if (num1 >= 33 && num1 <= 48) { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else if (num1 >= 49 && num1 <= 64) { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else {
							rlutil::setColor(14); rlutil::locate(9, 24); cout << "Go to NEXT or PREVIOUS Page if you want to mark numbers that are not in";
							rlutil::locate(9, 25); cout << "this page. Press any key to continue."; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
						}	clrScr(4);
					}
							
					else if (page == 3) {
						if (num1 >= 65 && num1 <= 80)  { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else if (num1 >= 81 && num1 <= 96) { rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
						//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else {
							rlutil::setColor(14); rlutil::locate(9, 24); cout << "Go to NEXT or PREVIOUS Page if you want to mark numbers that are not in";
							rlutil::locate(9, 25); cout << "this page. Press any key to continue."; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
						}	clrScr(4);
					}

					else if (page == 4) {
						if (num1 >= 97 && num1 <= 100) {
							rlutil::setColor(14); rlutil::locate(10, 24); cout << "Number " << num1 << " marked as DONE. Press any key to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);
							ofstream output("stats.txt"), tas_statuOut("tas_stat.txt");
							//--------------------------------TASK STATUS OUTPUT( D - DONE)----------------------------------//
							for (int y = 0; y < (k - 1); y++) {
								if (y == num1 - 1) { showDoneTas[y] = 'D'; tas_statuOut << showDoneTas[y] << endl; }
								else if (y != num1 - 1) { tas_statuOut << showDoneTas[y] << endl; }
							}
							//-----------------------------------INCREMENT STATS BY ONE (IF TASK MARKED AS DONE)------------------------------------------------//
							for (int x = 0; x < (s - 1); x++) {
								if (x == mon) { monTasCompl[x] += 1; output << monTasCompl[x] << endl; }	// monTasCompl +1
								else if (x != mon) { output << monTasCompl[x] << endl; }	// The rest, not changed
							} output.close();	clrScr(4);
						}
						else {
							rlutil::setColor(14); rlutil::locate(9, 24); cout << "Go to NEXT or PREVIOUS Page if you want to mark numbers that are not in";
							rlutil::locate(9, 25); cout << "this page. Press any key to continue."; rlutil::getkey(); rlutil::resetColor(); clrScr(3);
						}	clrScr(4);
					}
						
				}
				else if (op == rlutil::KEY_ESCAPE) {
					clrScr(3); rlutil::locate(12, 24); cout << "[Operation cancelled]"; Sleep(2000); clrScr(3); clrScr(4);
				}	
				else {
					clrScr(3);
					rlutil::locate(12, 24); rlutil::setColor(14); cout << "Invalid Option. Press any KEY to continue."; rlutil::resetColor(); rlutil::getkey(); clrScr(3);	clrScr(4);
				}
			}
			else {
				clrScr(3);
				rlutil::locate(10, 24); cout << "Input number range must be within the range of number of tasks. Press "; rlutil::locate(10, 25); cout << "any key to continue."; rlutil::getkey(); clrScr(3);	clrScr(4);
			}	
		}
	Tas_StOpt:
		clrScr(2); if (idx_No != 0) { Show(count, stor); }
	//---------------------------------------PRINT DONE TASKS IN CONSOLE SCREEN (D - DONE)---------------------------------------------//
		for (int i = 0; i < k - 1; i++) {
			if (page == 1) {
				if (i >= 0 && i < 16) { rlutil::setColor(10); rlutil::locate(41, i + 6); cout << showDoneTas[i]; rlutil::resetColor(); }
				else if (i >= 16 && i < 32) { rlutil::setColor(10); rlutil::locate(82, i - 10); cout << showDoneTas[i]; rlutil::resetColor(); }
			}
			else if (page == 2) {
				if (i >= 32 && i < 48) { rlutil::setColor(10); rlutil::locate(41, i - 26); cout << showDoneTas[i]; rlutil::resetColor(); }
				else if (i >= 48 && i < 64) { rlutil::setColor(10); rlutil::locate(82, i - 42); cout << showDoneTas[i]; rlutil::resetColor(); }
			}
			else if (page == 3) {
				if (i >= 64 && i < 80) { rlutil::setColor(10); rlutil::locate(41, i - 58); cout << showDoneTas[i]; rlutil::resetColor(); }
				else if (i >= 80 && i < 96) { rlutil::setColor(10); rlutil::locate(82, i - 74); cout << showDoneTas[i]; rlutil::resetColor(); }
			}
			else if (page == 4) {
				if (i >= 96 && i < 100) { rlutil::setColor(10); rlutil::locate(41, i - 90); cout << showDoneTas[i]; rlutil::resetColor(); }
			}
		}
	//-----------------------------------------------------------------------------------------------------------//
		Opt_ContrM(1); Opt_ContrM(2);
		switch (rlutil::getkey()) {
		case rlutil::KEY_RIGHT:
			page++;		if (page > 4) { page--; }
			goto Tas_StOpt;
			break;
		case rlutil::KEY_LEFT:
			page--;		if (page < 1) { page++; }
			goto Tas_StOpt;
			break;
		case rlutil::KEY_ENTER:
			if (selOpt == 7) { markTas = true;  goto Mar_Tas; }		// Go up and continue reading lines for MARK TASK
			break;
		case rlutil::KEY_ESCAPE:
			break;
		default:
			rlutil::setColor(14);
			rlutil::locate(9, 24); cout << "Invalid Key Press. Refer to CONTROLS in Right Menu. Press any key to";	rlutil::locate(9, 25); cout << "continue."; rlutil::getkey(); clrScr(3);
			rlutil::resetColor();
			goto Tas_StOpt;
			break;
		}
		clrScr(1); clrScr(3); clrOpt();		// Erase screen first b4 going to Previous Menu
	}
}
void printCalendar(int year) {
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int mDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	string monthList[] = { "January", "February", "March", "April", "May", "June",
						"July", "August", "September", "October", "November", "December" };
	rlutil::setColor(11); cout << "  --------------------------------" << endl; rlutil::resetColor();
	rlutil::setColor(9); cout << "           Calendar - " << year << endl; rlutil::resetColor();
	rlutil::setColor(11); cout << "  --------------------------------" << endl; rlutil::resetColor();
	int days;
	int current;
	int y = year - 1;
	current = (y + y / 4 - y / 100 + y / 400 + t[0] + 1) % 7;
	for (int i = 0; i < 12; i++) {
		if (i == 1)			//February Leap Year(happens every 4 years)
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
				days = 29;
			else
				days = mDays[i];
		else
			days = mDays[i];
		rlutil::setColor(12); cout << endl << "  ------------" << monthList[i] << "-------------" << endl; rlutil::resetColor();
		rlutil::setColor(14); cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl; rlutil::resetColor();

		int k;
		for (k = 0; k < current; k++)
			cout << "     ";

		for (int j = 1; j <= days; j++) {
			k++;
			cout << setw(5) << j;
			if (k > 6) { k = 0; cout << endl; }
		}
		if (k)
			cout << endl; current = k;
	}
	cout << "\n\t\t\t[NOTE: You must press ANY KEY stated below TWICE for it to function.] \n";
	rlutil::anykey("\n\t\t\tPress 'n' to go to NEXT YEAR, 'p' to go to PREVIOUS YEAR, 'e' to go to MAIN MENU. \n");
	return;
}
void viewStats(int menu) {
	if (menu == 1) {
		for (int i = 0; i < 15; i++) { rlutil::locate(12, 5 + i); cout << (char)0xB3; }
		rlutil::locate(12, 20); cout << (char)0xC0;
		for (int i = 0; i < 65; i++) { rlutil::locate(13 + i, 20);	cout << (char)0xC4; }

		for (int i = 0; i < 6; i++) {		// Left Index Label
			if (i == 0) { rlutil::locate(9, 20 - (i * 3)); cout << ind_Label + (i * 100); }
			else { rlutil::locate(8, 20 - (i * 3)); cout << ind_Label + (i * 100); }
		}
		ifstream gtSt("stats.txt"); int k = 0;
		while (!(gtSt.eof())) {						// get stats.txt contents first and store in array :)
			gtSt >> monTasCompl[k];
			k++;
		}
		//----------------------------drawBar Logic-------------------------------//
		for (int i = 0; i < mon + 1; i++) {
			if (monTasCompl[i] >= 50 && monTasCompl[i] < 100) { drawBar[i] += 1;	drawBar[i] > 1 ? drawBar[i] -= 1 : 0; }	// From 50 - 99 tasks
			else if (monTasCompl[i] >= 100 && monTasCompl[i] < 150) { drawBar[i] += 3;		drawBar[i] > 3 ? drawBar[i] -= 3 : 0; }	// From 100 - 149 tasks
			else if (monTasCompl[i] >= 150 && monTasCompl[i] < 200) { drawBar[i] += 4;		drawBar[i] > 4 ? drawBar[i] -= 4 : 0; }	// From 150 - 199 tasks
			else if (monTasCompl[i] >= 200 && monTasCompl[i] < 250) { drawBar[i] += 6;		drawBar[i] > 6 ? drawBar[i] -= 6 : 0; }	// From 200 - 249 tasks
			else if (monTasCompl[i] >= 250 && monTasCompl[i] < 300) { drawBar[i] += 7;		drawBar[i] > 7 ? drawBar[i] -= 7 : 0; }	// From 250 - 299 tasks
			else if (monTasCompl[i] >= 300 && monTasCompl[i] < 350) { drawBar[i] += 9;		drawBar[i] > 9 ? drawBar[i] -= 9 : 0; }	// From 300 - 349 tasks
			else if (monTasCompl[i] >= 350 && monTasCompl[i] < 400) { drawBar[i] += 10;		drawBar[i] > 10 ? drawBar[i] -= 10 : 0; }	// From 350 - 399 tasks
			else if (monTasCompl[i] >= 400 && monTasCompl[i] < 450) { drawBar[i] += 12;		drawBar[i] > 12 ? drawBar[i] -= 12 : 0; }	// From 400 - 449 tasks
			else if (monTasCompl[i] >= 450 && monTasCompl[i] < 500) { drawBar[i] += 13;	drawBar[i] > 13 ? drawBar[i] -= 13 : 0; }	// From 450 - 499 tasks
			else if (monTasCompl[i] >= 500) { drawBar[i] += 15;	drawBar[i] > 15 ? drawBar[i] -= 15 : 0; }	// 500 tasks or higher
		}
		for (int x = (navigDate - 3); x <= navigDate; x++) {
			if (x >= 0 && x <= 3) {						// all loops inside will not run unless system mon = "Jan - Apr"
				rlutil::locate(19 + x * 17, 21);  cout << months[x];	//Months Label

				for (int z = 0; z < (x + 1); z++) {			//Bar Graph Logic based on System Month
					for (int y = 0; y < drawBar[z]; y++) {
						rlutil::setColor(14);
						rlutil::locate(19 + (z * 17), 19 - y); cout << "±±";
						rlutil::resetColor();
					}
				}
		
			}
			else if (x >= 4 && x <= 7) {					// all loops inside will not run unless system mon = "May - Aug"
				rlutil::locate(19 + ((x - 4) * 17), 21); cout << months[x];		//Months Label 
										
				for (int z = 4; z < (x + 1); z++) {			//Bar Graph Logic based on System Month
					for (int y = 0; y < drawBar[z]; y++) {
						rlutil::setColor(14);
						rlutil::locate(19 + ((z - 4) * 17), 19 - y); cout << "±±";	//Bar Graph
					}	rlutil::resetColor();
				}
			}
			else if (x >= 8 && x <= 11) {					// all loops inside will not run unless system mon = "Sept - Dec"
				rlutil::locate(19 + ((x - 8) * 17), 21); cout << months[x];		//Months Label
				
				for (int z = 8; z < (x + 1); z++) {			//Bar Graph Logic based on System Month
					for (int y = 0; y < drawBar[z]; y++) {
						rlutil::setColor(14);
						rlutil::locate(19 + ((z - 8) * 17), 19 - y); cout << "±±";	//Bar Graph

					} rlutil::resetColor();
				}
			}
		}
		rlutil::setColor(11); rlutil::locate(9, 25); cout << "Tasks Completed [" << months[months_ind] << " " << Year << "] : " << monTasCompl[mon];
		rlutil::locate(58, 25); cout << "+ 50 Tasks = "; rlutil::resetColor();
		rlutil::setColor(14); rlutil::locate(72, 25); cout << "±±"; rlutil::resetColor();
	}
	else if (menu == 2) {
		clrScr(1); clrOpt();
		ifstream gtSt("stats.txt"); int k = 0;
		while (!(gtSt.eof())) {						// get stats.txt contents first and store in array :)
			gtSt >> monTasCompl[k];
			k++;
		}
		rlutil::setColor(11); rlutil::locate(WIN_WIDTH - 80, WIN_HEIGHT - 22); cout << "MONTHLY NUMBER OF TASKS COMPLETED"; rlutil::resetColor();
		rlutil::setColor(14);
		
		for (int j = 0; j < 6; j++) { rlutil::locate(15, (j + (6 + (j + 2)))); cout << months[j] << " = " << monTasCompl[j]; }
		for (int j = 6; j < 12; j++) { rlutil::locate(55, ((j - 6) + (6 + ((j - 6) + 2)))); cout << months[j] << " = " << monTasCompl[j]; }
		
		rlutil::locate(WIN_WIDTH - 20, 8); cout << "Press any key to Go";
		rlutil::locate(WIN_WIDTH - 21, 9); cout << "back to Previous Menu";
		rlutil::resetColor();
		rlutil::getkey(); clrScr(1); clrOpt();
	}
}

void Input_Main() {
	readFileInd(idx_No);	//Read Idx File
	if (kbhit()) {
		switch (rlutil::getkey()) {
		case rlutil::KEY_DOWN:
			selOpt++;
			if (selOpt == 12)
				selOpt--;
			break;
		case rlutil::KEY_UP:
			selOpt--;
			if (selOpt == 6)
				selOpt++;
			break;
		case rlutil::KEY_LEFT:
			clrScr(5); dueD_Idx--;
			if (dueD_Idx <= -1)
				dueD_Idx++;
			break;
		case rlutil::KEY_RIGHT:
			clrScr(5); dueD_Idx++;
			if (dueD_Idx >= idx_No)
				dueD_Idx--;
			break;
		case rlutil::KEY_ENTER:
			clrScr(1);
			if (selOpt == 7) { choose = 1; clrOpt(); selOpt = 7; }	//selOpt = 7 to reset its position sa top ng choices b4 it goes to another menu//
			else if (selOpt == 8) { choose = 2; clrOpt(); selOpt = 7; }	
			else if (selOpt == 9) { choose = 3; clrOpt(); selOpt = 7; }
			else if (selOpt == 10) { choose = 4; clrOpt(); selOpt = 7; } 
			else if (selOpt == 11) { dialBox(5); clrOpt(); choose = 5; selOpt = 7; }
			break;
		case rlutil::KEY_ESCAPE:
			choose--;
			if (choose == -1) {			//Exit Console (Other Func at main() )
				clrScr(1); clrOpt(); break;
			}
			break;
		}
	}
}
void firsOptContr() {
	Over_VOpt();
	if (kbhit()) {
		switch (rlutil::getkey())
		{
		case rlutil::KEY_LEFT:
			clrScr(1);
			overView(1);
			break;
		case rlutil::KEY_RIGHT:
			system("cls");
			overView(2);
			break;
		case rlutil::KEY_ESCAPE:
			clrScr(1); clrOpt(); choose = 0;
			break;
		}
	}
}
void secOptContr() {
	Input_MOpt();
	if (kbhit()) {
		switch (rlutil::getkey()) {
		case rlutil::KEY_UP:
			selOpt--;
			if (selOpt == 6) { selOpt++; }
			break;
		case rlutil::KEY_DOWN:
			selOpt++;
			if (selOpt == 9) { selOpt--; }
			break;
		case rlutil::KEY_ENTER:
			if (selOpt == 7) { addTasks = true; clrScr(1); clrOpt(); selOpt = 8; }		//selOpt = 8 pra if accident. napress ult yung enter, d na magaadd task
			else if (selOpt == 8) { clrScr(1); clrOpt(); selOpt = 7; choose = 0; }
			break;
		}
	}
}
void thirOptContr() {
	View_TasOpt();
	if (kbhit()) {
		switch (rlutil::getkey())
		{
		case rlutil::KEY_UP:
			selOpt--;
			if (selOpt == 6) { selOpt++; }
			break;
		case rlutil::KEY_DOWN:
			selOpt++;
			if (selOpt == 11) { selOpt--; }
			break;
		case rlutil::KEY_LEFT:
			clrScr(1); 	page -= 1;
			if (page < 1) { page++; }
			break;
		case rlutil::KEY_RIGHT:
			clrScr(1);	page += 1;
			if (page > 4) { page--; }
			break;
		case rlutil::KEY_ENTER:
			if (selOpt == 7) { viewTasks(1); }
			else if (selOpt == 8) { viewTasks(2); }
			else if (selOpt == 9) { viewTasks(3); }
			else if (selOpt == 10) { viewTasks(4); }
			break;
		case rlutil::KEY_ESCAPE:
			clrScr(1); clrOpt(); page = 1; selOpt = 7; choose = 0;
			break;
		}
	}
}
void fourOptContr() {
	View_StOpt();
	if (kbhit()) {
		switch (rlutil::getkey()) {
		case rlutil::KEY_LEFT:
			clrScr(1); navigDate -= 4;
			if (navigDate < 0) { navigDate = 3; }
			break;
		case rlutil::KEY_RIGHT:
			clrScr(1); navigDate += 4;
			if (navigDate > 11) { navigDate = 11; }
			break;
		case rlutil::KEY_ENTER:
			if (selOpt == 7) { viewStats(2); }
			break;
		case rlutil::KEY_ESCAPE:
			clrScr(1); clrOpt(); choose = 0;
			break;
		}
	}
}
void fifOptContr() {
	char option = _getch();
	if (option == 'n' || option == 'N') { year++; }
	else if (option == 'p' || option == 'P') { year--; }
	else if (option == 'e' || option == 'E') { system("cls"); year = 1900 + local_time->tm_year; choose = 0; }		// reset year to sys year
	else { cout << " "; }	// Counter to press event bug when calling printCalendar()
}
int main() {
	while (1) {
		fontsize(10, 18);
		rlutil::hidecursor(); rlutil::saveDefaultColor(); rlutil::setBackgroundColor(0);
		if (choose <= 4) { drawBorder(1); }
		//---------------------Specific Controls for any selected Option in the Main Menu------------------------------//
		if (choose == 0) { Input_Main(); }
		if (choose == 1) { firsOptContr(); }
		if (choose == 2) { secOptContr(); }
		if (choose == 3) { thirOptContr(); }
		if (choose == 4) { fourOptContr(); }
		if (choose == 5) { fifOptContr(); }
		//------------------------------------MENU-----------------------------------------//
		if (choose == 0) { mainMenu(1); }
		else if (choose == 1) { overView(1); }
		else if (choose == 2) { inputMenu(); }
		else if (choose == 3) { viewTasks(0); }
		else if (choose == 4) { viewStats(1); }
		else if (choose == 5) { system("cls");  printCalendar(year); }
		//---------------------------------EXIT CONSOLE CONFIRMATION-------------------------------------------//
		if (choose == -1) {
			dialBox(6);
			switch (rlutil::getkey()) {
			case rlutil::KEY_LEFT:
				exiSelOpt -= 21;
				if (exiSelOpt == 12)
					exiSelOpt += 21;
				break;
			case rlutil::KEY_RIGHT:
				exiSelOpt += 21;
				if (exiSelOpt == 75)
					exiSelOpt -= 21;
				break;
			case rlutil::KEY_ENTER:
				if (exiSelOpt == 33) { system("cls"); return 0; }		//Yes
				else if (exiSelOpt == 54) { clrScr(2); exiSelOpt = 33; choose++; }			//No
				break;
			}
		}
	}
}