objm+= simple.o
all:
	make -C /lib/modules/$(shell unamer)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell unamer)/build M=$(PWD) clean