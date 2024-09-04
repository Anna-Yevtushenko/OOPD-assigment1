# Airflight Booking System

## Task 🛠️


Develop a console-based  airplane  ticket  booking system. The system should read input 
configuration from a text file and allow users to book tickets via a command -line user interface. 
Emphasis should be placed on encapsulating the data and behavior within well-organized classes.

---

## Class Decomposition: 

Class `Airplane`

```java
    class Airplane {
    private:
    int numberOfSeats;          
    boolean[] seatAvailability; 
    
```

Class `Ticket`

```java
 class Ticket {
 private:
 String passengerName;  
 int seatNumber;        
 Airplane flightInfo;   
 String bookingStatus;  
    
}
    
```
## Command-line Interface:

Develop a user interface that allows users to perform the following commands:  

▪ Check seat availability. 


▪ Book a ticket. 


▪ Return a ticket. 


▪ View booked tickets. 


> [!WARNING]
> Each of these commands should be implemented as methods in the main program, 
> which interact with the Airplane and Ticket classes.
> 


<img src="https://github.com/user-attachments/assets/26304e99-296f-47f1-940b-8fcffcf01f2c" style="height: 600px;"/>
</div>





## Encapsulation: 
Ensure that the Airplane and Ticket classes encapsulate their data members and 
provide public methods to interact with them. For instance, booking a ticket 
should be done through a method in the Airplane class that ensures the 
encapsulated seat availability data is updated correctly. 

## Data Validation: 
Implement data validation within the classes. For example, when booking a ticket, 
validate that the requested seat is available.

## File Handling:
Encapsulate file reading operations in a separate class (e.g., FileReader) to 
promote encapsulation and separation of concerns, also to allow working with 
different file formats in the future by replacing only 1 class in the code. 

## Error Handling: 
Implement error handling to gracefully handle situations like invalid input or file 
not found errors.

## Documentation / theory learning:
Include clear comments and documentation to explain how encapsulation 
principles are applied within the project


Example of the input configuration file (// please ignore comments!!!):

![image](https://github.com/user-attachments/assets/46a76daa-e4b2-4076-b071-bdccb4f16544)


Explanation of a plane seat map (just as example):
![image](https://github.com/user-attachments/assets/e279d528-f517-4f4b-85c6-52a70e742400)




<details>
<summary>Code example🖥️ </summary>

---
In this example, the Student class encapsulates the name and age data members and provides getter 
and setter methods to access and modify them, respectively. :

   ```sh
   #include <iostream> 
#include <string> 
 
class Student { 
private: 
    std::string name; 
    int age;
public: 
    // Constructor to initialize the object 
    Student(const std::string& n, int a) : name(n), age(a) {} 
 
    // Getter method for the name 
    std::string getName() const { 
        return name; 
    } 
 
    // Setter method for the age 
    void setAge(int a) { 
        if (a >= 0 && a <= 120) { 
            age = a; 
        } 
        else { 
            std::cout << "Invalid age!" << std::endl; 
        } 
    } 
}; 
 
int main() { 
    // Creating a Student object 
    Student student("Alice", 20); 
 
    // Accessing and modifying private data using getter and setter 
    std::cout << "Student's name: " << student.getName() << std::endl; 
    student.setAge(22); 
    std::cout << "Student's age: " << student.getName() << std::endl; 
 
    // Trying to set an invalid age 
    student.setAge(150); // Outputs "Invalid age!" 
 
    return 0; 
}
```
---
This example shows encapsulation within an inheritance hierarchy. The Person class encapsulates 
the name attribute, and the Student class extends Person and encapsulates the age attribute. 
```sh

#include <iostream> 
#include <string> 
 
class Person { 
private: 
    std::string name; 
 
public: 
    Person(const std::string& n) : name(n) {} 
 
    std::string getName() const { 
        return name; 
    } 
}; 
 
class Student : public Person { 
private: 
    int age;
public: 
    Student(const std::string& n, int a) : Person(n), age(a) {} 
 
    int getAge() const { 
        return age; 
    } 
}; 
 
int main() { 
    Student student("Bob", 18); 
 
    std::cout << "Student's name: " << student.getName() << std::endl; 
    std::cout << "Student's age: " << student.getAge() << std::endl; 
 
    return 0; 
} 
 
```

---

</details>



## Task milestones 
1. Design your  system on  the paper or by  using some online tools, please use squares and 
arrows to draw classes and their relations, no specific notation is needed in this task, think 
in advance how would your system look like. 
2. Implement the I/O system to parse input file, create a class for user input processing 
3. Implement logic to book the ticket, create appropriate classes and relations between them, 
consider effective data structures 
4. Implement logic to view booking results 
5. Test the solution, develop your own input data files 

## Control questions  

1. Explain data abstraction and encapsulation programming technique. 
2. What is an interface? 
3. Which access specifiers do you know? 
4. What is the difference between struct and class in C++? 
5. What is this pointer? 
6. How can you initialize fields in the object? 
7. What is constructor? 
8. What is destructor? 
9. What is a friend class? 
10. What is const member function? 
11. What does mutable data member? 
12. What is objects composition?

---




## Assessment 🌟 
  - Encapsulation and data abstraction 
principles usage  - 3
  - Correct view functionality and optimal 
data structures usage - 3
  - Effective memory usage  - 1
  - System design (test description, photo of 
your notes or some diagrams) - 1
  - Git (3+ meaningful commits) - 1
  - Extra: RAII  wrapper around system file 
calls (winapi/posix) - 1
- Test in Moodle - 1

**Total 10 + 1**
