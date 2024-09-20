from PIL import Image


img = Image.open('./s.png')
# 模式L”为灰色图像，它的每个像素用8个bit表示，0表示黑，255表示白，其他数字表示不同的灰度。
Img = img.convert('L')
Img.save("./s.jpg")
# 自定义灰度界限，大于这个值为黑色，小于这个值为白色
maxvalve = 180
table = []
for i in range(256):
    if i < maxvalve :
        table.append(0)
    else:
        table.append(1)

# 图片二值化
photo = Img.point(table, '1')
photo.save("./s_2.jpg")



img=Image.open("./s_2.jpg")
new_img=img.resize((32,32))
w,h=new_img.size
with open("./s.txt", "w") as f:
   for c in range(h):
        for j in range(w):
             f.write(str(int((255-(new_img.getpixel((j,c))))/255)))
             if j==w-1:
                  f.write("\n")
f.close()
