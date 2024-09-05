void putch(char ch);
int putchar(int ch);

void say(const char *s){

for (;*s;s++){


#ifdef __ARCH__
	putch(*s);
#else
	putchar(*s);
#endif
}

}
