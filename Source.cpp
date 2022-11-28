#include <iostream>
#include <string>

using namespace std;

class Time {		// Class to get current time. Also to use getters and setters to get and update time. 
private:
	// Private attribute since user will not need to access any of these attributes.
	time_t ttime = time(0);
	tm* local_time = localtime(&ttime);
	int &hour = local_time->tm_hour;
	int &min = local_time->tm_min;
	int &sec = local_time->tm_sec;

public: // Public since user will need to access these methods.
	// Setter
	void setHour(int h) {
		hour = h;
	}
	void setMin(int m) {
		min = m;
	}
	void setSec(int s) {
		sec = s;
	}
	// Getter
	int getHour() {
		return hour;
	}
	int getMin() {
		return min;
	}
	int getSec() {
		return sec;
	}
};

string nCharString(int length, char character) { //Parameter: length, (Number of times character is repeated) / Parameter character (Character to be repeated).
	string returnString;						 //String to be returned.
	for (int i = 0; i < length; i++) {			 //Loop 'length' amount of times.  
		returnString += character;				 //Adding the 'character' to 'returnString' each time.
	}
	return returnString;						 //Return 'returnString'.

}

string twoDigitString(int n) {					 //Parameter: n(Digit to see if a 0 is needed in front of it).
	if (n > 9)									 //If 'n' is greater than 9.
		 return std::to_string(n);				 //Return 'n' in string format.
	return '0' + std::to_string(n);				 //Return 'n' with '0' in front of it in string format.
}

string formatTime12(int h, int m, int s) {	// Parameter: All int hour, minute, second. 
	string amOrPm;							// Initalizes string if time is AM or PM.
	if (h < 12)								// If hour is less than 12 then amOrPm is set to A M.
		amOrPm = "A M";
	else {									// Else amOrPm is set to P M.
		amOrPm = "P M";
		h -= 12;							// Hour subtracted by 12 since this is in 12 hour format.
	}
	if (h == 0)								// If hour is 0 after subtraction that means hour should be 12.
		h = 12;
	return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + amOrPm; //returns time in 12 hour format. 
}

string formatTime24(int h, int m, int s) {
	return twoDigitString(h) + ":"  +  twoDigitString(m) + ":" + twoDigitString(s);	// Formats time in 24 hour time.
}

void display(int h, int m, int s) {				 //Method to display both the 12 hour clock and 24 hour clock. 
	cout << nCharString(27, '*');
	cout << nCharString(3, ' ');
	cout << nCharString(27, '*') << endl;
	cout << "*      12-HOUR CLOCK      *   *      24-HOUR CLOCK      *" << endl << endl;
	cout << "*      " << formatTime12(h, m, s) << "       *   " << "*        " << formatTime24(h, m, s) << "         *" << endl;
	cout << nCharString(27, '*');
	cout << nCharString(3, ' ');
	cout << nCharString(27, '*') << endl;
}

void printMenu(char width) { //Method to print out the menu for the user to choose an option from. 
	const char* strings[] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };		//Constant char* array, which holds the four menu choices. 
	int numStrings = 4;		// Amount of choices
	cout << nCharString(width,'*') << endl;	
	for (int i = 0; i < numStrings; i++) {
		cout << "* " << i + 1 << " - " << strings[i] << nCharString(width - strlen(strings[i]) - 7, ' ') << "*" << endl; //Prints out all 4 choices in a clean format.
		if(i < numStrings -1)
			cout << endl;
	}
	cout << nCharString(width, '*') << endl;
}

int getMenuChoice(int maxChoice) { // Method to return which choice is made, with a parameter being the max choice number.
	int choice;
	while (true) {
		cin >> choice;
		if(choice <= maxChoice && choice > 0) 
			break;
	}
	return choice;
}

void addOneHour(Time myobj) {	// Method to add one hour to the current time if this option is chosen.    
	if (myobj.getHour() >= 0 && myobj.getHour() <= 22)
		myobj.setHour(myobj.getHour() + 1);
	else if (myobj.getHour() == 23) {
		myobj.setHour(0);
	}
}

void addOneMinute(Time myobj) {  // Method to add one minute to the current time if this option is chosen. 
	if (myobj.getMin() >= 0 && myobj.getMin() <= 58)
		myobj.setMin(myobj.getMin() + 1);
	else if (myobj.getMin() == 59) {
		addOneHour(myobj);
		myobj.setMin(0);
	}
}
 
void addOneSecond(Time myobj) {  // Method to add one second to the current time if this option is chosen. 
	if (myobj.getSec() >= 0 && myobj.getSec() <= 58)
		myobj.setSec(myobj.getSec() + 1);
	else if (myobj.getSec() == 59) {
		addOneMinute(myobj);
		myobj.setSec(0);
	}
}

void mainMenu(Time myobj) { // Method to get main menu choice and call the correct method.
	int input;
	while (true) {
		input = getMenuChoice(4);
		if (input == 1) {
			addOneHour(myobj);
			break;
		}
		else if (input == 2){
			addOneMinute(myobj);
			break;
		}
		else if (input == 3){
			addOneSecond(myobj);
			break;
		}
		else if (input == 4)
			exit(0);
	}
}

int main() {	// Main method of program.
		Time myobj;
		while (true) {
			system("CLS");
			display(myobj.getHour(), myobj.getMin(), myobj.getSec());
			printMenu(25);
			mainMenu(myobj);
	}
}














//bool getInput(char* c)
//{
//	if (_kbhit())
//	{
//		*c = _getch();
//		return true; // Key Was Hit
//	}
//	return false; // No keys were pressed
//}
//int main() {
//	Time myobj;
//	char key = ' ';
//	while (key != '1' && key != '2' && key != '3' && key != '4')
//	{
//		while (!getInput(&key))
//		{
//			Time myobj;
//			system("CLS");
//			display(myobj.getHour(), myobj.getMin(), myobj.getSec());
//			printMenu(25);
//			Sleep(1);
//		}
//		while (true) {
//			system("CLS");
//			display(myobj.getHour(), myobj.getMin(), myobj.getSec());
//			printMenu(25);
//			mainMenu(myobj);
//		}
//	}
//}

