#pragma once
#include "Common.h"

class Shader
{   
    public :
        void        initialize(const char* vertexRelativePath,const char* fragmentRelativePath);
        void        use(void);

    public :
        uint32      _programId;

    private:
        std::string _vertexFullPath;
        std::string _fragmentFullPath;
};
