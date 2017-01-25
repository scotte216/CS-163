// Scott Ewing
// CS163
// Assignment 2
//
// Filename:
// main.cpp
//

#include "inbox.h" //This is our inbox in a Stack of a dynamic array.
#include "vip_inbox.h" // This is our VIP inbox which is a queue via a CLL
#include <fstream>
using namespace std;

const int MAX = 200; // temporary size for loading emails to our ADT
const int LAST = 6; // used for the menu to determine how large it is


//Prototypes
void get_emails(inbox & my_inbox);
int again(char []);
int menu();
void read_top_email(inbox & my_inbox, vip_inbox & my_vip_inbox);
void read_top_vip(vip_inbox & my_vip);

//Simple function to display prompt, expecting a y/n response to determine if
//something should happen 'again'
int again(char prompt[])
{
    char response;
    cout << prompt;
    cin >> response;
    cin.ignore(MAX,'\n');

    response = toupper(response);

    if ('Y' == response) return 1;
    return 0;
}

//Menu function to display options of the program. 
int menu()
{
    int response;

    do{

    cout << "Please select an item from the menu below: \n"
         << "1) Load all emails into inbox\n"
         << "2) Show all regular emails\n"
         << "3) Read and delete most current email -- ask if it is VIP\n"
         << "4) Show all VIP emails.\n"
         << "5) Read and delete first VIP.\n"
         << "6) Quit\n";
        
    cout<< "\nPlease select a menu option: ";
    cin >> response;
    cin.ignore(100,'\n');

    } while(1 > response || LAST < response);

    return response;

}

//This function sets up a routine to load emails from a text file. Each email is
//then added to the inbox. emails.txt is the current test email file. 
void get_emails(inbox & my_inbox)
{
    email_details my_email;
    email_entry my_entry;

    my_email.name = new char[MAX];
    my_email.address = new char[MAX];
    my_email.subject = new char[MAX];
    my_email.date = new char[MAX];
    my_email.message = new char[MAX];
    
    ifstream file_in;// creating our file input variable.

    char filename[] = "emails.txt";
    file_in.open(filename);
    //expecting format of name|address|subject|Date|message\n

    if (file_in)
    {
        file_in.get(my_email.name,MAX,'|');
        file_in.ignore(MAX,'|');
        while (!file_in.eof()) 
        {

            file_in.get(my_email.address,MAX,'|');
            file_in.ignore(MAX,'|');

            file_in.get(my_email.subject,MAX,'|');
            file_in.ignore(MAX,'|');

            file_in.get(my_email.date,MAX,'|');
            file_in.ignore(MAX,'|');
  
            file_in.get(my_email.message,MAX,'\n');
            file_in.ignore(MAX,'\n');

            if (!my_entry.create_entry(my_email))
                cout << "\nError in creating a new email entry\n";
            if (!my_inbox.push(my_entry))
                cout << "\nError in adding new email to inbox\n";

            file_in.get(my_email.name,MAX,'|');
            file_in.ignore(MAX,'|');
        }

        file_in.close();
        file_in.clear();

        cout << "\nData loaded from: " << filename << ".\n";
    }
    else
    {
        cout << "\nERROR: " << filename << " not found.\n";
        filename[0]='\0';
    }
}


//This function will show the current email, prompt for deletion. If they want
//to delete it they will also be prompted if they want to mark it VIP. This will
//prevent the user from adding multiple copies of an email to the VIP inbox. 
void read_top_email(inbox & my_inbox,vip_inbox & my_vip)
{
    email_entry temp;

    if (!my_inbox.peek(temp))
        cout << "\nInbox is empty.\n";
    else
    {
        cout << "\nTop email:\n----------\n";
        temp.display();
        if (again("Delete this email? (Y/N)"))
        {
            if(again("Is this a VIP entry? (Y/N) "))
            {
                if (!my_vip.enqueue(temp))
                {
                    cout << "\nError adding VIP entry!\n";
                }
                else
                {      
                    cout << "\nAdded to VIP list.\n";
                }
            }
            if (!my_inbox.pop())
                cout << "\nError deleting top email.\n";
            cout << "Email deleted.\n";
        }
    }
}


//This function will display the top entry of the VIP inbox and prompt for a
//deletion.
void read_top_vip(vip_inbox & my_vip)
{
   
    email_entry temp;
    if (!my_vip.peek(temp))
        cout << "\nVIP inbox is empty.\n";
    else
    {
        temp.display();
        if (again("Delete? y/n: "))
            my_vip.dequeue();
    }
}

//This is the main function of assignment 2. It resolves what action to take
//depending on the menu option selected by the user. Generally users will want
//to use option 1 first to load the emails.txt file.
int main()
{
    inbox my_inbox;
    vip_inbox my_vip_inbox;

    int mennum=menu();

    while (mennum != LAST)
    {
        if (1 == mennum)
            get_emails(my_inbox);
        else if (2 == mennum)
        {
            if (!my_inbox.display_all())
                cout << "\nInbox is empty.\n";
        }
        else if (3 == mennum)
                read_top_email(my_inbox,my_vip_inbox);
        else if (4 == mennum)
        {    
            if (!my_vip_inbox.display_all())
                cout << "\nVIP inbox is empty.\n";
        }
        else if (5 == mennum)
            read_top_vip(my_vip_inbox);

        mennum=menu();
    }

    cout << "\nThanks for using this system. Come back again!\n";
    
    return 0;
}
