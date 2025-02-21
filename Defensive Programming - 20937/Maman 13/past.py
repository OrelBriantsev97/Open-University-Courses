
words = ["adopt","bake","beam","cook","time","grill","waved","hire"]
past_tense = []

for word in words:
    if(word[-1] == 'e'): #for words that ends with e
        past_tense.append(word + 'd')
    elif(word[-1] != 'd' and word [-2] !='e'): #for words that not ends with 'ed'
        past_tense.append(word +'ed')
    else:
        past_tense.append(word)



