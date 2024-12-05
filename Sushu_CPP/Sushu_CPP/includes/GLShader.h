#ifndef SHADER_H
#define SHADER_H


#include "../../../vendor/include/glad/glad.h"
#include "Types.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace sushi {
    class GLShader
    {
    public:
        uint32_t ID;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        GLShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
        ~GLShader(void);
        // activate the shader
        // ------------------------------------------------------------------------
        void use();

        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string& name, bool value) const;
        // ------------------------------------------------------------------------
        void setInt(const std::string& name, int32_t value) const;
        // ------------------------------------------------------------------------
        void setFloat(const std::string& name, float value) const;
        // ------------------------------------------------------------------------
        void setVec2(const std::string& name, const Vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        // ------------------------------------------------------------------------
        void setVec3(const std::string& name, const Vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        // ------------------------------------------------------------------------
        void setVec4(const std::string& name, const Vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w);
        // ------------------------------------------------------------------------
        void setMat2(const std::string& name, const Mat2& mat) const;
        // ------------------------------------------------------------------------
        void setMat3(const std::string& name, const Mat3& mat) const;
        // ------------------------------------------------------------------------
        void setMat4(const std::string& name, const Mat4& mat) const;

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(uint32_t shader, std::string type);
    };
}
#endif
