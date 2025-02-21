RAIN_CHECK = 75

Rainfull_mi="45,65,70.4,82.6,20.1,90.8,76.1,30.92,46.8,67.1,79.9"
num_rainy_months = 0

Rain_split=Rainfull_mi.split(',') #spliting the string 
for mi_int in Rain_split:
   mi=float(mi_int) #convert to float
   if(mi>RAIN_CHECK):
        num_rainy_months +=1


      
    
