#include "employees.h"
#include "company.h"
#include "queueEmp.h"
#include<iostream>

using namespace std;
void main()
{
	company mt;
	
	int choice=0;
	
	while (1)
	{
		cout << "\n\n1.create new employee\n2.Display names of employee from a particular year of joining\n3.details of the employee from a particular department having the highest pay";
		cout << "\n4.Display all details of all employees in ascending order\n5.Update pay by employee id ";
		cout << "\n6.Move Employee from project to bench\n7.Move Employee from bench to project";
		cout << "\nEnter choice ";
		choice = mt.validation();
		
		switch (choice)
		{
		case 1:
			mt.createNewEmployee();
			break;
		
		case 2:
			mt.namesFromDateOfJoining();
			break;
		case 3:
			mt.employeeWithHighPay();
			break;
		case 4:
			mt.displayDetails();
			break;
		case 5:
			mt.updatePay();
			break;
		case 6:
			mt.enqueue();
			break;
		case 7:
			mt.dequeue();
			break;
		case 0:
			exit(0);
		default:
			cout << "\nEnter valid choice ";
		}
		
	}
	cin.clear();
	cin.ignore(1000,'\n');
	cin.get();
}