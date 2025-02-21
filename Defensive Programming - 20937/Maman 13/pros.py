class User:
    def __init__(self,name,profession):
        self.name=name
        self.profession=profession


class Engineer(User):
    def __init__(self, name, major):
        super().__init__(name,f"{major} Engineer")

class ElectricalEng(Engineer):
     def __init__(self, name):
        super().__init__(name,"Electrical")

class ComputerEng(Engineer):
    def __init__(self, name):
        super().__init__(name,"Computer")

class MachineEng(Engineer):
    def __init__(self, name):
        super().__init__(name,"Machine")

class Technician(User):
    def __init__(self, name, major):
        super().__init__(name, f"{major} Technician" )

class Barber(User):
    def __init__(self, name, major):
        super().__init__(name, f"{major} Barber" ) 

class Politician(User):
    def __init__(self, name, major):
        super().__init__(name,  f"{major} Politician") 


Existing_Classes = [User,Engineer,ElectricalEng,ComputerEng,MachineEng,Technician,Barber,Politician]

new_class_name=input("Please enter the name of new class: ")
new_base_class=input("Please enter name of base class (blank if none): ")
baseClass=None

for exClass in Existing_Classes:
    if new_class_name == exClass.__name__:
        print(f"{new_class_name} Class already exist")
        exit()
    if new_base_class ==exClass.__name__:
        baseClass=exClass
    
if baseClass == None and new_base_class !=None:
    print(f"{new_base_class} not exist")
    exit()

new_bclass=(baseClass,)


new_method=input(f"Please enter name of new method for class {new_class_name}: ")
new_attribute=input(f"Please enter name of new attribute for class {new_class_name}: ")

class_dict ={
    new_attribute: None,
    new_method:lambda self :None
}

new_class= type(new_class_name,new_bclass,class_dict)



print(f"Class__name__is: {new_class.__name__}")
print(f"Class__dict__is: {new_class.__dict__}")

                 

  
