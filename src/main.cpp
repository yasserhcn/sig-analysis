#include <SFML/Graphics.hpp>
#include <files/openWav.hpp>
#include <display/window.hpp>
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

int main()
{
    
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>
                                               (sf::VideoMode(900, 600), "SFML works!");

    if(! ImGui::SFML::Init(*window)){
        return -1;
    }

    disp y(window);

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

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::SFML::Update(*window, delta.restart());

        window->clear();
        y.update();
        ImGui::SFML::Render(*window);
        window->display();
    }

    return 0;
}