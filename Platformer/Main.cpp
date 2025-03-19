//#include "ImGui/imgui.h"
//#include "ImGui/imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <SFML/Config.hpp>



#include "Grid.h"
#include "Gravity.h"
#include "Particle.h"

int main() {
    

    system("pause"); // Keep the window open
    sf::RenderWindow window(sf::VideoMode(2000, 1600), "Gravity Sim");
    window.setFramerateLimit(120);

    //ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    Grid grid(50);
    bool showGrid = true;

    std::vector<Gravity> gravities;
    std::vector<Particle> particles;

    gravities.emplace_back(640, 365, 250, 2); 
    gravities.emplace_back(1000, 865, 150,2);

    particles.emplace_back(800, 500, 1, 1, 1); 
    particles.emplace_back(1100, 400, 2, 1,1);

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds(); // Restart the clock and get elapsed time
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    gravities.emplace_back(mousePos.x, mousePos.y, 1000, 6);
                }

                else if (event.mouseButton.button == sf::Mouse::Middle)
                    particles.emplace_back(mousePos.x, mousePos.y, 0.1f, 0.1f, 1);

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    //checking if theres at least one gravity
                    if (!gravities.empty()) {
                    //initialize variables to track closest gravity source
                    //minDist is set to highest posible float so any real distance will be smaller
                    // closestGravity just says that we havent found any gravity nearby yet
                        float minDist = std::numeric_limits<float>::max();
                        auto closestGravity = gravities.end();

                    //looping thtough all gravity sources to find closest one
                        for (auto it = gravities.begin(); it != gravities.end(); ++it) {
                            float dx = it->get_pos().x - mousePos.x;
                            float dy = it->get_pos().y - mousePos.y;
                            float distance = std::sqrt(pow(dx,2) + pow(dy,2));

                            if (distance < minDist) {
                                minDist = distance;
                                closestGravity = it;
                            }
                        }

                       //remove the closest gravity source if it's within a 30px
                        if (closestGravity != gravities.end() && minDist < 30) {
                            gravities.erase(closestGravity);
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::G) {
                    showGrid = !showGrid; 
                }
            }

        }
        /*
        ImGui::SFML::Update(window, deltaClock.restart());
        
        ImGui::Begin("Gravity Controls");
        for (size_t i = 0; i < gravities.size(); i++)
        {
            Gravity& g = gravities[i];
            ImGui::Text("Gravity source %d", static_cast<int>(i));
            float mass = g.get_mass();
            float strength = g.get_strenght();

            std::string mass_Label = "Mass##" + std::to_string(i);
            if (ImGui::SliderFloat(mass_Label.c_str(), &mass, 1.f, 300.f))
                g.set_mass(mass);

            ImGui::Separator();
        }
        ImGui::End();
        */

        //for (auto& grav : gravities)

        window.clear();
        
        if (showGrid)
            grid.render(window, gravities);
        
       
        for (auto& particle : particles )
        {
            for (auto& gravity : gravities)
            {
                particle.update_phy(gravity);
            }

        }
        for (auto& grav : gravities) {
            grav.update(gravities, dt);
        }
        
        for (size_t i = 0; i < particles.size(); i++)
        {
            particles[i].check_colision(particles);
        }


        for (auto& grav : gravities) {
            grav.render(window);
        }

        for (auto& part : particles)
            part.render(window);

        window.display();
        

    }
    
    return 0;
}
