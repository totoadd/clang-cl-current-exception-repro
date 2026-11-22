#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <iostream>

void terminateHandler() noexcept {
    auto ptr = std::current_exception();

    if (!ptr) {
        std::cout << "The exception pointer is null" << std::endl;
        std::exit(1);
    }

    try {
        std::rethrow_exception(ptr);
    }
    catch (const std::logic_error& e) {
        std::cout << "Current exception: " << e.what() << std::endl;
        std::exit(42);
    }
    catch (...) {
        std::exit(2);
    }
}

__declspec(noinline) void throwException() {
    throw std::logic_error("An exception");
}

__declspec(noinline) void noexceptBoundary() noexcept {
    throwException();
}

__declspec(noinline) void invokeWithCatch(void (*action)() noexcept) {
    try {
        action();
    }
    catch (...) {
        std::exit(99);
    }
}

int main() {
    std::set_terminate(terminateHandler);
    invokeWithCatch(&noexceptBoundary);
}
