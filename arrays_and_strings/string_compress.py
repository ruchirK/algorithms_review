string = "testsssstringggg"
arr = list()
for i in range (0, len(string)):
    arr.append(0)

character = string[0] 
i = 0
j = 0
new_str = ""
while j < len(string):
    if string[j] == string[i]:
        j = j +1
    else:
        new_str = new_str + string[i] + str(j - i)
        arr.insert(j, string[j])
        i = j;
        j = j + 1;

new_str = new_str + string[i] + str(j -i)

print string, new_str
