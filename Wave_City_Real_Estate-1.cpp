#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<fstream>

using namespace std;

// This project shows the representaion of houses in a city.
// An administrator is the one who can perform every action including adding new properties and to removing them.
// A visitor is the person who can view the properties in the city and if desired, can book his/her desirable property.
//The first house in every sector is made for the committee members and can not be booked or bought.

// Node represent a house
class Node 
{
    public:

    int data;
    Node* next;

    Node(int d)
    {
        this -> data = d;
        this -> next = NULL;
    }
};

// for all cout statements for dynamic priting

void animation(string str)
{
    for(int i=0; i<str.length(); i++)
    {
        cout<<str[i];
        Sleep(15);
    }
}

// This function will be defined later
void logIN();

// Use of 'MULTI-LIST' Or 'ARRAY-OF-LIST' data structure to represent the real-estate structure of whole city.
vector<Node*> Wave_City;

// password to be used when logging in as an Administrator.
int password = 134679;

// function to check the password while logging in as an administrator.
bool checkPass()
{
    int n;

    string str = "Please Enter Password : ";
    animation(str);
    cin>>n;

    if(n == password)
    {
    return true;
    }

    else
    {
    return false;
    }
}


// Inserting the houses, in case of new houses, in the database

//Insertion of houses at the start of respective list.
void insertAtHead(Node* &head, int data)
{
    Node* temp = new Node(data);

    temp -> next = head;
    head = temp;
}

//Insertion of houses at the end of respective list.
void insertAtTail(Node* &tail ,int data)
{
    Node* temp = new Node(data);

    tail -> next = temp;
    tail = temp;
}

//Insertion of houses at the any place of respective list.
void insertInBetween(Node* &head, Node* &tail, int d, int position)
{
    if(position == 1)
    {
        insertAtHead(head, d);
        return;
    }

    Node* temp = head;

    int count = 1;

    while(count != position-1)
    {
        temp = temp -> next;
        count++;
    }

    if(temp -> next == NULL)
    {
        insertAtTail(tail, d);
        return;
    }

    Node* nodeToInsert = new Node(d);

    nodeToInsert -> next = temp -> next;
    temp -> next = nodeToInsert;
}

// If a house is being sold then that node would be deleted and the remaining houses would be displayed!
void deleteNode(Node* &head, int d)
{
    if(head->next == NULL){
       Node* temp = head;
       head = NULL;
       delete(temp);
    }

    else if(head->data == d)
    {
        Node* temp = head;
        head = head -> next;
        temp -> next = NULL;
        delete temp;
    }

    else
    {

        Node* curr = head;
        Node* prev = NULL;

        while(curr->data != d)
        {
            prev = curr;
            curr = curr -> next;

        }
        prev -> next = curr -> next;
        curr -> next = NULL;

        delete curr;
    }

}

// Function to find the tail of current list.

Node* findTail(Node* head)
{
    Node* temp = head;

    while(temp->next!= NULL)
    {
        temp = temp->next;
    }

    return temp;
}

// This function will display the current houses in a particular sector(list).

void displayHousesInSector(Node* arr)
{
    Node* temp = arr;
    string str;

    if(temp == NULL)
    {
        string str = "Oops!! This sector is Empty.";
        animation(str);
        return;
    }

    while(temp != NULL)
    {
        cout<<temp -> data<<" ";
        temp = temp -> next;
    }

    cout<<endl;
}


// This function will display the current houses in the city

void displayHouses(vector<Node*> arr)
{

    for(int i=0;i<arr.size();i++)
    {
        string str = "Displaying Houses for sector ";

        animation(str);
        cout<<i+1<<endl;

        displayHousesInSector(arr[i]);
    }
}


// To find the vacant sector, searching would be done.
// If the sector is vacant then true will be returned otherwise false will be returned.

bool isSectorVacant(Node* &head)
{
    Node* temp = head;

    if(temp == NULL)
    return false;

    else
    return true;
}

// Searching for the required house in that sector

bool isHouseVacant(Node* &head, int HouseNumber)
{
    Node* temp = head;

    if(temp == NULL)
        return false;

    while(temp != NULL)
    {
        if(temp->data == HouseNumber)
        return true;

        temp = temp->next;
    }

    return false;
}

//function to get length of a list

int getLength(Node* &head)
{
  int len=0;
  Node* temp = head;

  while(temp!=NULL)
    {
      temp = temp->next;
      len++;
    }

  return len;
}

//function to sort the list

void selectionSort(Node* head)
{
    Node* temp = head;
  
    // Traverse the List
    while (temp) {
        Node* min = temp;
        Node* r = temp->next;
  
        // Traverse the unsorted sublist
        while (r) {
            if (min->data > r->data)
                min = r;
  
            r = r->next;
        }
  
        // Swap Data
        int x = temp->data;
        temp->data = min->data;
        min->data = x;
        temp = temp->next;
    }
}

//function to collect response from the user

bool response()
{
    char ch;
    cin>>ch;

    if(ch == 'Y' || ch == 'y')
    return true;

    else if (ch == 'N' || ch == 'n')
    return false;

    else
    {
        bool cond = response();
        return cond;
    }

}

// Asking for users choice  for booking a house and searching if that house is vacant or occupied

pair<int, int> usersChoiceForSector(vector<Node*> arr)
{
    pair<int, int> secAndHouse;
    int sector;
    string str;

label1:
    str = "Please tell us in which sector you want to purchase a house : \n";
        
        animation(str);

        cin>>sector;

    Node* head = arr[sector-1];

    if(isSectorVacant(head))
    {

        secAndHouse.first = sector;

label2:
        str = "In this sector, following houses are vacant --> ";

        for(int i=0; i<str.length(); i++)
        {
            cout<<str[i];
            Sleep(15);
        }

        displayHousesInSector(arr[sector-1]);
        cout<<endl;

        int house;

        labelu1:
        str = "Please choose a house from the above list except the first house! \n";
        animation(str);

        cin>>house;
         
        if(house%100 == 1)
        {
            str = "This house cannot be booked \n It belongs to authorities \n";
            animation(str);
            goto labelu1;
        }

        if(isHouseVacant(head, house))
        {
            str = "Are you sure to book this house? (Y/N) \n";
            animation(str);

            char response;
            cin>>response;

            if(response == 'Y' or response == 'y')
            {
                secAndHouse.second = house;
                deleteNode(head,house);
                return secAndHouse;
            }

            else if(response == 'N' or response == 'n')
            {
               str = "You can choose another house :) \n Do you want to choose another house? (Y/N) \n";
               animation(str);

                cin>>response;

                if(response == 'N' || response == 'n')
                {
                    str = "You can choose another sector :) \n Do you want to choose another sector? (Y/N) \n";

                    animation(str);

                    cin>>response;

                     if(response == 'Y' or response == 'y')
                     {
                        goto label1;
                     }

                     else if(response == 'N' || response == 'n')
                     {
                        str = "We are sad to see you go!\n";
                        animation(str);
                        cout<<"----------------------------------------------------------------------------------------------------------------------"<<endl;
                        str = "We hope we will be able to provide you your dream house next time! \n Have a Good Day!\n";
                        animation(str);
                        exit(0);
                     }

                     else{
                        str = "Invalid Entry!\n";
                        animation(str);
                        goto label1;
                     }

                }

                else if(response == 'y' || response == 'Y')
                {
                    goto label2;
                }

                //if((response >= 0) && (response <=256) && (response != 78) && (response != 89) && (response != 110) && (response != 121))

                else
                {
                    str = "Invalid Entry! \n Please choose the correct option!\n";
                    animation(str);

                    goto label2;
                }
            }
        }
        else{
            str = "This House is not present in the above list. \n Would you like to try again ? (Y/N) \n";
            animation(str);

            char resp;
            cin>>resp;

            if(resp == 'Y' || resp == 'y')

            goto label1;

            else
            {
                pair<int,int>nil = make_pair(0,0);
                return nil;
            }
        }
    }
    else{
        str = "We are really sorry :( , All houses in this sector are already booked! \n You can choose another sector :) \n Do you want to choose another sector? (Y/N)\n";
        animation(str);

        char response;
        cin>>response;

        if(response == 'Y' or response == 'y')
        {
            goto label1;
        }
        else if(response == 'N' or response == 'n')
        {
            str = "We are sad to see you go! \n ";
            animation(str);

            str = "----------------------------------------------------------------------------------------------------------------------\n";
            animation(str);

            str = "We hope we will be able to provide you your dream house next time! \n Have a Good Day!\n";
            animation(str);
            
        }
    }
    pair<int,int>ret = make_pair(0,0);
    return ret;
}

//function to check if the ratings given are within bounds

bool checkRatings(int n)
{
    if(n < 1 || n > 5)
    {
        return false;
    }
    else{
        return true;
    }
}

//function to show the feedback data in form of a table

void createTable(string s[],int arr[])
{
    string str;
    str = "***************************************\n";
    animation(str);

    cout
        << left
        << setw(3)
        << " | "

        << left
        << setw(25)
        << "Criteria"

        << left
        << setw(3)
        << " | "

        << left
        << setw(5)
        << "Rating"

        << left
        << setw(3)
        << "| "

        << endl<<endl;
    for (int i = 0; i < 5; i++)
    {
        cout
            << left
            << setw(3)
            << " | "

            << left
            << setw(25)
            << s[i]

            << left
            << setw(3)
            << " | "

            << left
            << setw(5)
            << arr[i]

            << left
            << setw(3)
            << " | "

            << endl;
    }
    str = "***************************************\n";
     animation(str);

}

// function to collect the feedback from a person regarding the project

void Feedback()
{
    string str;
    str = "Hey Buyer, Glad you Made it upto here !!!! \n\nKindly spare a few moments to fill out this feedback form \n\nIt helps us making your experience better =) \n\n";
    animation(str);

    str = "On a scale of 1 to 5 (5 being the best and 1 being the worst) \n\n\nFill the below Entries \n";
    animation(str);

    int arr[5];
    string s[5] = {"Understanding","Applying","Conceptual Learning","Practical learning","Overall Project"};
    bool chk;

  labelp1:
    str = "\nGive marks for Understanding --> ";
    animation(str);

    cin>>arr[0];
    chk = checkRatings(arr[0]);

    if(!chk)
    {
        str = "Invalid ratings entered!\n";
        animation(str);
         //if ratings are not within bounds label will take u back.
        goto labelp1;
    }
    labelp2:

    str = "\nGive marks for Applying      --> ";
    animation(str);

    cin>>arr[1];

    chk = checkRatings(arr[1]);

    if(!chk)
    {
        str = "Invalid ratings entered!";
        animation(str);
         // "   "   "   "   "   "   "   "   "   "   "   "   "   ".
        goto labelp2;
    }

    labelp3:

    cout<<"\nGive marks for Conceptual Learning--> ";
    cin>>arr[2];

    chk = checkRatings(arr[2]);

    if(!chk)
    {
        str = "Invalid ratings entered!";
        animation(str);
     // "   "   "   "   "   "   "   "   "   "   "   "   "   ".
        goto labelp3;
    }

    labelp4:

    str = "\nGive marks for Practical learning -> ";
    animation(str);

    cin>>arr[3];

    chk = checkRatings(arr[3]);

    if(!chk)
    {
        str = "Invalid ratings entered!";
        animation(str);
        // "   "   "   "   "   "   "   "   "   "   "   "   "   ".
        goto labelp4;
    }

    labelp5:

    str = "\nGive marks for Overall Project --> ";
    animation(str);

    cin>>arr[4];

    chk = checkRatings(arr[4]);

    if(!chk)
    {
        str = "Invalid ratings entered!\n";
        animation(str);
        // "   "   "   "   "   "   "   "   "   "   "   "   "   ".
        goto labelp5;
    }

    str = "\n****************************************\n";
    animation(str);

    str = "thanks\n \n";
    animation(str);

    str = "Your respective Overall Ratings are :\n\n";
    animation(str);

    createTable(s,arr);

}

// function to facilitate administrator use.

void administratorUse()
{
    //function to clear screen whenever this function gets excecuted.

    string str;
    system("cls");
    //for sellers;
    int x;

    str = "Select the Operation you want to perform \n 1. Add a new Property \n 2. Delete a Property\n 3. Display Houses in city \n 4. Display Houses in a sector \n 5. Check sector presence \n 6. Check house vacancy \n 7. Exit \n";

    animation(str);
    cin>>x;

    int n,sector,HouseNumber,d;
    bool ans;
    Node* head = NULL;
    Node* tail = NULL;

    switch(x)
    {
        //for adding new property
        case 1 :  

 labelq1:

        str = "Enter sector No.\n";
        animation(str);
        cin>>n;

        if(n>Wave_City.size())
        {
            str = "Entry Beyond Bounds \n Try Again! \n";
            animation(str);
            goto labelq1;
        }
        head = Wave_City[n-1];
        tail = findTail(Wave_City[n-1]);


 labelq2:
        str = "Enter house No.\n";
        animation(str);
        cin>>d;

        ans = isHouseVacant(head, d);

        if(ans)
        {
            str = "The house with this number is already present! \n Kindly, Enter a different house number\n";
            animation(str);

            goto labelq2;
        }

        else
        {
            insertAtTail(tail, d);
            str = "House added successfully! \n";
            animation(str);

            //sorting houses after every successful insertion.

            selectionSort(head);
        }


        str = "Press any key to Continue \n";
        animation(str);

        getch();
        administratorUse();

        break;

        //for deleting a previous present property
        case 2 :

labeld1:

        str = "Enter sector No.\n";
        animation(str);

        cin>>n;

        if(n>Wave_City.size())
        {
            str = "Entry Beyond Bounds\n Try Again!\n";
            animation(str);
            goto labelq1;
        }
        head = Wave_City[n-1];
        tail = findTail(Wave_City[n-1]);

labeld2:
        str = "Enter house No. \n";
        animation(str);

        cin>>d;
    if(d%100 == 1)
        {
            str = "This house cannot be deleted \n This belongs to authorities\n";
            animation(str); 
            goto labeld1;
        }
    else
    {
        ans = isHouseVacant(head, d);

        if(!ans)
        {
            str = "The house with this number is not present! \n Kindly, Enter a different house number\n";
            animation(str);
            goto labeld1;
        }
        else
        {
        deleteNode(head,d);
        }
    }

        str = "Press any key to Continue \n";
        animation(str);

        getch();
        administratorUse();

        break;

        //to display houses in whole city
        case 3 :

        displayHouses(Wave_City);

        str = "Press any key to Continue \n";
        animation(str);

        getch();
        administratorUse();

        break;

        //to display houses in a sector
        case 4 :

        str = "Enter sector No.\n";
        animation(str);

        cin>>sector;

        displayHousesInSector(Wave_City[sector-1]);

        str = "Press any key to Continue\n";
        animation(str);

        getch();
        administratorUse();

        break;

        //to check if sector is vacant/present for business
        case 5 :

        str = "Enter sector No.\n";
        animation(str);

        cin>>sector;

        ans = isSectorVacant(Wave_City[sector-1]);
        if(sector>5)
            ans = false;
        if(ans)
        {
        str = "Yes sector is present!";
        animation(str);
        }
        else
        {
        str = "No this sector is not present! \n";
            animation(str);
        }

        str = "Press any key to Continue\n";
        animation(str);

        getch();
        administratorUse();

        break;

        //to check house presence
        case 6 :
labelu2:

        str = "Enter sector No. \n";
        animation(str);
        cin>>n;

        if(n>5)
        {
            str = "Entry Out of bound!\n";
            animation(str);
            goto labelu2;
        }
        head = Wave_City[n-1];

        str = "Enter House Number \n";

        animation(str);
        cin>>HouseNumber;

        ans = isHouseVacant(head,HouseNumber);

        if(ans)
        {
            str = "Yes house is already present \n";
            animation(str);
        }
        else
        {
            str = "No houses is not present \n";
        animation(str);
        }


        str = "Press any key to Continue\n";
        animation(str);

        getch();
        administratorUse();

        break;

        //to exit administrator use
        case 7 :

            logIN();

        break;

        //if wrong entry is given
        default :

        str = "Wrong choice !! \n Try again \n";
        animation(str);

        str = "Press any key to Continue\n";
        animation(str);

        getch();

        administratorUse();

    }

}

// function to facilitate visitor/viewer/buyer use.
void visitorUse()
{
    string str;
    //function to clear screen whenever this function gets excecuted.
    system("cls");

    int x;
    str = "Welcome !!!! \n";
    animation(str);
    //cout<<"Glad to see you again"<<endl;

    str = "Select the Operation you want to perform \n 1. Display Houses in city \n 2. Display Houses in a sector \n 3. Check sector presence \n 4. Check house vacancy \n 5. Book a house \n 6. Exit\n";
           cout<<endl;
    animation(str);

    cin>>x;
    int n,sector,HouseNumber,d;
    bool ans;
    Node* head = NULL;
    Node* tail = NULL;
    pair<int,int>booked;
    string name;
    long mobile;

    switch(x)
    {
        //to display houses in the whole city
        case 1 :

        displayHouses(Wave_City);

        str = "Press any key to Continue\n";
        animation(str);

        getch();
        visitorUse();

        break;

        //to display houses in a sector
        case 2 :
        
        if(sector>5)
        ans = false;

        if(ans)
        {
        str = "Yes sector is present! \n";
        animation(str);
        }
        else
        {
        str = "No this sector is not present! \n";
        animation(str);
        }

        str  = "Enter sector No. \n";
        animation(str);

        cin>>sector;

        displayHousesInSector(Wave_City[sector-1]);

        str = "Press any key to Continue\n";
        animation(str);

        getch();
        visitorUse();

        break;

        //to check sector vacancy or presence for business
        case 3 :

        str = "Enter sector No. \n";
        animation(str);

        cin>>sector;

        ans = isSectorVacant(Wave_City[sector-1]);

        if(sector>5)
            ans = false;

        if(ans)
        {
        str = "Yes sector is present! \n";
        animation(str);
        }

        else
        {
        str = "No this sector is not present! \n";
        animation(str);
        }

        str = "Press any key to Continue \n";
        animation(str);

        getch();
        visitorUse();

        break;

        //to check house presence
        case 4 :
    labelu3:

        str = "Enter sector No. \n";
        animation(str);

        cin>>n;

        if(n>5)
        {
            str = "Entry Out of Bounds!\n";
            animation(str);

            goto labelu3;
        }

        head = Wave_City[n-1];

        str = "Enter House Number \n";
        animation(str);

        cin>>HouseNumber;

        ans = isHouseVacant(head,HouseNumber);

        if(ans)
        {
        str = "Yes house is already present \n";
        animation(str);
        }
        else
        {
        str = "No this house is not present! \n";
        animation(str);
        }


        str = "Press any key to Continue\n";
        animation(str);

        getch();
        visitorUse();

        break;

        //to book a house of your dreams :)
        case 5 :

        booked = usersChoiceForSector(Wave_City);
        

        if(booked.first == 0)
        {
        str = "Booking was not completed\n";
        animation(str);
        }

        else
        {
            cout<<"Please Enter Your Name :";
            cin>>name;
            cout<<"Enter your mobile no.";
            cin>>mobile;
        fstream fout;
        fout.open("Wavecity.txt",ios::app);
        fout<<name<<" "<<booked.first<<" "<<booked.second<<" "<<mobile<<endl;
        str = "Congratulations!!!! \n Your house ";
        animation(str);
        cout<<booked.second;

        str =" is successfully booked in sector";
        animation(str);
        cout<<booked.first<<endl;

        }


        getch();

        visitorUse();

        break;

        //to exit visitor use
        case 6 :

            logIN();

        break;

        //if wrong input is given
        default :

        str = "Wrong choice !!!!! \n Try again";
        animation(str);

        str = "Press any key to Continue";
        animation(str);

        visitorUse();

    }

}

// main function of this project.
// contains all functions used inside it
// used to use the program.

void logIN()
{
    system("cls");
    int n;
    string str = "Welcome User!!!!\n Enter Your Preference :\n 1. If you are a Seller press '1'\n 2. If you are a Buyer press '2'\n 3. If you want to exit the program press '3'\n";
    // cout<<"Enter Your Preference : "<<endl;
    // cout<<"1. If you are a Seller press '1'"<<endl;
    // cout<<"2. If you are a Buyer press '2'"<<endl;
    // cout<<"3. If you want to exit the program press '3'"<<endl;
    for(int i=0; i<str.length(); i++)
    {
        cout<<str[i];
        Sleep(15);
    }
    cin>>n;

    //go into administrator use
    if(n==1)
    {
        bool x = checkPass();
        if(x)
        {
            administratorUse();
        }
        else
        {
            str = "errrr!!! Wrong Password\n Try Again\n";
            animation(str);
            logIN();
        }
    }
    
    //go into visitor use
    else if(n==2)
    {
        visitorUse();
    }

    //go to fill feedback form
    else if(n==3)
    {
        str = "Thanks for visiting \n Kindly on your way out please fill out our FEEDBACK FORM \n";
        animation(str);
        str = "Press any key to Continue\n";
        animation(str);
        str = "*******************************************************\n";
        animation(str);
        getch();

        int w;

        str = "\nDo you want to fill out the feedback form\n";
        animation(str);
        str = "\nPress 1 for 'YES' and any other key for 'NO' \n";
        animation(str);
        cin>>w;

        if(w == 1)
        {
            Feedback();
        }
        else
        {
           str = "THANKS FOR GIVING US YOUR TIME! \n";
            animation(str);
            getch();
            exit(0);
        }
    }

    else
    {
       str = "Wrong Choice!!!!!!\n";
       animation(str);
       str = "Press any key to Continue\n";
       animation(str);

       getch();
       logIN();
    }

}

int main()
{
    //Some predefined sectors for use
    // necessary for operation.

    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* head3 = NULL;
    Node* head4 = NULL;
    Node* head5 = NULL;

    insertAtHead(head1,101);
    insertAtHead(head2,201);
    insertAtHead(head3,301);
    insertAtHead(head4,401);
    insertAtHead(head5,501);

    Wave_City.push_back(head1);
    Wave_City.push_back(head2);
    Wave_City.push_back(head3);
    Wave_City.push_back(head4);
    Wave_City.push_back(head5);


    //calling of the main/driver function.

    logIN();

    return 0;
}

// planning to take this project further to turn it into a major project :)
// Wave_City Real-Estate project
// Prepared by :--   1. Raghav Dixit            21103161
//                   2. Keshav Singh Solanki    21103152
//                   3. Priyanshu Choudhary     21103157