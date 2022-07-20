#include <SFML/Graphics.hpp>
#include <files/openWav.hpp>
#include <display/window.hpp>
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

int main()
{
    
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>
                                               (sf::VideoMode(700, 500), "SFML works!");

    ImGui::SFML::Init(*window);

    Wav x("test.wav");
    disp y(window);
    y.openWavFile("test.wav");

    sf::Clock delta;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if( !ImGui::GetIO().WantCaptureMouse)
            {
                y.event(event);
            }
            if (event.type == sf::Event::Closed)
                window->close();
        }

        ImGui::SFML::Update(*window, delta.restart());

        ImGui::Begin("hello world");
        ImGui::Text(std::to_string(x.debugVal()).c_str());
        ImGui::Text(std::to_string(x.debugVar[0]).c_str());
        ImGui::Text(std::to_string(x.debugVar[1]).c_str());
        ImGui::Text(std::to_string(x.debugVar[2]).c_str());
        ImGui::Text(std::to_string(x.debugVar[3]).c_str());
        ImGui::Button("button text", ImVec2(0, 0));
        ImGui::End();

        window->clear();
        y.update();
        ImGui::SFML::Render(*window);
        window->display();
    }

    return 0;
}