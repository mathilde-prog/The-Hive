CC = gcc
OBJ = inventory.o items.o equipment.o menu_test.o

all: inventory_equipment_management

inventory_equipment_management: $(OBJ) structure.h
	$(CC) -o $@ $(OBJ)

equipment.o: equipment.c
	$(CC) -c $<

inventory.o: inventory.c
	$(CC) -c $<

items.o: items.c
	$(CC) -c $<

menu_test.o: menu_test.c
	$(CC) -c $<

clean:
	rm -rf *.o

mrproper: clean
	rm -rf inventory_equipment_management
