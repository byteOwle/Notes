def IntToBin(dec_num):
    binary_num= bin(dec_num).replace('0b', '')
    return binary_num

def fixedpointToBin(dec_num, bit_size = 16):
    bin_num, out = dec_num, ''
    fractional_sum = 0.0
    while True:
        bin_num = float(bin_num)*2.0
        
        if bin_num >= 1: out += '1' 
        else: out += '0'

        bin_num = float('0' + str(bin_num)[1:])

        #print('dec_num: ', bit_size )
        bit_size -= 1

        if bin_num == 1 or bit_size <= 0: break

    for i in range(0, len(out)):
        if int(out[i]) == 1:
            fractional_sum += pow(2, -(i+1))
    
    hex_rep= ''; 
    for i in range(0, len(out), 4):
        Four_bit = int(out[i:i+4],2)
        hex_rep += format(Four_bit, 'X')
        

    return out, fractional_sum, hex_rep


mode = int(input('(1) Bin to Float(not IEEE) | (2) Float(not IEEE) to Bin: '))

if mode == 1:
    number = input('Enter a Binary number:')
    int_number= int(number, 2)
    fixed_number= float(int_number)
    print('The Fixed conversion is:', fixed_number)

if mode == 2:
    number = input('Enter a fixed number:')
    num_fixed = str(float(number))
    num_split = number.split('.')
    fraction_bin = '0'
    fixed_Bin = '0'
    fixedToBin = 0
    bit_size = 16
    fraction_sum = 0.0
    hex_rep = ''
    wholN_bitSize = 4
    fracN_bitSize = 12
    test = ''


    if len(num_split) == 1:
        integer = int(num_split[0])
        fixedToBin = IntToBin(integer)
    else: 
        integer, fraction = int(num_split[0]), num_split[1]
        integer_bin = IntToBin(integer)
        BinFiller = "".join(['0' for i in range(0, wholN_bitSize - len(integer_bin))])
        fraction_bin, fraction_sum, hex_rep = fixedpointToBin('.' + fraction, fracN_bitSize)
        fixed_Bin = BinFiller+integer_bin + '.' + fraction_bin
        fixed_Bin = fixed_Bin[0:bit_size]
              
        
    print(type(num_fixed))
    print('The Float conversion is:', num_fixed)
    print('The split:', num_split)
    print('Whole Number: ', integer)
    print('Whole Number Bin: ', fixedToBin)
    print('Fractional part: ', fraction_bin)
    print('Fractional Sum: ', fraction_sum)
    print('Float Binary Rep: ', fixed_Bin)   
    print('Hexadecimal Rep: ', str(integer)+hex_rep)
    print('Bit Size: ', len(fixed_Bin))