#include "camera.h"
#include "game.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Nebel
{
    bool isFullScreen = false;
    void Camera::update(float sensitivity)
    {
        projection = glm::perspective(glm::radians(fov), (float)Game::platform->width/Game::platform->height, near, far);
        view = glm::lookAt(position, position + front, up);
        //rotation
        yaw += Input::MouseDelta.x;
        pitch += Input::MouseDelta.y;

        if (pitch > 89.0f)
            {pitch = 89.0f;}
        if (pitch < -89.0f)
            {pitch = -89.0f;}
        glm::vec3 cameraFront;
        cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront.y = sin(glm::radians(pitch));
        cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(cameraFront);
        //movement
        float cameraSpeed = static_cast<float>(0.5);// * deltaTime);
        if (Input::isKeyDown(Key::W))
            {position += cameraSpeed * cameraFront;}
        if (Input::isKeyDown(Key::S))
            {position -= cameraSpeed * cameraFront;}
        if (Input::isKeyDown(Key::A))
            {position -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;}
        if (Input::isKeyDown(Key::D))
            {position += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;}
        if (Input::isKeyDown(Key::Q))
            {position -= glm::vec3(0,1,0) * cameraSpeed;}
        if (Input::isKeyDown(Key::E))
            {position += glm::vec3(0,1,0) * cameraSpeed;}
        if (Input::isKeyDown(Key::F))
            isFullScreen = !isFullScreen;
            Game::platform->setfullscreen(isFullScreen);
    }
    void Camera2D::update()
    {
        float halfwidth = Game::platform->width / 2;
        float halfheight = Game::platform->height / 2;
        projection = glm::ortho(-halfwidth, halfwidth, halfheight, -halfheight, -1000.0f, 1000.0f);
        /*
        
        projection = glm::perspective(glm::radians(fov), (float)Game::platform->width/Game::platform->height, near, far);
        view = glm::lookAt(position, position + front, up);
        //rotation
        yaw += Input::MouseDelta.x;
        pitch += Input::MouseDelta.y;

        if (pitch > 89.0f)
            {pitch = 89.0f;}
        if (pitch < -89.0f)
            {pitch = -89.0f;}
        glm::vec3 cameraFront;
        cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront.y = sin(glm::radians(pitch));
        cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(cameraFront);
        //movement
        float cameraSpeed = static_cast<float>(0.5);// * deltaTime);
        if (Input::isKeyDown(Key::W))
            {position += cameraSpeed * cameraFront;}
        if (Input::isKeyDown(Key::S))
            {position -= cameraSpeed * cameraFront;}
        if (Input::isKeyDown(Key::A))
            {position -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;}
        if (Input::isKeyDown(Key::D))
            {position += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;}
        if (Input::isKeyDown(Key::Q))
            {position -= glm::vec3(0,1,0) * cameraSpeed;}
        if (Input::isKeyDown(Key::E))
            {position += glm::vec3(0,1,0) * cameraSpeed;}
        
        */
    }
} // namespace Nebel
