//Töltse ki a program hiányzó részeit ahhoz, hogy az alábbi kimenetet adja a program:
/*
nothing to consume
nothing to consume
nothing to consume
Added to queue: round 1 - item 0
Added to queue: round 1 - item 1
  --> consumed value: round 1 - item 0
  --> consumed value: round 1 - item 1
Added to queue: round 2 - item 0
  --> consumed value: round 2 - item 0
nothing to consume
nothing to consume
nothing to consume
nothing to consume
nothing to consume
nothing to consume
nothing to consume
nothing to consume
nothing to consume
*/

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <vector>

class Queue {
    std::list<std::string> elements;
public:
    void add(const std::string& s) { elements.push_back(s); }
    std::string get() {
        if (!elements.empty()) {
            std::string retval = elements.front();
            elements.pop_front();
            return retval;
        }
        else {
            throw int{};    // toltse ki! dobjon kivetelt!
        }
    }
};

void producer(Queue* queue) {
    int numItemsToProducePerRound[5] = { 0, 2, 1, 0, 0 };
    for (int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (int j = 0; j < numItemsToProducePerRound[i]; j++) {
            queue->add("round " + std::to_string(i) + " - item " + std::to_string(j));
            std::cout << "Added to queue: " << ("round " + std::to_string(i) + " - item " + std::to_string(j)) << std::endl;
        }
    }
}

void consumer(Queue* queue) {
    
    try{
        std::string val = queue->get();
        std::cout << "  --> consumed value: " << val << std::endl;
    }catch(int err){
        std::cout << "nothing to consume\n";    // toltse ki! kapja el a fent dobott kivetelt es irja ki, hogy "nothing to consume"
    }
}

void f() {
    Queue myqueue;

    std::thread producerThread(producer,&myqueue);   // toltse ki! 1 kodsor hianyzik, egy producerThread nevu szalat hozzon letre amely a producer fv-t futtatja

    for (int i = 0; i < 5; i++) {
        consumer(&myqueue);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    producerThread.join();  // toltse ki! producerThread-et be kell varni!
    
}

int main(){
    f();
    return 0;
}

/*MYRESULT
nothing to consume
Added to queue: round 1 - item 0
Added to queue: round 1 - item 1
  --> consumed value: round 1 - item 0
Added to queue: round 2 - item 0
  --> consumed value: round 1 - item 1
  --> consumed value: round 2 - item 0
nothing to consume
*/

/*result
nothing to consume
Added to queue: round 1 - item 0
Added to queue: round 1 - item 1
  --> consumed value: round 1 - item 0
Added to queue: round 2 - item 0
  --> consumed value: round 1 - item 1
  --> consumed value: round 2 - item 0
nothing to consume
*/
