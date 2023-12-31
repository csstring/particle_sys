#pragma once
#include "Common.h"

constexpr float cameraSpeed = 0.5f;
class Camera
{

    public:
        Camera() : _yaw(-90.0f), _pitch(0.0f), _mouseSensitivity(0.1f), _movementSpeed(2.5f), _fov(80.0f), _isFirst(true), _isOn(false)
        {};
        ~Camera(){};
        void update(void);
        void initialize(void);
        void updateCameraVectors(void);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
        glm::vec4 getWorldCursorPos() const;
    private:
        float _yaw;
        float _pitch;
        float _mouseSensitivity;

    public:
        float _movementSpeed;
        float _fov;
        bool _isFirst;
        bool _isOn;
        float _lastX;
        float _lastY;
        float _zNear = 0.1;
        float _zFar = 100;
        glm::vec3   _worldUp;
        glm::vec3   _cameraUp;
        glm::vec3   _cameraPos;
        glm::vec3   _cameraFront;
        glm::vec3   _cameraRight;
        glm::mat4   _view;
};  