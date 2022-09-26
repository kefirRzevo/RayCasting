CXX    = g++
TARGET = app
#CXXFLAGS = -g -std=c++14 -Wall -Wextra \
-Weffc++ -Wc++0x-compat \
-Wc++11-compat -Wc++14-compat -Wcast-qual \
-Wchar-subscripts   \
-Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
-Wformat-nonliteral -Wformat-security  \
-Wformat=2 -Winline \
-Wmissing-declarations -Wnon-virtual-dtor \
-Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls \
-Wshadow -Wsign-conversion -Wsign-promo \
 -Wstrict-overflow=2 \
 -Wsuggest-override \
 -Wundef -Wunreachable-code -Wunused \
 -Wvariadic-macros \
-Wno-missing-field-initializers -Wno-narrowing \
-Wno-old-style-cast -Wno-varargs -fcheck-new \
-fsized-deallocation -fstack-check -fstack-protector \
-fstrict-overflow \
-fno-omit-frame-pointer \
-fsanitize=address \
-fsanitize=bool \
-fsanitize=bounds \
-fsanitize=enum \
-fsanitize=float-cast-overflow \
-fsanitize=float-divide-by-zero \
-fsanitize=integer-divide-by-zero \
-fsanitize=nonnull-attribute \
-fsanitize=null \
-fsanitize=return \
-fsanitize=returns-nonnull-attribute \
-fsanitize=shift \
-fsanitize=signed-integer-overflow \
-fsanitize=undefined \
-fsanitize=unreachable \
-fsanitize=vla-bound \
-fsanitize=vptr

# $(CXX) -g $(CXXFLAGS) -c  main.cpp src/akinator.cpp src/dump.cpp src/parser.cpp src/tree.cpp
#"${workspaceFolder}\\/main.cpp", "${workspaceFolder}\\/lib/hash.cpp", "${workspaceFolder}\\/lib/operators.cpp", "${workspaceFolder}/\\src/lib/tree_viz_dump.cpp", "${workspaceFolder}/\\lib/tree.cpp", "${workspaceFolder}/\\src/differentiator.cpp", "${workspaceFolder}/\\src/optimization.cpp", "${workspaceFolder}/\\src/parser.cpp"
	
make: 
	$(CXX) $(CXXFLAGS) -Ofast -c -o obj/main.o  main.cpp
	$(CXX) $(CXXFLAGS) -Ofast -c -o obj/render.o src/render.cpp
	$(CXX) -o $(TARGET) obj/main.o obj/render.o -lsfml-graphics -lsfml-window -lsfml-system
	./$(TARGET)

clean:
	rm -rf obj/*.o $(TARGET)

kill:
	rm -rf logfiles/*.txt
	