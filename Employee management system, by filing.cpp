#include <iostream>
#include <string>
#include <fstream>

using namespace std;
	//Structures
	struct Employee{
		int employee_id;
		string employee_name;
		string employee_department;
		string employee_status;
		double employee_salary;
	};
	
	//max employees
	const int max_employee=25;
	
	//Functions
	void EmployeesFromFile(Employee employees[], int &total_employees, const string &filename);
	void saveEmployeesDataToFile(Employee employees[], int total_employees, const string &filename);
	void displayEmployeeDetail(Employee employees[], int total_employees);
	void addEmployeeDetail(Employee employees[], int &total_employees, const string &filename);
	void searchEmployeeDetail(Employee employees[], int total_employees);
	void editEmployeeDetail(Employee employees[], int total_employees, const string &filename);
	void deleteEmployeeDetail(Employee employees[], int &total_employees, const string &filename, const string &deleted_filename);
	void saveDeletedEmployeesDataToAnotherFile(Employee &deleted_employee, const string &deleted_filename);

int main(){
	Employee employees[max_employee];
	int total_employees=0;
	
	string filename="Employees.txt";
	string deleted_filename="delete employees.txt";
	EmployeesFromFile(employees, total_employees, filename);
	
	int select_number;
	do
	{
		cout<<"\n\t ====Employee Management System===="<<endl;
        cout<<"\t\t 1. Display Employees"<<endl;
        cout<<"\t\t 2. Add Employees"<<endl;
        cout<<"\t\t 3. Search Employee"<<endl;
        cout<<"\t\t 4. Edit Employee's Data."<<endl;
        cout<<"\t\t 5. Delete Employee's Data"<<endl;
        cout<<"\t\t 6. Exit"<<endl;
        
        cout<<"\n\t Enter Number: ";
        cin>>select_number;
        
        switch(select_number)
		{
            case 1:
                displayEmployeeDetail(employees, total_employees);
                break;
            case 2:
                addEmployeeDetail(employees, total_employees, filename);
                break;
            case 3:
                searchEmployeeDetail(employees, total_employees);
                break;
            case 4:
                editEmployeeDetail(employees, total_employees, filename);
                break;
            case 5:
                deleteEmployeeDetail(employees, total_employees, filename, deleted_filename);
                break;
            case 6:
                cout<<"\n\t Exiting... Thank you!"<<endl;
                break;
            default:
                cout<<"\t Invalid choice. Try again."<<endl;
        }
	}while(select_number!=6);
	
	return 0;
}

	//read from file
	void EmployeesFromFile(Employee employees[], int &total_employees, const string &filename)
	{
    	ifstream employee(filename.c_str());
    	if (!employee)
    	{
    	    return;
    	}

    	total_employees=0;
    	while(employee>>employees[total_employees].employee_id)
    	{
        	employee.ignore();
        	getline(employee, employees[total_employees].employee_name);
        	getline(employee, employees[total_employees].employee_department);
        	getline(employee, employees[total_employees].employee_status);
        	employee>>employees[total_employees].employee_salary;
        	employee.ignore();

        	total_employees++;
    	}
    	
    	employee.close();
    	
}

	
	//save data in file
	void saveEmployeesDataToFile(Employee employees[], int total_employees, const string &filename)
	{
    	ofstream file(filename.c_str());
    	for (int i=0; i<total_employees; ++i)
		{
        	file<<employees[i].employee_id<<endl;
            file<<employees[i].employee_name<<endl;
            file<<employees[i].employee_department<<endl;
            file<<employees[i].employee_status<<endl;
            file<<employees[i].employee_salary<<endl<<endl;
    	}
    	file.close();
	}
	
	
	//Display employee data
	void displayEmployeeDetail(Employee employees[], int total_employees)
	{
		if(total_employees==0)
		{
			cout<<"\n\t No Employee Works yet!"<<endl;
			return;
		}
		for(int i=0; i<total_employees; i++)
		{
			cout<<"\n\t Employee "<<i+1<<": "<<endl;
			cout<<"\t Employee ID: "<<employees[i].employee_id<<endl;
			cout<<"\t Employee Name: "<<employees[i].employee_name<<endl;
			cout<<"\t Employee Department: "<<employees[i].employee_department<<endl;
			cout<<"\t Employee Status: "<<employees[i].employee_status<<endl;
			cout<<"\t Employee Salary: "<<employees[i].employee_salary<<endl;
		}
	}
	
	//Add Employee
	void addEmployeeDetail(Employee employees[], int &total_employees, const string &filename)
	{
		if(total_employees>=max_employee)
		{
        	cout<<"\n\t We have capacity of only 25 employees not Exceed, sorry!"<<endl;
        	return;
    	}
			Employee empl;
			cout<<"\n\t Enter the Detail of employee "<<": "<<endl;
			cout<<"\t Enter employee ID: ";
			cin>>empl.employee_id;
			cout<<"\t Enter employee Name: ";
			cin.ignore();
			getline(cin, empl.employee_name);
			cout<<"\t Employee Department: ";
			getline(cin, empl.employee_department);
			cout<<"\t Employee status(Senior/Junior): ";
			getline(cin, empl.employee_status);
			cout<<"\t Enter Employee Salary: ";
			cin>>empl.employee_salary;
			
			for(int i=0; i<total_employees; i++)
			{
				if(empl.employee_id==employees[i].employee_id)
				{
					cout<<"\n\t Employee with this ID is already exist. \n"<<endl;
					return;
				}
			}
			
			employees[total_employees]=empl;
			total_employees++;
			saveEmployeesDataToFile(employees, total_employees, filename);
			cout<<"\n\t Employee added succesfully!\n"<<endl;
		
	}
	
	//Search Employee
	void searchEmployeeDetail(Employee employees[], int total_employees)
	{
		if(total_employees==0)
		{
			cout<<"\n\t No any employee added yet, please add first. \n"<<endl;
			return;
		}
		
		int search_id;
		int a=0;
		cout<<"\n\t Enter ID of employee about you want to search detail: ";
		cin>>search_id;
		
		for(int i=0; i<total_employees; i++)
		{
			if(search_id==employees[i].employee_id)
			{
				cout<<"\n\t Here is detail of employee: "<<endl;
				cout<<"\t Employee ID: "<<employees[i].employee_id<<endl;
				cout<<"\t Employee Name: "<<employees[i].employee_name<<endl;
				cout<<"\t Employee Department: "<<employees[i].employee_department<<endl;
				cout<<"\t Employee Status: "<<employees[i].employee_status<<endl;
				cout<<"\t Employee Salary: "<<employees[i].employee_salary<<endl;
				a++;
				break;
			}
		}
		
		
		if(a!=1)
		{
			cout<<"\n\t The employee with ID "<<search_id<<" is not found in our record."<<endl;
		}
		
	}
	
	//Edit Employee
	void editEmployeeDetail(Employee employees[], int total_employees, const string &filename)
	{
		if(total_employees==0)
		{
			cout<<"\n\t No any employee added yet, please add first. \n"<<endl;
			return;
		}
		
		int edit_id;
		cout<<"\n\t Enter the ID whose detail you want to edit: ";
		cin>>edit_id;
		
		for(int i=0; i<total_employees; i++)
		{
			if(edit_id==employees[i].employee_id)
			{
				cout<<"\n\t Employee ID: "<<employees[i].employee_id<<endl;
				cout<<"\t Enter the new ID: ";
				cin>>employees[i].employee_id;
				cout<<"\t Employee Name: "<<employees[i].employee_name<<endl;
				cout<<"\t Enter the new name of employee: ";
				cin.ignore();
				getline(cin, employees[i].employee_name);
				cout<<"\t Employee Department: "<<employees[i].employee_department<<endl;
				cout<<"\t Enter the new department of employee: ";
				getline(cin, employees[i].employee_department);
				cout<<"\t Employee Status: "<<employees[i].employee_status<<endl;
				cout<<"\t New Status: ";
				getline(cin, employees[i].employee_status);
				cout<<"\t Employee Salary: "<<employees[i].employee_salary<<endl;
				cout<<"\t Enter new salary: ";
				cin>>employees[i].employee_salary;
				
				saveEmployeesDataToFile(employees, total_employees, filename);
				
				cout<<"\n\t Data updated successfully!"<<endl;
				return;
			}
		}
		cout<<"\n\t The employee with ID "<<edit_id<<" is not found in our record."<<endl;
		
	}
	
	//Delete Employee
	void deleteEmployeeDetail(Employee employees[], int &total_employees, const string &filename, const string &deleted_filename)
	{
		if(total_employees==0)
		{
			cout<<"\n\t No any employee added yet, please add first. \n"<<endl;
			return;
		}
		
		int delete_id;
		cout<<"\n\t Enter ID of employee whoose detail you want to delete: ";
		cin>>delete_id;
		
		for(int i=0; i<total_employees; i++)
		{
			if(delete_id==employees[i].employee_id)
			{
				saveDeletedEmployeesDataToAnotherFile(employees[i], deleted_filename);
				
				for(int j=i; j<total_employees-1; j++)
    			{
    				employees[j]=employees[j+1];
				}
				
				total_employees--;
				saveEmployeesDataToFile(employees, total_employees, filename);
				cout<<"\t Employee with ID "<<delete_id<<" is deleted successfully!"<<endl;
				return;
			}
		}
		cout<<"\n\t The employee with ID "<<delete_id<<" is not found in our record."<<endl;
	}
	
	//Save deleted data in another file
	void saveDeletedEmployeesDataToAnotherFile(Employee &deleted_employee, const string &deleted_filename)
	{
		ofstream file(deleted_filename.c_str(), ios::app);
		
        file<<deleted_employee.employee_id<<endl;
        file<<deleted_employee.employee_name<<endl;
        file<<deleted_employee.employee_department<<endl;
        file<<deleted_employee.employee_status<<endl;
        file<<deleted_employee.employee_salary<<endl<<endl;

        file.close();
	}



