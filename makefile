
a.exe: 	 main.cpp BinTree/STL_bintree_struct.cpp BinTree/STL_bintree_struct.h BinTree/STL_graphviz.cpp BinTree/STL_graphviz.h STL_akinator.cpp STL_akinator.h temp/stack_way_func.o temp/stack_way_error.o STL_Onegin/STL_file_open.cpp STL_Onegin/STL_file_open.h
	 g++ main.cpp BinTree/STL_bintree_struct.cpp BinTree/STL_graphviz.cpp STL_akinator.cpp temp/stack_way_func.o temp/stack_way_error.o STL_Onegin/STL_file_open.cpp -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

temp/stack_way_func.o:
	g++ -c STL_Stack/STL_stack_functions.cpp   -DSTACK_FILE_TYPE=\"../BinTree/STACK_FILE_TYPE_WayToNode.h\" -o temp/stack_way_func.o

temp/stack_way_error.o:
	g++ -c STL_Stack/STL_stack_print_error.cpp -DSTACK_FILE_TYPE=\"../BinTree/STACK_FILE_TYPE_WayToNode.h\" -o temp/stack_way_error.o

makedirs:
	mkdir -p temp/


.PHONY: a.exe makedirs
