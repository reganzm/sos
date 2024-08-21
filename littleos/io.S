global outb

; the c call conversion is : parameter was put in stack from right to left.
; send a byte to an I/O port
; stack :[esp+8] the data byte
;        [esp+4] the i/o port
;        [esp]    return address
outb:
    mov al,[esp+8] ; move the data to be sent into the al register
    mov dx,[esp+4] ; 
    out dx,al
    ret


global inb
; return a byte from the given i/o port 
; stack :[esp+4] the address of the i/0 port
; [esp]  the return address
inb:
    mov dx,[esp+4] ; move the address of the i/o port to the dx register
    in al,dx       ; read a byte from the i/o port and store it in the al register
    ret            ; return the read byte 