LIBPATH=../bashGraphLib
CPPFLAGS=-std=c++11 -limage -L. -static

bomb:*.cpp *.h libimage.a
	$(CXX) *.cpp -o bomb $(CPPFLAGS) -O3

libimage.a : $(LIBPATH)/*.cpp
	g++ -std=c++11 -c $^
	ar r libimage.a $(subst .cpp,.o,$(notdir $^))
g:
	g++ *.cpp -o main $(CPPFLAGS) -g

.PHONY:clean
clean:
	rm *.o
