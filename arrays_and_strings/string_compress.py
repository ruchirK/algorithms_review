#Computes easy string compression of the form
#input sssssttrring
#output s5t2r2i1n1g1

#if the resultant "compression" takes more space than
#the original, the original is returned

def string_compress(string):
    if isinstance(string, basestring) is not True:
        print "ERROR: Please input a string"
        return 
         
    i = 0
    j = 0
    new_str = ""
    while j < len(string):
        if string[j] == string[i]:
            j = j +1
        else:
            new_str = new_str + string[i] + str(j - i)
            i = j;
            j = j + 1;

    new_str = new_str + string[i] + str(j -i)

    if len(new_str) > len(string):
        return string
    else:
        return new_str


def main():
    string = "testsssssssssssssssssssssssssssstringggg"

    print string, string_compress(string)

main()
