CC = icpc  -g
CFLAGS = #-O3 

C = $(CC) $(CFLAGS)
EXEC = SFwhguan

.PHONY : clean

$(EXEC):
	$(C) -c $(EXEC).cpp
	$(C) $(EXEC).o -o $(EXEC)
SF:
	./$(EXEC)  T1whguan.txt
clean:
	rm -f *.o
	rm -f $(EXEC)
	echo "clean obj"
