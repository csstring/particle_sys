#pragma once
#include "Common.h"
#include "EnumHeader.h"
#include "Scean.h"
#include <memory>

class Parser;
class Camera;
class Simulator : Noncopyable
{
    public:
        std::unique_ptr<Scean> _scean;
        int32 _speed;
        int32 _pointSize;
        int32 _drawCount;
        int32 _totalCount;

    public:
        Simulator() : _speed(0), _pointSize(4){};
        ~Simulator();
        
        void initialize(uint32 particlecount);
        void update(float delta, const Camera& camera);
        void draw(void);
};

// std::ostream& operator<<(std::ostream& os, const std::pair<Animation*, TimeNode>& ref);