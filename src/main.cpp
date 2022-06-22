#include <SFML/Graphics.hpp>
#include <openWav.hpp>
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    ImGui::SFML::Init(window);

    sf::Clock delta;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, delta.restart());

        ImGui::Begin("hello world");
        ImGui::Text("z key is pressed? = ");
        ImGui::Text(std::to_string(ImGui::IsKeyPressed(ImGuiKey_Z)).c_str());
        ImGui::Button("button text", ImVec2(0, 0));
        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}