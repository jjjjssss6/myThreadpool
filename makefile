test:
	g++ threadpool.h safeQueue.h test.cpp -pthread -o test

clean:
	rm test