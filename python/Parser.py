# coding : utf-8
'''
Parser class 
read a text file containing coefficients for the convolution operation.
Any coefficient array in the text file must be after a tensor name :
tensor_name:  name
[[v v v v v
  v v v v v]
 [v v v v v
  v v v v v]
    .....
 [v v v v v
  v v v v v]
 [v v v v v
  v v v v v]]

- values in the array must be separated by spaces.
- The array can be written on multiple lines.
- exponential notation is accepted
- new subarray must start on a new line

Parsing result are stored in the coeffs dictionaries with string keys and lists of floats as values
'''
import re
from pprint import pprint
import numpy as np

class Parser:

    f_path    = ""
    coeffs = {}

    def __init__(
        self, 
        f_path
        ):
        self.f_path = f_path

    def readCoeff(self):
        f           = open(self.f_path)
        lines       = f.readlines()
        tensor_name = ""
        array_str   = ""

        for l in lines:
            if l.split(':')[0] == "tensor_name":
                if tensor_name != "":
                    self.coeffs[tensor_name] = array_str

                tensor_name = re.sub(" +", '', l.split(":")[1]).replace('\n','')
                array_str = ""
            elif len(l) > 1:
                tmp_line = re.sub("\[ +",'[', l)        # Removing space after/before bracket to avoid wrong comma insertion
                tmp_line = re.sub(" +\]",']', tmp_line) # ...
                tmp_line = re.sub(" +"  ,',', tmp_line).replace('\n', '') # change space to comma
        
                chr_test = re.match("[\[\]0-9\-,.e]+", tmp_line) # sanetization of input

                if chr_test == None or chr_test.string != tmp_line:
                    print(tmp_line)
                    print(chr_test)
                    print("Invalid character detected.") # could also mean empty line
                    return 0

                array_str += tmp_line
        
        self.coeffs[tensor_name] = array_str

        # translate array_str into a real float array
        #istce_name = [k for k,v in globals().items() if v is self][0] # name of the instance variable
        for k,v in self.coeffs.items():
            exec("self.coeffs['"+k+"'] = "+v)
        
        return 1
    def convertKernel(self, kernels):
        size_y    = len(kernels)
        size_x    = len(kernels[0])
        nb_pixel_c= len(kernels[0][0]) # (= RGB)
        nb_kernel = len(kernels[0][0][0])
        newKernels= np.zeros((nb_kernel, nb_pixel_c, size_x, size_y))
        for x in range(size_x):
            for y in range(size_y):
                for nbc in range(nb_pixel_c):
                    for kl in range(nb_kernel):
                        newKernels[kl][nbc][x][y] = kernels[x][y][nbc][kl]
        
        return newKernels
    def writeCoeff(self):
        fp = open("coeffs.h", "w")
        str = "#ifndef _COEFFS_H_\n"
        str += "#define _COEFFS_H_\n\n"
        str += "#include \"types.h\"\n\n"
        str += "static dType coeffs[112594] = {"
        values = [0.0 for i in range(112594)]
        addr = 0
        index = 0
        kernels = self.convertKernel(self.coeffs['conv1/weights'])
        print(len(kernels))
        print(len(kernels[0]))
        print(len(kernels[0][0]))
        for kl in kernels:
            addr = index*3*3*64
            index += 1
            for nbc in kl:
                for x in nbc:
                    for y in x:
                        values[addr] = y
                        addr += 1 
        addr = 3*3*64*64
        for b in self.coeffs['conv1/biases']:
            values[addr] = b
            addr += 1
        index = 0
        kernels = self.convertKernel(self.coeffs['conv2/weights'])
        for x in kernels:
            addr = 3*3*64*64+64 + index*3*3*64
            index += 1
            for y in x:
                for nbc in y:
                    for kl in nbc:
                        values[addr] = kl
                        addr += 1
        addr = 3*3*64*64*2 + 64
        for b in self.coeffs['conv2/biases']:
            values[addr] = b
            addr += 1
        addr = (3*3*64*64+64)*2
        index = 0
        kernels = self.convertKernel(self.coeffs['conv3/weights'])
        for x in kernels:
            addr = 2*(3*3*64*64+64) + index*3*3*64
            index += 1
            for y in x:
                for nbc in y:
                    for kl in nbc:
                        values[addr] = kl
                        addr += 1
        addr = (3*3*64*64+64)*2 + (3*3*64*64)
        for b in self.coeffs['conv3/biases']:
            values[addr] = b
            addr += 1
        addr = (3*3*64*64+64)*3
        for nbc in self.coeffs['local3/weights']:
            for kl in nbc:
                values[addr] = kl
                addr += 1
        for b in self.coeffs['local3/biases']:
            values[addr] = b
            addr += 1
        
        i = 0
        for e in values:
            str += "{0}".format(e)

            if e != values[-1]:
                str += ",\n"
                i+=1
                if i%8 == 0:
                    str += ""
            else:
                str += "};\n\n"
        str += "#endif"
        fp.write(str)

if __name__ == "__main__":
    from time import time
    from pprint import pprint

    t0 = time()
    prsr = Parser("../data/CNN_coeff_3x3.txt")
    t1 = time()

    print("Total parsing time {} ms".format((t1-t0)*1000))

    
    if prsr.readCoeff():
        prsr.writeCoeff()
    #     # print(prsr.coeffs.keys())
    #     wght = prsr.coeffs["conv2/weights"]

    #     for k, v in prsr.coeffs.items():
    #         print(k, v, "\n\n")
    # else:
    #     print("An error occured.")
