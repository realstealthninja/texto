#pragma  once
#ifndef TEXTO_3D_HPP
#define TEXTO_3D_HPP


struct vector3 {
    float x;
    float y;
    float z;
};

struct vector2 {
    float x;
    float y;
};


namespace textoEngine {
    class Camera {
        public:
            vector3 Position{};
            vector3 Target{};
            Camera(vector3 position, vector3 target);
            [[nodiscard]] vector3 getPosition() const;
            [[nodiscard]] vector3 getTarget() const;
    };


    class Mesh {
        public:
            std::string Name;
            vector3 Position{};
            vector3 Rotation{};
            std::vector<vector3> Vertices;
            Mesh(
                    std::string name,
                    vector3 position,
                    vector3 rotation,
                    std::vector<vector3> vertices
            );
    };
}

#endif //TEXTO_3D_HPP
