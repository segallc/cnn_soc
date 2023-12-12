from Adaptator import *
from ImageRead import *
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

if __name__ == "__main__":
    for i in range(1):
        generateCImg(i)
        subprocess.run("cd ../")