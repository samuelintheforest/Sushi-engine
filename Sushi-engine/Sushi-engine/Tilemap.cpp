#include "Tilemap.h"
#include <fstream>
#include <iostream>

namespace sushi {

    Tilemap::Tilemap(const std::string& filename) { loadFromFile(filename); }

    void Tilemap::loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        nlohmann::json j;
        file >> j;

        // the same code as range for
        for (auto& el : j.items()) {
            std::cout << el.key() << " : " << el.value() << "\n";
        }



        //int64_t map_grid_h = j["tileheight"];
        //int64_t map_grid_w = j["tileheight"];


        //for (nlohmann::json::iterator it = tilesets.begin(); it != tilesets.end(); ++it)
        //{
        //    std::cout << *it << "\n";
        //}


        //for (auto& ts : j["tilesets"]) { // Removed const here
        //    Tileset tileset;
        //    tileset.image = ts["image"].template get<std::string>();
        //    tileset.firstgid = ts["firstgid"].template get<int>();
        //    tileset.tilewidth = ts["tilewidth"].template get<int>();
        //    tileset.tileheight = ts["tileheight"].template get<int>();
        //    tileset.tilecount = ts["tilecount"].template get<int>();
        //    tileset.columns = ts["columns"].template get<int>();
        //    tilesets.push_back(tileset);
        //}

        //for (auto& ly : j["layers"]) { // Removed const here
        //    if (ly["type"] == "tilelayer") {
        //        Layer layer;
        //        layer.name = ly["name"];
        //        layer.width = ly["width"];
        //        layer.height = ly["height"];
        //        for (const auto& tile : ly["data"]) {
        //            layer.data.push_back(tile);
        //        }
        //        layers.push_back(layer);
        //    }
        //    else if (ly["type"] == "objectgroup") {
        //        ObjectGroup objectGroup;
        //        objectGroup.name = ly["name"];
        //        for (auto& obj : ly["objects"]) { // Removed const here
        //            Object object;
        //            object.id = obj["id"];
        //            object.name = obj["name"];
        //            object.x = obj["x"];
        //            object.y = obj["y"];
        //            object.width = obj["width"];
        //            object.height = obj["height"];
        //            if (obj.contains("gid")) {
        //                object.gid = obj["gid"];
        //            }
        //            else {
        //                object.gid = 0;
        //            }
        //            objectGroup.objects.push_back(object);
        //        }
        //        objectGroups.push_back(objectGroup);
        //    }
        //}
    }

    std::vector<Tilemap::Tileset> Tilemap::getTilesets() const { return tilesets; }
    std::vector<Tilemap::Layer> Tilemap::getLayers() const { return layers; }
    std::vector<Tilemap::ObjectGroup> Tilemap::getObjectGroups() const {
        return objectGroups;
    }

} // namespace sushi