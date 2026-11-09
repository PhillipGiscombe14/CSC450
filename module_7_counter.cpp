#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <system_error>
#include <thread>

namespace {
constexpr int kFirstCount = 0;
constexpr int kLastCount = 20;

// The mutex protects the completion flag; the condition variable provides
// the handoff from the counting-up thread to the counting-down thread.
struct CounterState {
    std::mutex mutex;
    std::condition_variable completed;
    bool countUpComplete = false;
};

void countUp(CounterState& state) {
    std::cout << "Count up:   ";
    for (int count = kFirstCount; count <= kLastCount; ++count) {
        std::cout << count << (count == kLastCount ? '\n' : ' ');
    }

    // Mark the count-up as complete before notifying the waiting thread.
    {
        std::lock_guard<std::mutex> lock(state.mutex);
        state.countUpComplete = true;
    }
    state.completed.notify_one();
}

void countDown(CounterState& state) {
    {
        std::unique_lock<std::mutex> lock(state.mutex);
        // Wait until the count-up thread has finished printing.
        state.completed.wait(lock, [&state] { return state.countUpComplete; });
    }

    std::cout << "Count down: ";
    for (int count = kLastCount; count >= kFirstCount; --count) {
        std::cout << count << (count == kFirstCount ? '\n' : ' ');
    }
}
}  // namespace

int main() {
    CounterState state;
    std::thread upThread;
    std::thread downThread;

    try {
        upThread = std::thread(countUp, std::ref(state));
        downThread = std::thread(countDown, std::ref(state));
    } catch (const std::system_error& error) {
        // If the second thread could not start, finish the first before exit.
        if (upThread.joinable()) {
            upThread.join();
        }
        std::cerr << "Unable to create a counter thread: " << error.what()
                  << '\n';
        return 1;
    }

    // Wait for both threads to finish before the program exits.
    upThread.join();
    downThread.join();
    return 0;
}
