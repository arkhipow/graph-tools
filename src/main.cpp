#include "window.hpp"

int main() {
    auto manager = WindowManager::CreateWindowManager();

    std::unique_ptr<WindowUnit> unit_1 = std::make_unique<WindowUnit>(1280, 720, "Unit 1");
    /* Setting up a unit_1 */

    std::unique_ptr<WindowUnit> unit_2 = std::make_unique<WindowUnit>(1280, 720, "Unit 2");
    /* Setting up a unit_2 */
    
    manager->Push(std::move(unit_1));
    manager->Push(std::move(unit_2));

    manager->Run();
}