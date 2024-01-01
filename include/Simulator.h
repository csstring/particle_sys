#pragma once
#include "Common.h"
#include "EnumHeader.h"

class Parser;
class Scean;
class Camera;
class Simulator : Noncopyable
{
    private:
        uint32 _textureID;
        uint32 _vertexSize;
        
    public:
        Scean* _scean = nullptr;
        int32 _drawCount;
        int32 _totalCount;
        
    public:
        glm::mat4 _worldTranslate;

        Simulator(){};
        ~Simulator();
        
        void initialize(uint32 particlecount);
        void update(float delta, const Camera& camera);
        void draw(void);
};

// std::ostream& operator<<(std::ostream& os, const std::pair<Animation*, TimeNode>& ref);