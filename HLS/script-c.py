from Adaptator import *
from ImageRead import *
import random
import subprocess

IMG_HEIGHT = 24
IMG_WIDTH  = 24

def generateCImg(index):
    imgObj = ImageRead("../data/cifar10_data/cifar-10-batches-bin/test_batch.bin")
    img, label = imgObj.readImg(index)

    adap = Adaptator(IMG_HEIGHT,IMG_WIDTH)
    if adap.imgLoad(img):
        adap.normalize()
        adap.writeImg()
    else:
        exit()
    return label

if __name__ == "__main__":
    random_number = random.randint(0, 10000)
    # print("Image #", random_number)
    for i in range(100):
        label = generateCImg(i)
        subprocess.run(["make", "main"])
        subprocess.run(["./main"])
        print(label)
