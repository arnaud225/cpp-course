#include <iostream>
#include <future>
#include <thread>
 
int main()
{
    // future depuis un packaged_task
    std::packaged_task<int()> task([](){ return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread(std::move(task)).detach(); // launch on a thread
 
    // future depuis un async()
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
 
    // future depuis un promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [](std::promise<int>& p){ p.set_value(9); }, 
                 std::ref(p) ).detach();
 
    std::cout << "En attente...";
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Fait!\nLes resultats sont: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
}
