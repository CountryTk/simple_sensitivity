import sys

def parse(file):
    
    with open(file, 'r') as opened_file:
        # print(opened_file.read())
        contents = []
        string = None
        for i in opened_file.readlines():
            contents.append(i)
            
        for j in contents:
            
            if "IBM" in j :
                string = j.replace(" ", "")
        #for k in string:
        for index, char in enumerate(list(string)):
            
            if index == 22:
                
                return "".join(list(string)[index+3:index+5])
           
return_value = parse(sys.argv[1])

with open("value.txt", "w+") as open:
    open.write(return_value)
    open.close()
    