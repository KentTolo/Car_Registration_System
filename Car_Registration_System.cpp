/*
===================================================================================
Authors: Sello M.F  202100003 & Tolo K.J 202100092
Date: 04 December 2023
Title: Security System Test1.cpp

==================================================================================
*/

#include <iostream>
#include <string>
using namespace std;

// ADT declarations
struct passenger

{
    string passport_no;
    string surname;
    char gender;
};

struct car
{
    int registration_no;
    int driver_id;
    string car_make;
    passenger car_passengers[15];
    int last; // number of passengers of the car
};

struct car_node
{
    car a_car;
    car_node *next;
    car_node *prev;
};

// Securty system declaration using a doubly linked list

class security_system
{
public:
    security_system()
    {
		first_car = nullptr;
    	last_car = nullptr;
    	passengers = new passenger[10000]; // Assuming the maximum capacity of the security system is 1000 passengers
    	registered_passengers = 0;
	}
   ~security_system()
    {
    	delete[] passengers;
	};
    void register_car(car new_car);
    void deregister_car(int reg_no);
    void search_passenger(string passport_num);
    void display_all();
    void display_car(int reg_no);
    void edit(int reg_no,passenger someone);
    void edit(int reg_no,int driverID);

private:
    car_node *first_car;
    car_node *last_car;
    passenger *passengers;
    int registered_passengers; //  This keeps track of the number of passengers currently in the system
};

void security_system::register_car(car new_car)
{

    if (first_car==nullptr)
    {
        first_car=new car_node;
        first_car->a_car=new_car;
        for (int i=0;i<new_car.last+1;i++)
        {
            passengers[i]=new_car.car_passengers[i];
        }
    }
    else
    {
        last_car=new car_node;
        last_car->next->a_car=new_car;
        last_car=last_car->next;
        int n=0;
        for (int j=registered_passengers++;j<registered_passengers+new_car.last;j++)
        {
            passengers[j]=new_car.car_passengers[n];
            n++;
        }
    }
}

void security_system::deregister_car(int reg_no)
{
    car_node *temp_car = first_car;
    while (temp_car != nullptr)
    {
        if (temp_car->a_car.registration_no == reg_no)
        {
            if (temp_car->prev != nullptr)
            {
                temp_car->prev->next = temp_car->next;
            }
            else
            {
                first_car = temp_car->next;
            }

            if (temp_car->next != nullptr)
            {
                temp_car->next->prev = temp_car->prev;
            }
            else
            {
                last_car = temp_car->prev;
            }

            // Update the list of registered passengers
            for (int i = 0; i < temp_car->a_car.last; ++i)
            {
                for (int j = 0; j < registered_passengers; ++j)
                {
                    if (temp_car->a_car.car_passengers[i].passport_no == passengers[j].passport_no)
                    {
                    	for (j;j < registered_passengers; ++j)
                    	{
                    		passengers[j] = passengers[j+1];

						}
                        registered_passengers--;

                    }
                }
            }

            delete temp_car;
            return;
        }
        temp_car = temp_car->next;
    }

    cout << "Car not found in the system!" << endl;
}

void security_system::search_passenger(string passport_num)
{
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Searcing for passenger"<<endl;
	cout<<"Search criteria (Passport Number) "<<passport_num<<endl;
	cout<<"---------------------------------------------------------\n"<<endl;
    for (int i = 0; i < registered_passengers; ++i)
    {
        if (passengers[i].passport_no == passport_num)
        {
        	cout<<"Passenger found!\n"<<endl;
            car_node *temp_car = first_car;
            while (temp_car != nullptr)
            {
                for (int j = 0; j < temp_car->a_car.last; ++j)
                {
                    if (temp_car->a_car.car_passengers[j].passport_no == passport_num)
                    {

                        cout << "Car Registration Number: " << temp_car->a_car.registration_no << endl;
                        cout << "Driver ID: " << temp_car->a_car.driver_id << endl;
                        cout << "Car make: " << temp_car->a_car.car_make << endl;

                        for(int p = 0; p<temp_car->a_car.last;p++)
                        {
                        	cout<<"Passenger "<<p+1<<" passport number is: "<<temp_car->a_car.car_passengers[p].passport_no<<endl;
                        	cout<<"Passenger "<<p+1<<" surname is: "<<temp_car->a_car.car_passengers[p].surname<<endl;
                        	cout<<"Passenger "<<p+1<<" gender is: "<<temp_car->a_car.car_passengers[p].gender<<endl;
						}
                        // array display
                        cout<<"=========================================================\n"<<endl;
                        cout<<"\n"<<endl;
                        return;
                    }
                }
                temp_car = temp_car->next;
            }
        }
    }


    cout << "Passenger not found on campus!\n" << endl;
    cout<<"=========================================================\n"<<endl;
}

void security_system::display_all()
{
    car_node *temp_car = first_car;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"All Cars "<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    while (temp_car != nullptr)
    {
        cout << "Car Registration Number: " << temp_car->a_car.registration_no << endl;
        cout << "Driver ID: " << temp_car->a_car.driver_id << endl;
        cout << "Car make: " << temp_car->a_car.car_make << endl;
        cout << "Passengers:" << endl;

        for (int i = 0; i < temp_car->a_car.last; ++i)
        {
            cout << "Passenger " << i + 1 << ":" << endl;
            cout << "  Passport Number: " << temp_car->a_car.car_passengers[i].passport_no << endl;
            cout << "  Surname: " << temp_car->a_car.car_passengers[i].surname << endl;
            cout << "  Gender: " << temp_car->a_car.car_passengers[i].gender << endl;
        }
        temp_car = temp_car->next;
        cout<<"---------------------------------------------------------"<<endl;

    }
    cout<<"=========================================================\n"<<endl;


}

void security_system::display_car(int registration_no)
{
	car_node *temp_car = first_car;
    while (temp_car != nullptr)
    {
    	if(temp_car->a_car.registration_no == registration_no)
    	{
    		cout<<"---------------------------------------------------------"<<endl;
    		cout<<"Car Details"<<endl;
    		cout<<"---------------------------------------------------------"<<endl;
    		cout << "Car Registration Number: " << temp_car->a_car.registration_no << endl;
            cout << "Driver ID: " << temp_car->a_car.driver_id << endl;
            cout << "Car make: " << temp_car->a_car.car_make << endl;
            for(int p = 0; p<temp_car->a_car.last;p++)
            {
                cout<<"Passenger "<<p+1<<" passport number is: "<<temp_car->a_car.car_passengers[p].passport_no<<endl;
                cout<<"Passenger "<<p+1<<" surname is: "<<temp_car->a_car.car_passengers[p].surname<<endl;
                cout<<"Passenger "<<p+1<<" gender is: "<<temp_car->a_car.car_passengers[p].gender<<endl;
			}
			cout<<"---------------------------------------------------------"<<endl;
            cout<<"\n"<<endl;
            return;
		}
		else
		{
			 temp_car = temp_car->next;
		}

    }
    cout<<"Car not found!\n"<<endl;
}
void security_system::edit(int reg_no,passenger new_passenger)
{
    car_node *temp_car=first_car;
    while (temp_car != nullptr)
    {
        if (temp_car->a_car.registration_no==reg_no)
        {
            if (temp_car->a_car.last==15)
            {
                cout<<"Car is full"<<endl;
                break;
            }
            else
            {
                temp_car->a_car.last++;
                temp_car->a_car.car_passengers[temp_car->a_car.last]=new_passenger;
                registered_passengers++;
                passengers[registered_passengers]=new_passenger;
                break;
            }
        }
        else
        {
            temp_car=temp_car->next;
        }
    }
}
void security_system::edit(int reg_no,int driverID)
{
    car_node *temp_car=first_car;
    while (temp_car != nullptr)
    {
        if (temp_car->a_car.registration_no==reg_no)
        {
            temp_car->a_car.driver_id=driverID;
            cout<<"New driver of ID "<<driverID<<" has been assigned to car of registration number "<<reg_no<<endl;
            break;
        }
        else
        {
            temp_car=temp_car->next;
        }
    }
}

void Menu()
{
	cout << "+========================================================+" << endl;
    cout << "     NATIONAL UNIVERSITY OF LESOTHO SECURITY SYSTEM" << endl;
    cout << "+========================================================+"  << endl;
    cout << "||   1. Register a Car                                  ||" << endl;
    cout << "||   2. Deregister a Car                                ||" << endl;
    cout << "||   3. Search for a Passenger                          ||" << endl;
    cout << "||   4. Display All Cars and Passengers                 ||" << endl;
    cout << "||   5. Display Car Details                             ||" << endl;
    cout << "||   6. Edit Car Details                                ||" << endl;
    cout << "||   0. Exit                                            ||" << endl;
    cout << "----------------------------------------------------------\n"<< endl;
    cout << "Enter your choice: ";

}
void subMenu()
{
	cout<<"+----------------------------------------------------------+"<<endl;
	cout<<"|		Edit Details Sub-Menu                      |"<<endl;
	cout<<"+----------------------------------------------------------+"<<endl;
	cout<<"1. Insert New Passenger"<<endl;
	cout<<"2. Change Driver ID "<<endl;
	cout<<"3. Exit \n"<<endl;
	cout<<"Enter your choice: ";
}


int main()
{
    security_system system;
    int choice;
    do
    {
    	Menu();
        cin >> choice;
        switch (choice)
        {
	        case 1:
	        {
	            car new_car;
	            cout << "Enter Car Registration Number: ";
	            cin >> new_car.registration_no;
	            cout << "Enter Driver ID: ";
	            cin >> new_car.driver_id;
	            cout << "Enter Car Make: ";
	            cin >> new_car.car_make;
	            cout << "Enter the number of passengers: ";
	            cin >> new_car.last;

	            for (int i = 0; i < new_car.last; ++i)
	            {
	                cout << "Passenger " << i + 1 << " Passport Number: ";
	                cin >> new_car.car_passengers[i].passport_no;
	                cout << "Passenger " << i + 1 << " Surname: ";
	                cin >> new_car.car_passengers[i].surname;
	                cout << "Passenger " << i + 1 << " Gender (M/F): ";
	                cin >> new_car.car_passengers[i].gender;
	            }

	            system.register_car(new_car);
	            break;
	        }

	        case 2:
	        {
	            int reg_no;
	            cout << "Enter Car Registration Number to Deregister: ";
	            cin >> reg_no;
	            system.deregister_car(reg_no);
	            break;
	        }

	        case 3:
	        {
	            string passport_num;
	            cout << "Enter Passenger's Passport Number to Search: ";
	            cin >> passport_num;
	            system.search_passenger(passport_num);
	            break;
	        }

	        case 4:
	            system.display_all();
	            break;

	        case 5:
	        {
	            int reg_no;
	            cout << "Enter Car Registration Number to Display Details: ";
	            cin >> reg_no;
	            system.display_car(reg_no);
	            break;
	        }

	        case 6:
            {
            	subMenu();
                int option;
                cin>>option;
                if (option==1)
                {
                    passenger new_passenger;
                    cout<<"Enter details of new passenger."<<endl;
                    cout<<"Enter their passport number: "<<endl;
                    cin>>new_passenger.passport_no;
                    cout<<endl<<"Enter Their Gender: ";
                    cin>>new_passenger.gender;
                    cout<<endl<<"Enter Their Surname: ";
                    cin>>new_passenger.surname;
                    cout<<endl<<"Enter Registration Number Of Car You Want To Further Populate: ";
                    int registration;
                    cin>>registration;
                    system.edit(registration,new_passenger);
                    break;
                }
                else if (option==2)
                {
                    int new_ID;
                    cout<<endl<<"Enter ID Of New Driver: "<<endl;
                    cin>>new_ID;
                    cout<<endl<<"Enter registration number of car you want to change driver: "<<endl;
                    int registration;
                    cin>>registration;
                    system.edit(registration,new_ID);

                }

            }
	        case 0:
	            cout << "Exiting the program. Goodbye!" << endl;
	            break;

	        default:
	            cout << "Invalid choice. Please enter a valid option." << endl;
	    }

    } while (choice != 0);

    return 0;
}
