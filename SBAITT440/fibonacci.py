#QUESTION PART D
# a) result of fibonacci series printing
# b) result of printing square numbers 
# c) result of printing cube numbers
# d) show the source code 

import threading

class FiboThread(threading.Thread):
    def run(self):
        a, b = 0, 1
        while b <= 10000:
            print(b)
            a, b = b, a + b

class SqThread(threading.Thread):
    def run(self):
        for i in range(1, 10001):
            print(i * i)

class CbThread(threading.Thread):
    def run(self):
        for i in range(1, 10001):
            print(i * i * i)

# Create and start the threads
fib_thread = FiboThread()
sq_thread = SqThread()
cb_thread = CbThread()

fib_thread.start()
sq_thread.start()
cb_thread.start()

# Wait for all threads to finish
fib_thread.join()
sq_thread.join()
cb_thread.join()
