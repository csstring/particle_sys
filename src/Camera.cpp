#include "Camera.h"
#include "GLM/gtc/matrix_transform.hpp"
void Camera::update(void)
{
    _view = glm::lookAt(_cameraPos, _cameraPos+_cameraFront, _cameraUp);
}

void Camera::initialize(void)
{
    _cameraPos = glm::vec3(0, 0 ,2.0);
    _cameraUp = glm::vec3(0,1,0);
    _cameraFront = glm::vec3(0,0,-1);
    _worldUp = _cameraUp;
    _zFar = 100;
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    _fov -= (float)yoffset;
    if (_fov < 1.0f)
        _fov = 1.0f;
    if (_fov > 80.0f)
        _fov = 80.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(front);

    _cameraRight = glm::normalize(glm::cross(_cameraFront, _worldUp));  
    _cameraUp    = glm::normalize(glm::cross(_cameraRight, _cameraFront));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }
    updateCameraVectors();
}

glm::vec4 Camera::getWorldXYPosition() const
{
    const float distance = (_zFar + _zNear) / 2.0f;
    const float midlePlaneY = distance * tan(glm::radians(_fov/2.0f)) * 2;
    const float midlePlaneX = midlePlaneY * ASPECT_RATIO;
    const float ratio = WINDOW_HEIGHT / midlePlaneY;

    const float y = 1.0f - (_lastY / ratio - midlePlaneY / 2);
    const float x = _lastX / ratio - midlePlaneX / 2;

    return glm::vec4(_cameraPos + _cameraFront * distance + _cameraRight * x + _cameraUp * y, 0);
}