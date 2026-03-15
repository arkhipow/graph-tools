#include "window.hpp"
#include "panel.hpp"

int main() {
    auto manager = WindowManager::CreateWindowManager();

    /* Unit 1 */
    std::unique_ptr<WindowUnit> unit1 = std::make_unique<WindowUnit>(1280, 720, "Unit 1");
    unit1->SetMinWidth(1280);
    unit1->SetMinHeight(720);
    unit1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    PanelGraph graph1;
    unit1->PushPanelUnit();
    /* Setting up a unit_1 */

    /* Unit 2 */
    std::unique_ptr<WindowUnit> unit2 = std::make_unique<WindowUnit>(1280, 720, "Unit 2");
    /* Setting up a unit_2 */

    manager->PushWindowUnit(std::move(unit1));
    manager->PushWindowUnit(std::move(unit2));

    manager->Run();
}