# coding : utf-8
'''
Adaptator class
It resize the image to the given resolution 
then normalize the image with the given equation

usage :
ada = Adaptator(OUTPUT_HEIGHT, OUTPUT_WIDTH)
ada.imgLoad(IMG_PATH)
ada.normalize()

result -> ada.output_image
'''
from math import sqrt
from pprint import pprint 

class Adaptator:

    input_img   = [] # Original image
    cropped_img = [] # Cropped image
    output_img  = [] # Adapated image

    img_len = 0     # Pixels number
    img_mu  = []    # Image average value on each component [R,G,B]
    img_sig = []    # Image std deviation on each component [R,G,B]

    size_x  = 24
    size_y  = 24
    comp_nb = 3

    def __init__(
        self, 
        output_height, 
        output_width
        ):
        self.size_x     = output_width
        self.size_y     = output_height
        self.output_img = [[[0 for c in range(self.comp_nb)] for i in range(self.size_x)] for j in range(self.size_y)] # initialize output image with null vector
        self.img_mu     = 0
        self.img_sigma  = 0

    def imgLoad(self, img):
        self.img_mu = 0
        self.img_sigma = 0
        self.input_img  = img # useless atm
        self.img_len    = len(img)*len(img[0])*len(img[0][0])
        self.comp_nb    = len(img[0][0])
        self.cropped_img = []
        # crop image
        if len(img) < self.size_y or len(img[0]) < self.size_x:
            print("Input image smaller than expected output image")
            return 0

        sxi      = len(img[0]) # input image size x
        syi      = len(img)    # input image size y
        margin_x = int((sxi - self.size_x)/2)
        margin_y = int((syi - self.size_x)/2)

        for l in range(margin_y, margin_y + self.size_y):
            self.cropped_img.append([])
            for c in range(margin_x, margin_x + self.size_x):
                self.cropped_img[-1].append(img[l][c])

        self.img_len = len(self.cropped_img)*len(self.cropped_img[0])*len(self.cropped_img[0][0])

        # mu
        for l in list(self.cropped_img):
            self.img_mu += sum([sum(c) for c in l])

        self.img_mu = (1./self.img_len) * self.img_mu

        # sigma
        for l in self.cropped_img:
            for c in l:
                for z in c:
                    self.img_sigma += (z-self.img_mu)**2 
        self.img_sigma = sqrt(1./self.img_len * self.img_sigma)
    
        # print("µ : {} ; σ : {}".format(self.img_mu, self.img_sigma))
        
        return 1
    
    def normalize(self):
        for l in range(self.size_x):
            for c in range(self.size_y):
                for i in range(self.comp_nb):
                    self.output_img[l][c][i] = (self.cropped_img[l][c][i] - self.img_mu)/max(self.img_sigma, 1./sqrt(self.img_len))

        return 1

    def writeImg(self):
        fp = open("../HLS/include/img.h", "w")
        str =  "#ifndef _IMG_H_\n"
        str += "#define _IMG_H_\n\n"
        str += "#include \"types.h\"\n\n"
        str += "static dType img[1728] = {\n"
        i = 0
        for z in range(self.comp_nb):
            for y in range(self.size_y):
                for x in range(self.size_x):
                    str += "{}".format(self.output_img[x][y][z])
                    if (i % 8 == 0 and i != 0):
                        str += ",\n"
                    else:
                        if (z == (self.comp_nb-1) and y == (self.size_y-1) and x == (self.size_x-1)):
                            str += "\n"
                        else:
                            str += ","
                    i+=1
        str += "};\n\n#endif\n"
        fp.write(str)

# testing
if __name__ == "__main__":
    from time import time
    from matplotlib.pyplot import imread, subplots, show
    
    IMG_HEIGHT = 24
    IMG_WIDTH  = 24

    t0 = time()
    img = imread("tests/airplane1.png")
    adap = Adaptator(IMG_HEIGHT,IMG_WIDTH)
    if adap.imgLoad(img):
        adap.normalize()
        adap.writeImg()
    else:
        exit()
    t1 = time()
    print("Total processing time : {} ms\n".format((t1-t0)*1000))

    # fig, axs = subplots(1, 2, figsize=(7, 4))
    # fig.canvas.manager.set_window_title('Normalization result')
    # axs[1].imshow(adap.output_img)
    # print(adap.output_img)
    # axs[1].set(title="Output image")
    # axs[0].imshow(adap.input_img)
    # axs[0].set(title="Input image")
    # show()
    
