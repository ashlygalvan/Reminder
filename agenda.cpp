#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;

struct Reminder 
//assign variables to define the day the person wants the reminder to go out.
//assign variables to define what the person wants to say on the certain day.

{
    int year;
    int month;
    int day;
    string popup_message;
    string selfwritten_message;
    bool poppedup; //This will check if one of the popup messages has been displayed
};

int main()
{
    //getting the current time and date to show user
    time_t local;
    struct tm * ltime; //ltime = localtime
    time (&local);
    ltime = localtime(&local);

    cout << "As a reminder the current time is: " << asctime(ltime);

    vector<Reminder*> reminders;
    char addremind;


    //person will set what date they want the reminder to go out.

    do {
        Reminder* newReminder = new Reminder;
    cout << "\nChoose the year: \n";
    cin >> newReminder->year;
        while (newReminder->year > 2099||newReminder->year < 2024)
        {
            cout << "\nThe year selected is too far! Choose a closer year: \n";
            cin >> newReminder->year;
        }

    //The loop will make sure that there is a valid month entered
    cout << "\nChoose the month: \n";
    cin >> newReminder->month;
        while (newReminder->month < 1 || newReminder->month > 12)
        {
            cout << "\nReminder there is only 12 months! Choose again: \n";
            cin >> newReminder->month;
        }
    
    cout << "\nChoose the day: \n";
    cin >> newReminder->day;

    while ((newReminder->day == 2 && newReminder->day > 29) || (newReminder->month == 4 || newReminder->month == 6 || 
        newReminder->month == 9 || newReminder->month == 11) && newReminder->day> 30 || (newReminder->day < 1 || newReminder->day > 31))
    {
        cout << "\nThat's not a valid date! Choose a valid date!";
        cin >> newReminder->day;
    }

    cout << "\nWrite your reminder for that day!\n";
    cin.ignore();
    getline(cin, newReminder->selfwritten_message);
    cout << "\nWrite what the popup message will be titled!\n";
    getline(cin, newReminder->popup_message);
    cout << "\n";
    newReminder->poppedup = false;

    reminders.push_back(newReminder);

    cout << "Add more reminders? (y/n)";
    cin >> addremind;
    } while (addremind == 'y' || addremind == 'Y');

    while(true)
    {
        int current_year = ltime -> tm_year + 1900;
        int current_month = ltime -> tm_mon + 1;
        int current_day = ltime -> tm_mday;

        bool reminderpopped = false;
        //This checks if the time is still valid
        for (auto reminder : reminders)
        {
            if(!reminder -> poppedup &&
            reminder ->  year == current_year &&
            reminder -> month == current_month &&
            reminder -> day == current_day)
            {
                MessageBox(NULL, reminder -> selfwritten_message.c_str(), reminder -> popup_message.c_str(), MB_ICONINFORMATION|MB_OK);
                reminder -> poppedup = true;
                reminderpopped = true;
            }
        }
        if (!reminderpopped){
            Sleep(60000);
        }else
            {
                break;
            }
         }

    for(auto reminder : reminders)
    {
        delete reminder;
    }

    return 0;
}