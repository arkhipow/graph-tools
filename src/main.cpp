#include "window.hpp"

int main() {
    auto manager = WindowManager::CreateWindowManager();

    /* Unit 1 */
    auto unit1 = std::make_unique<WindowUnit>(1280, 720, "Unit 1");
    unit1->SetMinWidth(1280);
    unit1->SetMinHeight(720);
    unit1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    auto button1 = std::make_unique<PanelButton>(1260, 50, "Button 1");
    button1->SetPos(10, 10);

    unit1->PushPanelUnit(std::move(button1));
    /* Setting up a unit_1 */

    /* Unit 2 */
    auto unit2 = std::make_unique<WindowUnit>(1280, 720, "Unit 2");
    /* Setting up a unit_2 */

    manager->PushWindowUnit(std::move(unit1));
    manager->PushWindowUnit(std::move(unit2));

    manager->Run();
}