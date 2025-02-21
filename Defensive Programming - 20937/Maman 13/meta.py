import ast
import astor
import inspect
import random

ARG_UPPER_BOUND = 10000

def Add_Code(source_code,python_code):
    comp_code=ast.parse(source_code)
    for statement in ast.walk(comp_code):
        if isinstance(statement,ast.ClassDef):
            for method in statement.body:
                if isinstance(method,ast.FunctionDef) and method.name != "__init__":
                    method.body.insert(0,ast.parse(python_code).body[0])
                  
    return astor.to_source(comp_code)
        

def main():

    file_name=input("Enter python file name : ")
    python_code=input("Enter a python code: ")
    
    with open(file_name,"r") as file:
        source_code=file.read()
    new_code=Add_Code(source_code,python_code)
    exec(new_code)


main()
