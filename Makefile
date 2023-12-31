DEBUG_FLAGS = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
RELEASE_FLAGS = -O2
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system

EXE_FILE = Exe/run

debug: vector_debug coord_sys_debug widget_debug particle_debug flask_debug circle_particle_debug square_particle_debug button_debug button_manager_debug plot_debug
	g++ $(SFML_FLAGS) $(DEBUG_FLAGS) Src/main.cpp Obj/Vector.o Obj/CoordSystem.o Obj/Widget.o Obj/Particle.o Obj/Flask.o Obj/CircleParticle.o Obj/SquareParticle.o Obj/Button.o Obj/ButtonManager.o Obj/Plot.o -o $(EXE_FILE)
release: vector_release coord_sys_release widget_release particle_release flask_release circle_particle_release square_particle_release button_release button_manager_release plot_release
	g++ $(SFML_FLAGS) $(RELEASE_FLAGS) Src/main.cpp Obj/Vector.o Obj/CoordSystem.o Obj/Widget.o Obj/Particle.o Obj/Flask.o Obj/CircleParticle.o Obj/SquareParticle.o Obj/Button.o Obj/ButtonManager.o Obj/Plot.o -o $(EXE_FILE)

vector_debug:
	g++ -c $(DEBUG_FLAGS) Src/Vector/Vector.cpp -o Obj/Vector.o
vector_release:
	g++ -c $(RELEASE_FLAGS) Src/Vector/Vector.cpp -o Obj/Vector.o

coord_sys_debug:
	g++ -c $(DEBUG_FLAGS) Src/CoordSystem/CoordSystem.cpp -o Obj/CoordSystem.o
coord_sys_release:
	g++ -c $(RELEASE_FLAGS) Src/CoordSystem/CoordSystem.cpp -o Obj/CoordSystem.o

widget_debug:
	g++ -c $(DEBUG_FLAGS) Src/Widget/Widget.cpp -o Obj/Widget.o
widget_release:
	g++ -c $(RELEASE_FLAGS) Src/Widget/Widget.cpp -o Obj/Widget.o

particle_debug:
	g++ -c $(DEBUG_FLAGS) Src/Particle/Particle.cpp -o Obj/Particle.o
particle_release:
	g++ -c $(RELEASE_FLAGS) Src/Particle/Particle.cpp -o Obj/Particle.o

circle_particle_debug:
	g++ -c $(DEBUG_FLAGS) Src/Particle/CircleParticle/CircleParticle.cpp -o Obj/CircleParticle.o
circle_particle_release:
	g++ -c $(RELEASE_FLAGS) Src/Particle/CircleParticle/CircleParticle.cpp -o Obj/CircleParticle.o

square_particle_debug:
	g++ -c $(DEBUG_FLAGS) Src/Particle/SquareParticle/SquareParticle.cpp -o Obj/SquareParticle.o
square_particle_release:
	g++ -c $(RELEASE_FLAGS) Src/Particle/SquareParticle/SquareParticle.cpp -o Obj/SquareParticle.o

flask_debug:
	g++ -c $(DEBUG_FLAGS) Src/Widget/Flask/Flask.cpp -o Obj/Flask.o
flask_release:
	g++ -c $(RELEASE_FLAGS) Src/Widget/Flask/Flask.cpp -o Obj/Flask.o

button_debug:
	g++ -c $(DEBUG_FLAGS) Src/Widget/Button/Button.cpp -o Obj/Button.o
button_release:
	g++ -c $(RELEASE_FLAGS) Src/Widget/Button/Button.cpp -o Obj/Button.o

button_manager_debug:
	g++ -c $(DEBUG_FLAGS) Src/ButtonManager/ButtonManager.cpp -o Obj/ButtonManager.o
button_manager_release:
	g++ -c $(RELEASE_FLAGS) Src/ButtonManager/ButtonManager.cpp -o Obj/ButtonManager.o

plot_debug:
	g++ -c $(DEBUG_FLAGS) Src/Widget/Plot/Plot.cpp -o Obj/Plot.o
plot_release:
	g++ -c $(RELEASE_FLAGS) Src/Widget/Plot/Plot.cpp -o Obj/Plot.o

run:
	./$(EXE_FILE)

preparation:
	mkdir Obj
	mkdir Exe

