make:
	g++ -c main.cc
	g++ -o program.exe main.o
	rm *.o
	@echo "********************************************************************"
	@echo "*                                                                  *"
	@echo "*  To execute the program: ./program.exe param1 [param2] [param3]  *"
	@echo "*  param1: INPUT FILE, example: ./file.txt                         *"
	@echo "*  param2: N (length of soup), example: 10                         *"
	@echo "*  param3: MAX WORD LENGTH, example: 10                            *"
	@echo "*                                                                  *"
	@echo "********************************************************************"