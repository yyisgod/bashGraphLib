LIBPATH=../ImageLib
CPPFLAGS=-std=c++11 -pthread -limage -L. -I$(LIBPATH)

bomb:*.cpp *.h libimage.a
	$(CXX) *.cpp -o bomb $(CPPFLAGS) -O3

libimage.a : $(LIBPATH)/*.cpp
	g++ -std=c++11 -pthread -c $^
	ar r libimage.a $(subst .cpp,.o,$(notdir $^))
g:
	g++ *.cpp -o main $(CPPFLAGS) -g

.PHONY:clean
clean:
	rm libimage.a bomb *.o main
