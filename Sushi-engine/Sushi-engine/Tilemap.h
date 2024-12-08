#ifndef TILEMAP_H
#define TILEMAP_H

// Tilemap.h
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace sushi {

    class Tilemap {
    public:
        struct Tileset {
            std::string image;
            int firstgid;
            int tilewidth;
            int tileheight;
            int tilecount;
            int columns;
        };

        struct Layer {
            std::string name;
            int width;
            int height;
            std::vector<int> data;
        };

        struct Object {
            int id;
            std::string name;
            double x;
            double y;
            double width;
            double height;
            int gid;
        };

        struct ObjectGroup {
            std::string name;
            std::vector<Object> objects;
        };

        Tilemap(const std::string& filename);

        void loadFromFile(const std::string& filename);

        std::vector<Tileset> getTilesets() const;
        std::vector<Layer> getLayers() const;
        std::vector<ObjectGroup> getObjectGroups() const;

    private:
        std::vector<Tileset> tilesets;
        std::vector<Layer> layers;
        std::vector<ObjectGroup> objectGroups;
    };

} // namespace sushi

#endif
