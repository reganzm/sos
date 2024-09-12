.text
.code32

start32:
    # print 'Z' into serial
    mov $0x3f8,%dx
    mov $'Z',%al
    out %al,%dx

    hlt