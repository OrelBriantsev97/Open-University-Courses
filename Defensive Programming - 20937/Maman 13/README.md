#  Assignment 13 - Defensive Programming (20937)  

This assignment focuses on Python and Metaprogramming as part of the course "Defensive Programming ".   

##  Question 1 (20%) - List and String Processing  
- **Requirements:**  
  - Write short Python scripts (up to 10 lines) without using functions.  
  - Process the given input data without hardcoding values.  
- **Subsections:**  
  - **a. Conjugating Verbs to Past Tense in English:**  
    - Add "d" to the end of words ending in "e" or "ed" otherwise.  
    - Store the words in past tense in a list called `past_tense`.  
    - **Submit in file:** `past.py`  
  - **b. Counting Rainy Months:**  
    - Check rainfall amounts for different months and count those above 75 mm as rainy.  
    - Store the number of rainy months in the variable `num_rainy_months`.  
    - **Submit in file:** `rain.py`  

---

##  Question 2 (20%) - Classes and Objects in Python  
- **Requirements:**  
  - Write short Python scripts (up to 15 lines) including classes and methods.  
- **Subsections:**  
  - **a. Class `AppleBasket`:**  
    - Constructor accepts color and quantity.  
    - Method `increase()` to increase the quantity by 1.  
    - `__str__()` method to display in the format:  
      - Example1: "A basket of 4 red apples."  
      - Example2: "A basket of 50 blue apples."  
    - **Submit in file:** `fruit.py`  
  - **b. Class `BankAccount`:**  
    - Constructor accepts account name and balance.  
    - `__str__()` method to display in the format:  
      - "Your account, [name], has [balance] dollars."  
    - **Submit in file:** `bank.py`  

---

##  Question 3 (60%) - Metaprogramming and Dynamic Class Creation  
- **Requirements:**  
  - Create a class system with inheritance, including dynamic class and method creation at runtime.  
- **Subsections:**  
  - **a. Dynamic Class System:**  
    - Base Class: `User` with name and profession.  
    - Subclasses based on professions: Engineers, Technicians, Writers, Politicians.  
    - Create new classes at runtime based on user input.  
    - Option to specify a parent class for inheritance.  
    - Display `__name__` and `__dict__` content of the newly created class.  
    - **Submit in file:** `pros.py`  
  - **b. Metaprogramming to Modify Existing Code:**  
    - Accept a Python filename and a line of code.  
    - Add the line of code to all methods in the class defined in the file.  
    - Ensure the correct number of arguments for the methods.  
    - **Submit in file:** `meta.py`  

---




